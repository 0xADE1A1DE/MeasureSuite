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

  function loadAsmString(assembly: string): string;
  function loadAsmFile(path: string): string;
  function loadBinFile(path: string): string;
  function loadElfFile(path: string, symbol?: string): string;
  function loadSharedObjectFile(path: string, symbol: string): string;

  function enableChecking(): void;
  function enableChunkCounting(chunkSize: number): void;
  function setBounds(bounds: BigUint64Array): void;

  function measure(batchSize: number, numBatches: number): string;
}
