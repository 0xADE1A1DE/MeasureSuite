import Measuresuite from "../../src/";
import { width, numArgsIn, numArgsOut, functionA, functionB } from "./functions";
import { unlinkSync } from "fs";
import { compileTestlib } from "./test-helper";

describe("general with test_lib", () => {
  it("should get the right stats", () => {
    // We need to tell Measuresuite the suffix of how the so-file-will end.
    Measuresuite.libcheckfunctionssuffix = "test_lib-plus1";

    // Then, measuresuite's libcheckfunctionsFilename will tell us where to compile our all_lib.c file to.
    compileTestlib(Measuresuite.libcheckfunctionsFilename);

    // set up as the bound  (to Binary-and the inpot and results with)
    const bounds = ["0xffffffffffffffff"];

    // symbol in the shared object
    const symbol = "increment";

    // passed to Assemblyline for the stats of the chunk-breaking instructions
    const chunkSize = 16;

    // create a Measuresuite object
    const ms = new Measuresuite(width, numArgsIn, numArgsOut, chunkSize, bounds, symbol);

    // number of batches: each function will have at least this many time-measurements
    const nob = 50;

    // how many times the functionA/B are called within a loop. Short functions need bigger
    // numbers in order to have sensible measurements
    const batchSize = 10000;

    // measure
    const measurementResult = ms.measure(functionA, functionB, batchSize, nob);
    expect(measurementResult).toBeTruthy();
    if (!measurementResult) {
      // this is more or less for typescript tooling to assert, that measurementResult is not nullish
      throw new Error("measurementResult is nullish. This should not happen.");
    }

    // minimum of both must be nob
    // measurementResult contains the general 'stats'
    const stats = measurementResult.stats;
    expect(stats).toBeTruthy();

    // and the timings itself as an array of triples (Is that a word? If not, it should be IMO.)
    const times = measurementResult.times;
    expect(times).toBeTruthy();

    // Lets have a look at the stats first:

    // checkResult is true, if the data written to the out-pointer is the
    // same for the symbol in the shared object and for the called function
    expect(stats.checkResult).toBe(true);

    // countA and countB refer to how many data points there exist for each respective function
    // must be at least nob many for both.
    expect(stats.countA).toBeGreaterThanOrEqual(nob);
    expect(stats.countB).toBeGreaterThanOrEqual(nob);

    // and the smaller one must be exactly nob
    expect(Math.min(stats.countA, stats.countB)).toBe(nob);

    // the chunks. Function a, can be assembled in one chunk, hence there is no breaks
    expect(stats.chunksA).toBe(0);
    // the chunks. Function b, is bigger and uses instructions at certain addresses, such that it breaks chunks with three instructions
    expect(stats.chunksB).toBe(3);

    // just confirming the bs and nob.
    expect(stats.batchSize).toBe(batchSize);
    expect(stats.numBatches).toBe(nob);

    // this gives the entire runtime for all batches in milliseconds... Really depends on the system
    expect(stats.runtime).toBeGreaterThan(0);

    // as we run randomly, show here, in which order that randomness actually decided.
    // its of the form, Where in practice, after each execution of A or B, one batch of check function is executed.
    expect(stats.runOrder).toMatch(/[ab]+/);
    // i.e. aabab is short for running acacbcacbc

    // we report the timings in the times property
    // each entry in times is of the form [CYCLES_A, -1, CYCLES_C] or [-1, CYCLES_B, CYCLES_C], -1 depicting that in this run, the other one was measured.

    // because this is simple small function and we want this to work on all machines, we are very bold with our claims that we check here.
    // Hence we sum all cycles up
    const [timeForAllA, timeForAllB] = times.reduce(
      ([totalA, totalB], [a, b, _c]) => {
        if (a > 0) totalA += a;
        if (b > 0) totalB += b;
        return [totalA, totalB];
      },
      [0, 0], // initialize with 0 cycles each
    );

    // that's a bit risky though... As it depends on the machine
    expect(timeForAllB).toBeGreaterThan(timeForAllA); // But we just cross our fingers here.

    // cleanup for the testfile lib
    unlinkSync(Measuresuite.libcheckfunctionsFilename);
  });
});
