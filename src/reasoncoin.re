/* Inspired by https://medium.com/crypto-currently/lets-build-the-tiniest-blockchain-e70965a248b */
external sha256 : string => string = "sha256" [@@bs.module "js-sha256"];

/*type data = {
    fromAddress: string,
    amount: int,
    toAddress: string
  };
  */
/* Define what a reasoncoin block is, can I type the data better while still storing it as json?*/
type block = {
  index: int,
  timestamp: float,
  data: Js.Json.t,
  previousHash: string,
  hash: string
};

type blockchain = list block;

let createHash ::index ::currentTime ::data ::previousHash => {
  let dataString = Js.Json.stringify data;
  sha256 (
    string_of_int index ^
    string_of_float currentTime ^ dataString ^ previousHash
  )
};

/*
 function that returns a block record
 */
let blockBuilder ::index ::previousHash => {
  let currentTime = Js.Date.now ();
  let data =
    Json.Encode.(
      object_ [
        ("toAddress", string "toAddyHere"),
        ("fromAddress", string "fromAddyHere"),
        ("amount", int 1)
      ]
    );
  let hash = createHash ::index ::currentTime ::data ::previousHash;
  {index, previousHash, timestamp: currentTime, data, hash}
};

/*
 Manually construct a block with
 index zero and arbitrary previous hash
 */
let createGenesisBlock () => blockBuilder index::0 previousHash::"0";

let nextBlock lastBlock => {
  let newIndex = lastBlock.index + 1;
  blockBuilder index::newIndex previousHash::lastBlock.hash
};

let proof_of_work last_proof => {
  /* Create a variable that we will use to find
     our next proof of work*/
  let incrementor = ref (last_proof + 1);
  /* Keep incrementing the incrementor until
     it's equal to a number divisible by 9
     and the proof of work of the previous
     block in the chain*/
  while (not (!incrementor mod 9 === 0 && !incrementor mod last_proof === 0)) {
    incrementor := !incrementor + 1
  };
  /* Once that number is found,
     we can return it as a proof
     of our work*/
  incrementor
};
