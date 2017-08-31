/* Inspired by https://medium.com/crypto-currently/lets-build-the-tiniest-blockchain-e70965a248b */
external sha256 : string => string = "sha256" [@@bs.module "js-sha256"];

/* borrowed from llama-snake, https://github.com/rdavison/llama-snake*/
let rec range a b =>
  if (a > b) {
    []
  } else {
    [a, ...range (succ a) b]
  };

/* Define what a reasoncoin block is*/
type block = {
  index: int,
  timestamp: string,
  data: string,
  previous_hash: string,
  hash: string
};

type blockchain = list block;

/*
 function that returns a block record
 */
let blockBuilder ::index ::timestamp ::data ::previous_hash ::hash => {
  index,
  previous_hash,
  timestamp: "now",
  data: "Hey! I'm block " ^ string_of_int index,
  hash: sha256 (string_of_int index ^ timestamp ^ data ^ hash ^ previous_hash)
};

/*
 Manually construct a block with
 index zero and arbitrary previous hash
 */
let create_genesis_block () =>
  blockBuilder
    index::0
    timestamp::"1234"
    data::"Genesis Block"
    previous_hash::"0"
    hash::"0";

let next_block last_block => {
  let newIndex = last_block.index + 1;
  let data = "Hey! I'm block " ^ string_of_int newIndex;
  blockBuilder
    index::newIndex
    timestamp::"now"
    ::data
    hash::last_block.hash
    previous_hash::last_block.hash
};

let genesisBlock = create_genesis_block ();

let blocksToAdd: list int = range 0 20;

let reasonBlockChain =
  List.fold_left
    (
      fun blockchain _index => {
        let firstBlock = List.nth blockchain 0;
        let newBlock = next_block firstBlock;
        [newBlock, ...blockchain]
      }
    )
    [genesisBlock]
    blocksToAdd;

List.iter (fun block => Js.log block) reasonBlockChain;
