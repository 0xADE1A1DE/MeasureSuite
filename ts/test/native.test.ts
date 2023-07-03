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

import { describe, expect, it } from "vitest";

import { native_ms } from "../src/";
describe("native_ms", () => {
  it("should export the native interface with the correct properties", () => {
    expect(native_ms).toBeTruthy();

    const props = [
      "init",
      "load_asm_string",
      "load_asm_file",
      "load_bin_file",
      "load_elf_file",
      "load_shared_object_file",
      "unload_all",
      "unload_last",
      "enable_checking",
      "enable_chunk_counting",
      "set_bounds",
      "measure",
      "destroy",
      "get_timer",
    ] as Array<keyof typeof native_ms>;
    props.forEach((property) => {
      expect(native_ms).toHaveProperty(property);
      expect(typeof native_ms[property]).toBe("function");
    });
  });
});
