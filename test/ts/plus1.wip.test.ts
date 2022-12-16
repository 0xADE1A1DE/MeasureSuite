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
import { unlinkSync } from "fs";
import { resolve } from "path";
import { describe, expect, it } from "vitest";

import { Measuresuite } from "../../src/";
import { width, numArgsIn, numArgsOut, functionA, functionB } from "./functions";
import { compileTestlib } from "./test-helper";

const sharedObject = resolve(process.cwd(), "libcheckfunctions-fiat-libtest.so");
describe("general with test_lib", () => {
  it("should get the right stats", () => {
    // We need to compile into the shared object from our all_lib.c.
    compileTestlib(sharedObject);

    // set up as the bound  (to Binary-and the inpot and results with)
    const bounds = ["0xffffffffffffffff"];

    // symbol in the shared object
    const symbol = "increment";

    // passed to Assemblyline for the stats of the chunk-breaking instructions
    const chunkSize = 16;

    // create a Measuresuite object
    const ms = new Measuresuite(width, numArgsIn, numArgsOut, chunkSize, bounds, sharedObject, symbol);

    // number of batches: each function will have at least this many time-measurements
    const nob = 50;

    // how many times the functionA/B are called within a loop. Short functions need bigger
    // numbers in order to have sensible measurements
    const batchSize = 10000;

    // measure
    const measurementResult = ms.measure(functionA, functionB, batchSize, nob);
    expect(measurementResult).toBeTruthy();
    if (!measurementResult) {
      // this is more or less for typescript tooling to assert, that measurementResult is not nullish
      throw new Error("measurementResult is nullish. This should not happen.");
    }

    // cleanup for the testfile lib
    unlinkSync(sharedObject);
  });
});
