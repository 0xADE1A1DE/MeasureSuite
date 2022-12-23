import typescript from "@rollup/plugin-typescript";
import copy from "rollup-plugin-copy";

import dts from "rollup-plugin-dts";

const external = ["child_process", "fs", "lodash-es", "measureaddon", "module", "os", "path"];
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
