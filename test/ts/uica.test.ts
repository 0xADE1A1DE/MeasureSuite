import Measuresuite from "../../src/";
import { functionA, functionB } from "./functions_sq";

Measuresuite.libcheckfunctionssuffix = "clang-AMD";

const describeif = (condition: boolean) => (condition ? describe : describe.skip);

describeif(Measuresuite.uiCAinitialized)("uiCA", () => {
  it("should throw if an unsupported arch is requested", () => {
    expect(() => {
      Measuresuite.measure_uiCA(functionA, functionB, "arch-does-not-exist");
    }).toThrow();
  });

  it("should return -1 as throughput, if the arch does not support instructions", () => {
    // SNB => Sandy bridge.
    const resultuiCA = Measuresuite.measure_uiCA(functionA, functionB, "SNB");

    // It should return a valid object
    expect(resultuiCA).not.toBeFalsy();

    // but estimate the throughput as -1,
    expect(resultuiCA?.throughputA).toBe(-1);
    expect(resultuiCA?.throughputB).toBe(-1);
  });

  it("check uiCA", () => {
    const resultuiCA = Measuresuite.measure_uiCA(functionA, functionB, "CFL");

    expect(resultuiCA).not.toBeFalsy();

    expect(resultuiCA?.throughputA).toBe(39.25);
    expect(resultuiCA?.throughputB).toBe(37);
  });
});
