import typescript from "@rollup/plugin-typescript";

const external = ["lodash-es", "measure-addon", "child_process", "fs", "os", "path"];
export default [
  {
    input: "src/index.ts",
    output: {
      dir: "dist",
      format: "es",
    },
    external,
    plugins: [typescript()],
  },
];
