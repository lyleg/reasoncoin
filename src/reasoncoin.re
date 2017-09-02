/* Inspired by https://medium.com/crypto-currently/lets-build-the-tiniest-blockchain-e70965a248b */
external sha256 : string => string = "sha256" [@@bs.module "js-sha256"];

external currentTime : unit => int = "Date.now" [@@bs.val];

/* Define what a reasoncoin block is*/
type block = {
  index: int,
  timestamp: int,
  data: string,
  previous_hash: string,
  hash: string
};

type blockchain = list block;

/*
 function that returns a block record
 */
let blockBuilder ::index ::previous_hash => {
  let currentTime = currentTime ();
  let data = "Hey! I'm block " ^ string_of_int index;
  {
    index,
    previous_hash,
    timestamp: currentTime,
    data,
    hash:
      sha256 (
        string_of_int index ^ string_of_int currentTime ^ data ^ previous_hash
      )
  }
};

/*
 Manually construct a block with
 index zero and arbitrary previous hash
 */
let create_genesis_block () => blockBuilder index::0 previous_hash::"0";

let next_block last_block => {
  let newIndex = last_block.index + 1;
  blockBuilder index::newIndex previous_hash::last_block.hash
};
