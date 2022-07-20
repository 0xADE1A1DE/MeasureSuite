import Measuresuite from "../../src/";
import { width, numArgsIn, numArgsOut } from "./functions";

const chunkSize = 16;

describe("general", () => {
  it("should throw if trying to read libcheckfunctionsFilename without setting it first", () => {
    expect(() => Measuresuite.libcheckfunctionsFilename).toThrow();
  });
  it("should throw if the file cannot be found", () => {
    expect(() => {
      Measuresuite.libcheckfunctionssuffix = "does-not-exist.so";
      new Measuresuite(width, numArgsIn, numArgsOut, chunkSize, [], "does-not-matter");
    }).toThrow();
  });
});
