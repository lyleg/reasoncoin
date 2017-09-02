let genesisBlock = Reasoncoin.create_genesis_block ();

let blocksToAdd: list int = Utils.range 0 20;

let reasonBlockChain =
  List.fold_left
    (
      fun blockchain _index => {
        let firstBlock = List.nth blockchain 0;
        let newBlock = Reasoncoin.next_block firstBlock;
        [newBlock, ...blockchain]
      }
    )
    [genesisBlock]
    blocksToAdd;

List.iter (fun block => Js.log block) reasonBlockChain;
