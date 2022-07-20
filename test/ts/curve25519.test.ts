import { unlinkSync } from "fs";

import Measuresuite from "../../src/";
import { bounds, functionA, functionB, width, numArgsIn, numArgsOut } from "./functions_sq";
import { numBatches, batchSize } from "./constants";
import { compileFiat } from "./test-helper";

const chunkSize = 16;

it("sanity check", () => {
  expect(functionA.length).toBe(5363);
  expect(functionB.length).toBe(4900);
});

describe("measure curve25519-sq", () => {
  const SUFF = "fiat";
  afterAll(() => {
    unlinkSync(Measuresuite.libcheckfunctionsFilename);
  });
  it("check A/B versions", () => {
    Measuresuite.libcheckfunctionssuffix = SUFF;
    compileFiat(Measuresuite.libcheckfunctionsFilename);
    const measureTest = new Measuresuite(
      width,
      numArgsIn,
      numArgsOut,
      chunkSize,
      bounds,
      "fiat_curve25519_carry_square",
    );

    const result = measureTest.measure(functionA, functionB, numBatches, batchSize);

    expect(result).not.toBeFalsy();
    expect(result!.stats?.checkResult).toBe(true);
  });
  it("check A/A versions", () => {
    Measuresuite.libcheckfunctionssuffix = SUFF;
    compileFiat(Measuresuite.libcheckfunctionsFilename);
    const measureTest = new Measuresuite(
      width,
      numArgsIn,
      numArgsOut,
      chunkSize,
      bounds,
      "fiat_curve25519_carry_square",
    );

    expect(functionA.length).toBe(5363);

    const result = measureTest.measure(functionA, functionA, numBatches, batchSize);
    expect(result).not.toBeFalsy();
    expect(result!.stats?.checkResult).toBe(true);
  });
  describe("throw", () => {
    it("should throw if argwidth does not match bounds width", () => {
      expect(() => {
        Measuresuite.libcheckfunctionssuffix = SUFF;
        compileFiat(Measuresuite.libcheckfunctionsFilename);
        new Measuresuite(
          bounds.length + 1,
          numArgsIn,
          numArgsOut,
          chunkSize,
          bounds,
          "fiat_curve25519_carry_square",
        );
      }).toThrow();
    });
  });
});
