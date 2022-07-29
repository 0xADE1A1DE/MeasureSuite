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

import { native_ms } from "../../src/";
describe("native_ms", () => {
  it("should export the native interface with the correct properties", () => {
    expect(native_ms).toBeTruthy();
    expect(native_ms).toHaveProperty("init");
    expect(native_ms).toHaveProperty("measure");
    expect(typeof native_ms.init).toBe("function");
    expect(typeof native_ms.measure).toBe("function");
  });
});
