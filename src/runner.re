let genesisBlock = Reasoncoin.createGenesisBlock();

let blocksToAdd: list(int) = Utils.range(0, 20);

let reasonBlockChain =
  List.fold_left(
    (blockchain, _index) => {
      let firstBlock = List.nth(blockchain, 0);
      let newBlock = Reasoncoin.nextBlock(firstBlock);
      [newBlock, ...blockchain];
    },
    [genesisBlock],
    blocksToAdd,
  );

List.iter(block => Js.log(block), reasonBlockChain);