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

export interface MeasureResult {
  // example JSON
  //{
  //  "stats": {
  //    "numFunctions": 2,
  //    "runtime": 0,
  //    "incorrect": 0
  //  },
  //  "functions": [
  //    {
  //      "type": "ASM",
  //      "chunks": 0
  //    },
  //    {
  //      "type": "SHARED_OBJECT"
  //    }
  //  ],
  //  "cycles": [
  //    [ 2406, 1749, 1702, 1733, 1887, 2716, 2738, 2729, 2746, 2735 ],
  //    [ 1874, 1730, 1698, 1720, 1803, 1791, 2721, 2732, 2724, 2729 ]
  //  ]
  //}

  stats: {
    numFunctions: number;
    runtime: number;
    incorrect: number;
  };
  functions: FunctionSummary[];

  cycles: number[][];
}
export type FunctionSummary =
  | BaseSummary<"ELF">
  | BaseSummary<"BIN">
  | BaseSummary<"SHARED_OBJECT">
  | AsmFunctionSummary;

export type AsmFunctionSummary = BaseSummary<"ASM"> & { chunks: number };

export type FunctionType = "ASM" | "BIN" | "ELF" | "SHARED_OBJECT";

interface BaseSummary<T extends FunctionType> {
  type: T;
}

/**
 * example:
{
  "stats": {
    "numFunctions": 2  // 2 functions have been loaded. Details in functions-property
    "runtime": 0,      // in milliseconds, is too short in this example. It is the time which is used for the experiments, excluding the set up and cleanup
    "incorrect": 0,    // if checking was enabled, this will index to the first function which produces a different result than the previous one.
                       // i.e. 0 means all correct (as there is no previous)
                       // i.e. 1 means function 1 calculated a different result thant function 0
                       // i.e. x means function x calculated a different result thant function x-1,  and functions 0..x-1 all calculated the same.
  },
  "cycles":           // has the same length as functions and as specified in numFunctions
                      // each element contains num_batches numbers of the cyclecounts for the respective loaded function
}
  */
