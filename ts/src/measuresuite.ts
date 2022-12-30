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

import { existsSync } from "fs";

import { createRequire } from "module";
const require = createRequire(import.meta.url);
// import * as ms from "measuresuite-native-module"; // for development and get the types and type completion
const ms = require("measuresuite-native-module");

import type { MeasureResult } from "./measure.interface";

// use with caution
export const native_ms = {
  init: ms.init,

  load_asm_string: ms.load_asm_string,
  load_asm_file: ms.load_asm_file,
  load_bin_file: ms.load_bin_file,
  load_elf_file: ms.load_elf_file,
  load_shared_object_file: ms.load_shared_object_file,

  enable_checking: ms.enable_checking,
  enable_chunk_counting: ms.enable_chunk_counting,
  set_bounds: ms.set_bounds,

  measure: ms.measure,
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
    if (!bounds || bounds.length === 0) {
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
      ms.init(argwidth, argNumIn, argNumOut);
      if (libcheckfunctionsFilename) {
        ms.enable_checking();
        ms.load_shared_object_file(libcheckfunctionsFilename, functionSymbol);
      }
      if (typeof chunkSize !== "undefined" && chunkSize !== null) {
        ms.enable_chunk_counting(chunkSize);
      }

      ms.set_bounds(bounds_u64);
    } catch (e) {
      console.error(e);
      throw new Error("Could not initialize Measuresuite.");
    }
  }

  public measure(batchSize: number, numBatches: number, functions: string[] = []): MeasureResult | null {
    let result: string | undefined;

    try {
      functions.forEach(ms.load_asm_string);
    } catch (e) {
      console.error("Measuresuite: in measuresuite_measure, an error occurred whilel loading asm strings", e);
      throw new Error(`Could not measure.${e}`);
    }

    try {
      result = ms.measure(batchSize, numBatches);
    } catch (e) {
      console.error("Measuresuite: in measuresuite_measure, an error occurred", e);
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
