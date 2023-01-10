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

/**
 * our assembly strings to measure, same as in ./add_two_numbers.c
 */

const functionA = [
  "mov rax, [rsi]",
  "add rax, [rdx]",
  "mov [rdi], rax",
  "ret",
].join("\n");

const functionB = [
  "mov rax, [rsi]",
  "push rbx",
  "mov rbx, [rdx]",
  "lea rax, [rbx + rax]",
  "mov [rdi], rax",
  "pop rbx",
  "ret",
].join("\n");

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

// measure
const measurementResult: MeasureResult | null = ms.measure(batchSize, nob, [
  functionA,
  functionB,
]);

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

const medianA = functionARes.sort().at(Math.floor(nob / 2));
const medianB = functionBRes.sort().at(Math.floor(nob / 2));

console.log(`Function A's median: ${medianA}`);
console.log(`Function B's median: ${medianB}`);

console.log(
  `Function A is ${medianA < medianB ? "" : "not"} faster than Function B`
);
