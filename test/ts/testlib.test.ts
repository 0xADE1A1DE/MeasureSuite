import Measuresuite from "../../src/";
import { width, numArgsIn, numArgsOut, functionA, functionB } from "./functions";
import { unlinkSync } from "fs";
import { compileTestlib } from "./test-helper";

const chunkSize = 16;
describe("general with test_lib", () => {
  afterAll(() => {
    unlinkSync(Measuresuite.libcheckfunctionsFilename);
  });

  it("should accept an empty bounds array ", () => {
    expect(() => {
      Measuresuite.libcheckfunctionssuffix = "test_lib";
      compileTestlib(Measuresuite.libcheckfunctionsFilename);
      new Measuresuite(width, numArgsIn, numArgsOut, chunkSize, [], "increment");
    }).not.toThrow();
  });

  it("should throw if argwidth does not match bounds width", () => {
    expect(() => {
      Measuresuite.libcheckfunctionssuffix = "test_lib";
      compileTestlib(Measuresuite.libcheckfunctionsFilename);
      new Measuresuite(width + 1, numArgsIn, numArgsOut, chunkSize, ["0xffffffffffffffff"], "increment");
    }).toThrow();
  });
  it("should measure", () => {
    Measuresuite.libcheckfunctionssuffix = "test_lib";
    compileTestlib(Measuresuite.libcheckfunctionsFilename);
    const ms = new Measuresuite(width, numArgsIn, numArgsOut, chunkSize, ["0xffffffffffffffff"], "increment");
    const res = ms.measure(functionA, functionB, 10, 10);
    expect(res).toBeTruthy();
    expect(res?.stats.checkResult).toBe(true);
  });
});
