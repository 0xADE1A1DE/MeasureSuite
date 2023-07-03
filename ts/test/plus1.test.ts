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
import { unlinkSync } from "fs";
import { resolve } from "path";
import { describe, expect, it } from "vitest";

import { type MeasureResult, Measuresuite } from "../src/";
import { AsmFunctionSummary } from "../src/measure.interface";
import { width, numArgsIn, numArgsOut, functionA, functionB } from "./test_data/functions";
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
    const measurementResult: MeasureResult | null = ms.measure(batchSize, nob, [functionA, functionB]);
    expect(measurementResult).toBeTruthy();
    if (!measurementResult) {
      // this is more or less for typescript tooling to assert, that measurementResult is not nullish
      throw new Error("measurementResult is nullish. This should not happen.");
    }

    // Because all the functions calculate the same result, the id of the incorrect function shall be 0
    expect(measurementResult.stats.incorrect).toBe(0);

    // Should either have used RDTSCP or PMC
    expect(["RDTSCP", "PMC"]).toContain(measurementResult.stats.timer);
    expect(ms.timer).toBe(measurementResult.stats.timer);

    // should have used two ASM functions and one Shared Object
    expect(measurementResult.stats).toBeTruthy();
    expect(measurementResult.stats.numFunctions).toBe(3);

    expect(measurementResult.functions).toHaveLength(3);
    const [sharedObjectRes, functionARes, functionBRes] = measurementResult.functions;
    expect(sharedObjectRes.type).toBe("SHARED_OBJECT");
    expect(functionARes.type).toBe("ASM");
    expect(functionBRes.type).toBe("ASM");

    // the asm-functions should have a chunk with it

    // Function a, can be assembled in one chunk, hence there is no breaks
    expect((functionARes as AsmFunctionSummary).chunks).toBe(0);

    // Function b, is bigger and uses instructions at certain addresses, such that it breaks chunks with three instructions
    expect((functionBRes as AsmFunctionSummary).chunks).toBe(3);

    // this gives the entire runtime for all batches in milliseconds... Really depends on the system
    expect(measurementResult.stats.runtime).toBeGreaterThan(0);

    // lets look at the cycles: (= same as number of functions loaded)
    expect(measurementResult.cycles).toHaveLength(3);

    // each of which should have num_batches (nob) elements
    measurementResult.cycles.forEach((cycles) => {
      expect(cycles.length).toBe(nob);
      // and all of those should be positive integers
      cycles.forEach((cycle) => {
        expect(typeof cycle).toBe("number");
        expect(cycle).toBeGreaterThan(0);
      });
    });

    // cleanup for the testfile lib
    unlinkSync(sharedObject);
  });
});
