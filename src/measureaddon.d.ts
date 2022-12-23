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

// c interface
declare module "measureaddon" {
  function init(argWidth: number, numArgIn: number, numArgOut: number): void;

  function load_asm_string(assembly: string): number; // returns id of where the function has been loaded into
  function load_asm_file(path: string): number;
  function load_bin_file(path: string): number;
  function load_elf_file(path: string, symbol?: string): number;
  function load_shared_object_file(path: string, symbol: string): number;

  function enable_checking(): void;
  function enable_chunk_counting(chunkSize: number): void;
  function set_bounds(bounds: BigUint64Array): void;

  function measure(batchSize: number, numBatches: number): string;
}
