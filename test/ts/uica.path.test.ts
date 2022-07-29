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

import { describe, expect, it } from "vitest";

import { Measuresuite } from "../../src";
import { functionA, functionB } from "./functions_sq";

describe("uiCA", () => {
  it("should throw if the uica-Path is unset", () => {
    expect(() => {
      Measuresuite.measureUiCA(functionA, functionB, "RKL");
    }).toThrow();
  });
  it("should throw if we set the uica-Path to something non existent", () => {
    expect(() => {
      Measuresuite.setUiCaPath("does not exist.");
      Measuresuite.measureUiCA(functionA, functionB, "RKL");
    }).toThrow();
  });
});
