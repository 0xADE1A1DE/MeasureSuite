/**
 * Copyright 2022 University of Adelaide
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { writeFileSync, mkdtempSync, existsSync, rmSync } from "fs";
import { resolve } from "path";
import { tmpdir } from "os";
import { execSync, spawnSync } from "child_process";

import { createRequire } from "module";
const require = createRequire(import.meta.url);
const ms = require("measureaddon");

import type { uiCAResult, MeasureResult } from "./measure.interface";

// use with caution
export const native_ms = {
  init: ms.measuresuite_init,
  measure: ms.measuresuite_measure,
};

export class Measuresuite {
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
    libcheckfunctionsFilename: string,
    functionSymbol: string,
  ) {
    if (!existsSync(libcheckfunctionsFilename)) {
      throw new Error(
        `${libcheckfunctionsFilename} does not exist. Cannot use measuresuite if there is no shared object for check the functions' results against.`,
      );
    }
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
        libcheckfunctionsFilename,
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
    "SKL",
    "SKX",
    "KBL",
    "CFL",
    "CLX",
    "ICL",
    "TGL",
    "RKL",
  ];

  private static uiCAPath: string;

  public static setUiCaPath(path: string) {
    Measuresuite.uiCAPath = path;
  }

  private static assertOkUiCaPath() {
    if (!Measuresuite.uiCAPath || !existsSync(Measuresuite.uiCAPath)) {
      throw new Error(
        `${Measuresuite.uiCAPath} does not exist. Cannot execute uiCA if the path does not even exist.`,
      );
    }
  }

  public static measureUiCA(functionA: string, functionB: string, arch: string): uiCAResult {
    Measuresuite.assertOkUiCaPath();

    if (!Measuresuite.supportedUicaArchs.includes(arch)) {
      throw new Error(
        `unsupported architecture. Supported are: ${Measuresuite.supportedUicaArchs.join(", ")}`,
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
      const uiCACmd = `python3 ${Measuresuite.uiCAPath} ${binFile} -raw -TPonly -arch ${arch}`;
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
    rmSync(tmpDir, { recursive: true });

    return {
      throughputA,
      throughputB,
    };
  }
}
