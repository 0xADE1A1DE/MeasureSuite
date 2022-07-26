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

import { Measuresuite } from "../../src/";
import { functionA, functionB } from "./functions_sq";

Measuresuite.libcheckfunctionssuffix = "clang-AMD";

const describeif = (condition: boolean) => (condition ? describe : describe.skip);

describeif(Measuresuite.uiCAinitialized)("uiCA", () => {
  it("should throw if an unsupported arch is requested", () => {
    expect(() => {
      Measuresuite.measure_uiCA(functionA, functionB, "arch-does-not-exist");
    }).toThrow();
  });

  it("should return -1 as throughput, if the arch does not support instructions", () => {
    // SNB => Sandy bridge.
    const resultuiCA = Measuresuite.measure_uiCA(functionA, functionB, "SNB");

    // It should return a valid object
    expect(resultuiCA).not.toBeFalsy();

    // but estimate the throughput as -1,
    expect(resultuiCA?.throughputA).toBe(-1);
    expect(resultuiCA?.throughputB).toBe(-1);
  });

  it("check uiCA", () => {
    const resultuiCA = Measuresuite.measure_uiCA(functionA, functionB, "CFL");

    expect(resultuiCA).not.toBeFalsy();

    expect(resultuiCA?.throughputA).toBe(39.25);
    expect(resultuiCA?.throughputB).toBe(37);
  });
});
