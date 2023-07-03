/**
 * Copyright 2023 University of Adelaide
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

import { existsSync } from "fs";
import { extname } from "path";

import { createRequire } from "module";
const require = createRequire(import.meta.url);
// import * as ms from "measuresuite-native-module"; // for development and get the types and type completion
const ms = require("measuresuite-native-module");
declare function assert(value: unknown): asserts value;

import type { MeasureResult, FunctionType } from "./measure.interface";

// use with caution
export const native_ms = {
  init: ms.init,

  load_asm_string: ms.load_asm_string,
  load_asm_file: ms.load_asm_file,
  load_bin_file: ms.load_bin_file,
  load_elf_file: ms.load_elf_file,
  load_shared_object_file: ms.load_shared_object_file,

  unload_all: ms.unload_all,
  unload_last: ms.unload_last,

  enable_checking: ms.enable_checking,
  enable_chunk_counting: ms.enable_chunk_counting,
  set_bounds: ms.set_bounds,

  measure: ms.measure,
  destroy: ms.destroy,
  get_timer: ms.get_timer,
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
    private argwidth: number,
    argNumIn: number,
    argNumOut: number,
    chunkSize?: number,
    bounds?: string[],
    libcheckfunctionsFilename?: string,
    functionSymbol?: string,
  ) {
    if (libcheckfunctionsFilename && !existsSync(libcheckfunctionsFilename)) {
      throw new Error(
        `${libcheckfunctionsFilename} does not exist. Cannot use measuresuite if there is no shared object for check the functions' results against.`,
      );
    }

    try {
      ms.init(argwidth, argNumIn, argNumOut);
      if (libcheckfunctionsFilename) {
        ms.enable_checking();
        ms.load_shared_object_file(libcheckfunctionsFilename, functionSymbol);
      }
      if (typeof chunkSize !== "undefined" && chunkSize !== null) {
        ms.enable_chunk_counting(chunkSize);
      }

      if (!bounds || bounds.length === 0) {
        // default to 'use all bits'
        bounds = Array(argwidth).fill("0xffffffffffffffff");
      }
      this.setBounds(bounds);
    } catch (e) {
      console.error(e);
      throw new Error("Could not initialize Measuresuite.");
    }

    // initializing the load's
    this.ft2load.set("ELF", ms.load_elf_file);
    this.ft2load.set("ASM", ms.load_asm_file);
    this.ft2load.set("BIN", ms.load_bin_file);
    this.ft2load.set("SHARED_OBJECT", ms.load_shared_object_file);
  }

  public get timer(): "PMC" | "RDTSCP" {
    const timer = ms.get_timer();
    if (timer === 0) {
      return "PMC";
    }
    if (timer === 1) {
      return "RDTSCP";
    }
    throw new Error("Could not get timer information from native module.");
  }

  public destroy(): number {
    return ms.destroy();
  }

  // mapping tables
  private ft2load = new Map<FunctionType, (filename: string, symbol: string) => void>();

  private ext2FT: { [ext: string]: FunctionType } = {
    o: "ELF",
    elf: "ELF",
    so: "SHARED_OBJECT",
    bin: "BIN",
    asm: "ASM",
  };

  public enableChecking(): void {
    ms.enable_checking();
  }

  public loadFile({
    filename,
    filetype,
    functionSymbol,
  }: {
    filename: string;
    filetype?: FunctionType;
    functionSymbol?: string;
  }): void {
    if (!filetype) {
      const ext = extname(filename).substring(1);
      filetype = this.ext2FT[ext];
      if (!filetype) {
        throw new Error(
          `type was not given, and could not be inferred from filename ${filename} (ext: ${ext})`,
        );
      }
    }
    // load the file with the appropriate filetype
    const loadFunction = this.ft2load.get(filetype);
    assert(loadFunction);
    loadFunction(filename, functionSymbol ?? "");
  }

  public setBounds(bounds: string[]): void {
    if (this.argwidth !== bounds.length) {
      throw new Error("Illegal arguments. Bounds array must be same size as argwidth, or empty.");
    }
    const bigInts = bounds.map((v) => {
      if (["0", "2", "4", "8"].some((end) => v.endsWith(end))) {
        return BigInt(v) - BigInt(1);
      }
      return BigInt(v);
    });
    const bounds_u64 = new BigUint64Array(bigInts);
    ms.set_bounds(bounds_u64);
  }

  public measure(batchSize: number, numBatches: number, functions: string[] = []): MeasureResult | null {
    let result: string | undefined;

    try {
      functions.forEach(ms.load_asm_string);
    } catch (e) {
      console.error("Measuresuite: in measuresuite_measure, an error occurred while loading asm strings", e);
      throw new Error(`Could not measure.${e}`);
    }

    try {
      result = ms.measure(batchSize, numBatches);
    } catch (e) {
      console.error("Measuresuite: in measuresuite_measure, an error occurred", e);
      throw new Error(`Could not measure.${e}`);
    }

    // unload them
    try {
      functions.forEach((_) => ms.unload_last());
    } catch (e) {
      console.error(
        "Measuresuite: in measuresuite_measure, an error occurred while unloading the functions after measuremets",
        e,
      );
      throw new Error(`Could not measure.${e}`);
    }

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
}
