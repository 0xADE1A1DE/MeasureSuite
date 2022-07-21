import { native_ms } from "../../src/";
describe("native_ms", () => {
  it("should export the native interface with the correct properties", () => {
    expect(native_ms).toBeTruthy();
    expect(native_ms).toHaveProperty("init");
    expect(native_ms).toHaveProperty("measure");
    expect(typeof native_ms.init).toBe("function"); expect(typeof native_ms.measure).toBe("function");
  });
});
