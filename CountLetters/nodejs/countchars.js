#!/usr/bin/env node

const fs = require('fs');

const FILE_PATH = '../res/words.txt';

let text;
try {
  text = fs.readFileSync(FILE_PATH);
} catch (ex) {
  process.stderr.write(`Error reading file ${FILE_PATH}\n`);
  process.exit();
}
let characterMap = {};
for (let characterCode of text) {
  let character = String.fromCharCode(characterCode).toUpperCase();
  if (character.search(/[a-zA-Z]/) !== 0) {
    continue;
  }
  if (!(character in characterMap)) {
    characterMap[character] = 0
  }
  characterMap[character]++;
}
text = null;
console.log(Object.keys(characterMap).sort((lhs, rhs) => {
  return characterMap[rhs] - characterMap[lhs];
}).join(''));
