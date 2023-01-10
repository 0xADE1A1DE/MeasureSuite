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
import typescript from "@rollup/plugin-typescript";
import copy from "rollup-plugin-copy";

import dts from "rollup-plugin-dts";

const external = ["fs", "module", "path"];
export default [
  {
    input: "src/index.ts",
    output: {
      dir: "dist",
      format: "es",
    },
    external,
    plugins: [
      typescript(),
      copy({
        targets: [
          {
            src: ["build/Release/measuresuite.node"],
            dest: "./dist",
          },
        ],
      }),
    ],
  },
  {
    input: "./dist/dts/index.d.ts",
    output: [{ file: "dist/index.d.ts", format: "es" }],
    plugins: [dts()],
  },
];
