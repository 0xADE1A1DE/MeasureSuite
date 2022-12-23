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

import { resolve } from "path";
import { existsSync } from "fs";
import { execSync } from "child_process";
import { expect } from "vitest";

export function compileTestlib(outfile: string) {
  const testlib_C = resolve(process.cwd(), "test", "test_data", "all_lib.c");
  compile(testlib_C, outfile);
}

export function compileFiat(outile: string) {
  const fiat_C = resolve(process.cwd(), "test", "all_fiat.c");
  compile(fiat_C, outile);
}

function compile(infile: string, out: string) {
  if (!existsSync(out)) {
    const cc = process.env.CC ?? "gcc";
    const cmd = `${cc} ${infile} -O3 -fPIC -fpie -shared -o ${out}`;
    execSync(cmd);
  }
}
export function expectNotNull<T>(a: T): asserts a is NonNullable<T> {
  expect(a).not.toBe(null);
}
