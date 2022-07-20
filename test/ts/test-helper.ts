import { resolve } from "path";
import { existsSync } from "fs";
import { execSync } from "child_process";

export function compileTestlib(outfile: string) {
  const testlib_C = resolve(__dirname, "..", "all_lib.c");
  compile(testlib_C, outfile);
}

export function compileFiat(outile: string) {
  const fiat_C = resolve(__dirname, "..", "all_fiat.c");
  compile(fiat_C, outile);
}
function compile(infile: string, out: string) {
  if (!existsSync(out)) {
    const cc = process.env.CC ?? "gcc";
    const cmd = `${cc} ${infile} -O3 -fPIC -fpie -shared -o ${out}`;
    console.debug("compiling... " + cmd);
    execSync(cmd);
  }
}
