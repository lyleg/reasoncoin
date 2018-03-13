/* borrowed from llama-snake, https://github.com/rdavison/llama-snake*/
let rec range = (a, b) =>
  if (a > b) {
    [];
  } else {
    [a, ...range(succ(a), b)];
  };