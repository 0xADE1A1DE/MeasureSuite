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
  stats: {
    countA: number;
    countB: number;
    chunksA: number;
    chunksB: number;
    batchSize: number;
    numBatches: number;
    runtime: number;
    runOrder: string;
    checkResult: boolean;
  };
  times: [number, number, number][];
}
/**
 * example:
{
  "stats": {
    "countA": 6, //function_A was run 6 times
    "countB": 4  //function_B was run 4 times
    "countA": 6, //function_A breaks the given chunk boundary 6 times.
    "countB": 4  //function_B breaks the given chunk boundary 4 times.
    "batchSize": 10, // a batch has a size. This is the number of iterations of the same function which is measured (for(batchSize=10;batchSize; batchSize--)function_A/function_B). This is the length of the times-array
    "numBatches": 4,   //this is the minimum that each function needs to be ran. Either countA or countB is equal to this number.
    "runtime": 0, // in milliseconds, is too short in this example. It is the time which is used for the experiments, excluding the set up and cleanup
    "runOrder": "abbaabaab", // order in which the functions were executed. Executions of checkFunctions are omitted.
    "checkResult": true // whether the results is correct (whatever was run last compared to what function_check calculated)
  },
  // number in tuples are runtime from A and B and check_method respectively. Using -1 if there is no number for the other run.
  // the array is at least stats.numBatches in size; aka. each function has at least stats.numBatches entries.
  "times": [
    [176, -1, 174], // a was run, 10 evauluations of A took 176 cycles, then c was executed where 10 executions (batchSize) took 174 cycles.
    [-1, 300, 178], // b was run here: 10 executions (batch Size) took 300 cycles, c needed 178 for 10 executions (batchSize).
    [-1, 344, 181],
    [185, -1, 170],
    [274, -1, 181],
    [-1, 401, 181],
    [257, -1, 177],
    [355, -1, 266],
    [-1, 477, 375]
  ]
}
  */

export interface uiCAResult {
  throughputA: number;
  throughputB: number;
}
