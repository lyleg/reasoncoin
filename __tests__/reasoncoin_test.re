external sha256 : string => string = "sha256" [@@bs.module "js-sha256"];

open Jest;

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

let numCoins = List.length reasonBlockChain;

let firstBlock = List.nth reasonBlockChain (numCoins - 1);

let secondBlock = List.nth reasonBlockChain (numCoins - 2);

let firstBlockExpectedHash = secondBlock.previous_hash;

let firstBlockCalculatedHash =
  sha256 (
    string_of_int firstBlock.index ^
    string_of_int firstBlock.timestamp ^
    firstBlock.data ^ firstBlock.previous_hash
  );

/*expect secondBlock previous hash to equal re-computed hash */
/*check hash references*/
let _ =
  describe
    "Expect hashes to match"
    (
      fun () =>
        Expect.(
          test
            "Hashes should match"
            (
              fun () =>
                expect firstBlockExpectedHash |> toBe firstBlockCalculatedHash
            )
        )
    );
