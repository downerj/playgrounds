import fs = require('fs');

const FILE_PATH = '../res/words.txt';

let text: Buffer | null;
try {
  text = fs.readFileSync(FILE_PATH);
} catch (ex) {
  process.stderr.write(`Error reading file ${FILE_PATH}\n`);
  process.exit();
}
let characterMap: Record<string, number> = {};
for (let characterCode of text) {
  let character: string = String.fromCharCode(characterCode).toUpperCase();
  if (character.search(/[A-Z]/) !== 0) {
    continue;
  }
  if (!(character in characterMap)) {
    characterMap[character] = 0;
  }
  characterMap[character]++;
}
// Cleanup.
text = null;
console.log(Object.keys(characterMap).sort((lhs: string, rhs: string): number => {
  return characterMap[rhs] - characterMap[lhs];
}).join(''));
