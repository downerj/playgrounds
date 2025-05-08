#!/usr/bin/env nodejs
// Run: node iife.js

const s = 'Bye.';
console.log((() => {
  const s = 'Hello!';
  return s;
})());
console.log(s);
