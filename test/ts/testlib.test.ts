import Measuresuite from "../../src/";
import { width, numArgsIn, numArgsOut, functionA, functionB } from "./functions";
import { unlinkSync } from "fs";
import { compileTestlib } from "./test-helper";

const chunkSize = 16;

beforeAll(() => {
  Measuresuite.libcheckfunctionssuffix = "test_lib";
  compileTestlib(Measuresuite.libcheckfunctionsFilename);
});

afterAll(() => {
  unlinkSync(Measuresuite.libcheckfunctionsFilename);
});

describe("general with test_lib", () => {
  it("should accept an empty bounds array ", () => {
    expect(() => {
      new Measuresuite(width, numArgsIn, numArgsOut, chunkSize, [], "increment");
    }).not.toThrow();
  });

  it("should throw if argwidth does not match bounds width", () => {
    expect(() => {
      new Measuresuite(width + 1, numArgsIn, numArgsOut, chunkSize, ["0xffffffffffffffff"], "increment");
    }).toThrow();
  });
  it("should measure", () => {
    const ms = new Measuresuite(width, numArgsIn, numArgsOut, chunkSize, ["0xffffffffffffffff"], "increment");
    const res = ms.measure(functionA, functionB, 10, 10);
    expect(res).toBeTruthy();
    expect(res?.stats.checkResult).toBe(true);
  });
});
