external sha256 : string => string = "sha256" [@@bs.module "js-sha256"];

open Jest;

let genesisBlock = Reasoncoin.createGenesisBlock ();

let blocksToAdd: list int = Utils.range 0 20;

let reasonBlockChain =
  List.fold_left
    (
      fun blockchain _index => {
        let firstBlock = List.nth blockchain 0;
        let newBlock = Reasoncoin.nextBlock firstBlock;
        [newBlock, ...blockchain]
      }
    )
    [genesisBlock]
    blocksToAdd;

let numCoins = List.length reasonBlockChain;

let _ =
  describe
    "Iterate through each coin while checking the computed hash from n to the hash recorded in n+1"
    (
      fun () =>
        for blockIndex in (numCoins - 1) downto 1 {
          Expect.(
            test
              ("Hashes should match, checking " ^ string_of_int blockIndex)
              (
                fun () => {
                  let block = List.nth reasonBlockChain blockIndex;
                  let nextCoin = List.nth reasonBlockChain (blockIndex - 1);
                  let blockCalculatedHash =
                    Reasoncoin.createHash
                      index::block.index
                      data::block.data
                      currentTime::block.timestamp
                      previousHash::block.previousHash;
                  expect nextCoin.previousHash |> toBe blockCalculatedHash
                }
              )
          )
        }
    );

let _ =
  describe
    "Change data and verify the hashes no longer match"
    (
      fun () => {
        let block = List.nth reasonBlockChain (numCoins - 1);
        let nextBlock = List.nth reasonBlockChain (numCoins - 2);
        let expectedBlockHash = nextBlock.previousHash;
        let modifiedBlock = {...block, data: "He Hax"};
        let modifiedBlockHash =
          Reasoncoin.createHash
            index::modifiedBlock.index
            data::modifiedBlock.data
            currentTime::modifiedBlock.timestamp
            previousHash::modifiedBlock.previousHash;
        Expect.(
          test
            "Hashes should no longer match"
            (
              fun () =>
                expect modifiedBlockHash |> not_ |> toBe expectedBlockHash
            )
        )
      }
    );
