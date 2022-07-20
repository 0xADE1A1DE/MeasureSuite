// c interface
declare module "measure-addon" {
  function measuresuite_init(
    argWidth: number,
    numArgIn: number,
    numArgOut: number,
    chunkSize: number,
    bounds: BigUint64Array,
    libCheckFunctionsFilename: string,
    checkFunctionSymbolname: string,
  ): void;
  function measuresuite_measure(
    functionA: string,
    functionB: string,
    batchSize: number,
    numBatches: number,
  ): string;
}
