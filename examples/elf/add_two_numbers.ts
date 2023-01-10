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
import { type MeasureResult, Measuresuite } from "measuresuite";

import * as path from "path";

/**
 * our objects / shared objects we create from the ./add_two_numbers.asm
 */

const filenameElf = path.resolve("./add_two_numbers.o");
const filenameShared = path.resolve("./add_two_numbers.so");
const functionSymbol = "add_two_numbers"; // c.f. ./add_two_numbers.asm:1 'global add_two_numbers' and line 3

const arg_width = 1;
const arg_num_out = 1;
const arg_num_in = 2;

// create a Measuresuite object
const ms = new Measuresuite(arg_width, arg_num_in, arg_num_out);
ms.enableChecking();

// number of batches: each function will have at least this many time-measurements
const nob = 50;

// how many times the functionA/B are called within a loop. Short functions need bigger
// numbers in order to have sensible measurements
const batchSize = 10000;
console.debug({ filenameElf, filenameShared });

ms.loadFile({ filename: filenameShared, functionSymbol }); // symbol req'd because we internally use 'dlopen'
ms.loadFile({ filename: filenameElf }); // will use the first found symbol from the elf file

// measure
const measurementResult: MeasureResult | null = ms.measure(batchSize, nob);

if (!measurementResult) {
  // this is more or less for typescript tooling to assert, that measurementResult is not nullish
  throw new Error("measurementResult is nullish. This should not happen.");
}

if (measurementResult.functions.length !== 2) {
  throw new Error("should have two functions measured.");
}

if (measurementResult.stats.incorrect !== 0) {
  throw new Error(
    "This means, that the two functions did not compute the same result."
  );
}

// this gives the entire runtime for all batches in milliseconds... Really depends on the system
console.log(
  `The Measurement took ${measurementResult.stats.runtime}ms to complete`
);

/* lets look at the cycles: (= same as number of functions loaded)
    each of the measurements have num_batches (nob) elements
*/

const [functionARes, functionBRes] = measurementResult.cycles;
console.log(`Function A's cycles: ${functionARes.join(",")}`);
console.log(`Function B's cycles: ${functionBRes.join(",")}`);

const medianA = functionARes.sort().at(Math.floor(nob / 2)) ?? -1;
const medianB = functionBRes.sort().at(Math.floor(nob / 2)) ?? -1;

console.log(`Function A's median: ${medianA}`);
console.log(`Function B's median: ${medianB}`);

console.log(
  `Function A is${medianA < medianB ? " " : " not "}faster than Function B`
);
