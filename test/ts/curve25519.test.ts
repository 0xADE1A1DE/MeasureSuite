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

import { Measuresuite } from "../../src/";
import { bounds, functionA, functionB, width, numArgsIn, numArgsOut } from "./functions_sq";
import { numBatches, batchSize } from "./constants";
import { compileFiat } from "./test-helper";

const chunkSize = 16;
const sharedObject = resolve(process.cwd(), "libcheckfunctions-fiat-curve25519.so");

it("sanity check", () => {
  expect(functionA.length).toBe(5363);
  expect(functionB.length).toBe(4900);
});

beforeAll(() => {
  compileFiat(sharedObject);
});

afterAll(() => {
  unlinkSync(sharedObject);
});

describe("measure curve25519-sq", () => {
  it("check A/B versions", () => {
    const measureTest = new Measuresuite(
      width,
      numArgsIn,
      numArgsOut,
      chunkSize,
      bounds,
      sharedObject,
      "fiat_curve25519_carry_square",
    );

    const result = measureTest.measure(functionA, functionB, numBatches, batchSize);

    expect(result).not.toBeFalsy();
    expect(result?.stats?.checkResult).toBe(true);
  });
  it("check A/A versions", () => {
    const measureTest = new Measuresuite(
      width,
      numArgsIn,
      numArgsOut,
      chunkSize,
      bounds,
      sharedObject,
      "fiat_curve25519_carry_square",
    );

    expect(functionA.length).toBe(5363);

    const result = measureTest.measure(functionA, functionA, numBatches, batchSize);
    expect(result).not.toBeFalsy();
    expect(result?.stats?.checkResult).toBe(true);
  });
  describe("throw", () => {
    it("should throw if argwidth does not match bounds width", () => {
      expect(() => {
        new Measuresuite(
          bounds.length + 1,
          numArgsIn,
          numArgsOut,
          chunkSize,
          bounds,
          sharedObject,
          "fiat_curve25519_carry_square",
        );
      }).toThrow();
    });
  });
});
