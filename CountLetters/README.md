# Count characters
Ordering alphabetic letters by count in English words list, in multiple languages 

## Setup
You'll need to download an English words text file and put it in the `res/` folder.
You can get one at [https://github.com/dwyl/english-words/blob/master/words.txt](https://github.com/dwyl/english-words/blob/master/words.txt).

## C
```
$ cd c
$ make init
$ make countchars-c
$ bin/countchars-c
```
For debugging:
```
$ make DEBUG=1 countchars-c
```

## JavaScript (NodeJS)
```
$ cd nodejs
$ node countchars.js
```

## Python 3.7+
```
$ cd python
$ python3.7 countchars.py
```

## TypeScript (NodeJS)
```
$ cd nodets
$ tsc src/countchars.ts
$ node dist/countchars.js
```

