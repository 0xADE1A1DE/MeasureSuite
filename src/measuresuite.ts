import { writeFileSync, mkdtempSync, existsSync } from "fs";
import { resolve } from "path";
import { tmpdir } from "os";
import { execSync, spawnSync } from "child_process";
import ms from "measure-addon";

import type { uiCAResult, MeasureResult } from "./measure.interface";

// use with caution
export const native_ms = {
  init: ms.measuresuite_init,
  measure: ms.measuresuite_measure,
};
const uiCAPY = resolve(__dirname, `../uiCA/uiCA.py`);

export class Measuresuite {
  private static _libcheckfunctionsFilename: string;
  private static chunkSize: number;

  // the idea behind that is, to have different libcheckfunctions-p256-mul.so to be able to run multiple instances at the same time. otherwise one would overwrite the other
  public static set libcheckfunctionssuffix(suff: string) {
    this._libcheckfunctionsFilename = `${__dirname}/libcheckfunctions-${suff}.so`;
  }

  public static get libcheckfunctionsFilename(): string {
    if (!Measuresuite._libcheckfunctionsFilename) {
      throw new Error("set Measuresuite.libcheckfunctionssuffix first;");
    }
    return Measuresuite._libcheckfunctionsFilename;
  }

  /**
   *
   * @param bounds is a string array of length @param argwidth. It must contain hex-numbers representing a mask or an upper bound.
   * if the string ends with a '0/2/4/8' it is assumed to be a bound.
   * if the string ends with a '1/3/5/9/f' it is assumed to be a mask.
   * if it is considered a bound, the mask is compuded via subtracting 1.
   * bounds may also be an empty array, in which case -1 as the mask is assumed. (all bits used, no effective bound.)
   */
  public constructor(
    argwidth: number,
    argNumIn: number,
    argNumOut: number,
    chunkSize: number,
    bounds: string[],
    functionSymbol: string,
  ) {
    if (!existsSync(Measuresuite.libcheckfunctionsFilename)) {
      throw new Error(
        `${Measuresuite.libcheckfunctionsFilename} does not exist. Cannot use measuresuite if there is no so for check the functions' results against.`,
      );
    }
    Measuresuite.chunkSize = chunkSize;
    if (bounds.length === 0) {
      // default to 'use all bits'
      bounds = Array(argwidth).fill("0xffffffffffffffff");
    }
    if (argwidth !== bounds.length) {
      throw new Error("Illegal arguments. Bounds array must be same size as argwidth, or empty.");
    }
    const bigInts = bounds.map((v) => {
      if (["0", "2", "4", "8"].some((end) => v.endsWith(end))) {
        return BigInt(v) - BigInt(1);
      }
      return BigInt(v);
    });
    const bounds_u64 = new BigUint64Array(bigInts);

    try {
      ms.measuresuite_init(
        argwidth,
        argNumIn,
        argNumOut,
        chunkSize,
        bounds_u64,
        Measuresuite.libcheckfunctionsFilename,
        functionSymbol,
      );
    } catch (e) {
      console.error(e);
      throw new Error("Could not initialize Measuresuite.");
    }
  }

  public measure(
    functionA: string,
    functionB: string,
    batchSize: number,
    numBatches: number,
  ): MeasureResult | null {
    let result: string | undefined;
    try {
      result = ms.measuresuite_measure(functionA, functionB, batchSize, numBatches);
    } catch (e) {
      console.error("Measuresuite: in measuresuite_measure, an error occurred", e);
      throw new Error(`Could not measure.${e}`);
    }
    // const sub = result.substring( result.indexOf("{"), result.lastIndexOf("}") + 1); // skip other output, e.g. wrong bytes or extend memory info
    if (result) {
      try {
        return JSON.parse(result) as MeasureResult;
      } catch (e) {
        console.error(`While JSON.parse'ing an error occurred: I tried to parse: >>${result}<<`);
        throw e;
      }
    }
    return null;
  }

  public static supportedUicaArchs = [
    "SNB",
    "IVB",
    "HSW",
    "BDW",
    "SKL", "SKX", "KBL",
    "CFL",
    "CLX",
    "ICL",
    "TGL",
    "RKL",
  ];

  public static get uiCAinitialized(): boolean {
    return existsSync(uiCAPY);
  }

  public static measure_uiCA(functionA: string, functionB: string, arch: string): uiCAResult {
    if (!Measuresuite.supportedUicaArchs.includes(arch)) {
      throw new Error(
        `unsupported architecture. supported are: ${Measuresuite.supportedUicaArchs.join(",")}`,
      );
    }
    const tmpDir = mkdtempSync(resolve(tmpdir(), "measure"));
    const [throughputA, throughputB] = [functionA, functionB].map((fun) => {
      // write to disk
      const asmFile = resolve(tmpDir, "func.asm");
      writeFileSync(asmFile, fun);

      // create binary with asmline
      const binFile = resolve(tmpDir, "func.bin");
      spawnSync(`asmline`, ["-P", binFile, asmFile]);

      // call uiCA
      if (!Measuresuite.uiCAinitialized) {
        throw new Error(`uiCA seems to be not initialized.`);
      }

      const uiCACmd = `${uiCAPY} ${binFile} -raw -TPonly -arch ${arch}`;
      try {
        const tp = execSync(uiCACmd).toString();
        const nu = Number(tp);
        if (!isNaN(nu)) {
          return nu;
        }
      } catch (e) {
        console.error(e);
      }
      return -1;
    });
    // rmSync(tmpDir, { recursive: true });

    return {
      throughputA,
      throughputB,
    };
  }
}
