/* Inspired by https://medium.com/crypto-currently/lets-build-the-tiniest-blockchain-e70965a248b */
[@bs.module "js-sha256"] external sha256 : string => string = "sha256"; /* Define what a reasoncoin block is*/

type block = {
  index: int,
  timestamp: float,
  data: string,
  previousHash: string,
  hash: string,
};

type blockchain = list(block);

let createHash = (~index, ~currentTime, ~data, ~previousHash) =>
  sha256(
    string_of_int(index)
    ++ string_of_float(currentTime)
    ++ data
    ++ previousHash,
  ); /*
 function that returns a block record
 */

let blockBuilder = (~index, ~previousHash) => {
  let currentTime = Js.Date.now();
  let data = "Hey! I'm block " ++ string_of_int(index);
  let hash = createHash(~index, ~currentTime, ~data, ~previousHash);
  {index, previousHash, timestamp: currentTime, data, hash};
}; /*
 Manually construct a block with
 index zero and arbitrary previous hash
 */

let createGenesisBlock = () => blockBuilder(~index=0, ~previousHash="0");

let nextBlock = lastBlock => {
  let newIndex = lastBlock.index + 1;
  blockBuilder(~index=newIndex, ~previousHash=lastBlock.hash);
};