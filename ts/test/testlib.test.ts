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
import { afterAll, beforeAll, describe, expect, it } from "vitest";

import { Measuresuite } from "../src/";
import { width, numArgsIn, numArgsOut, functionA, functionB } from "./test_data/functions";
import { expectNotNull, compileTestlib } from "./test-helper";

const chunkSize = 16;
const sharedObject = resolve(process.cwd(), "libcheckfunctions-fiat-libtest-2.so");

beforeAll(() => {
  compileTestlib(sharedObject);
});

afterAll(() => {
  unlinkSync(sharedObject);
});

describe("general with test_lib", () => {
  it("should accept an empty bounds array ", () => {
    expect(() => {
      new Measuresuite(width, numArgsIn, numArgsOut, chunkSize, [], sharedObject, "increment");
    }).not.toThrow();
  });

  it("should throw if argwidth does not match bounds width", () => {
    expect(() => {
      new Measuresuite(
        width + 1,
        numArgsIn,
        numArgsOut,
        chunkSize,
        ["0xffffffffffffffff"],
        sharedObject,
        "increment",
      );
    }).toThrow();
  });
  it("should measure", () => {
    const ms = new Measuresuite(
      width,
      numArgsIn,
      numArgsOut,
      chunkSize,
      ["0xffffffffffffffff"],
      sharedObject,
      "increment",
    );
    const res = ms.measure(10, 10, [functionA, functionB]);
    expect(res).toBeTruthy();
    expect(res?.stats.incorrect).toBe(0);
  });

  it("should run measureLibOnly", () => {
    const ms = new Measuresuite(width, numArgsIn, numArgsOut, chunkSize, [], sharedObject, "increment");
    const numBatches = 100;
    const batchSize = 10000;
    const result = ms.measure(batchSize, numBatches);
    expectNotNull(result);

    expect(result.stats.numFunctions).toBe(1);
    expect(result.functions[0].type).toBe("SHARED_OBJECT");
    result.cycles[0].forEach((r) => {
      expect(typeof r).toBe("number");
      expect(r).toBeGreaterThanOrEqual(10);
    });
  });
});
