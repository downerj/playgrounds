#!/usr/bin/env python3

import sys
from typing import Any, Dict, List, Tuple

FILE_PATH = "../res/words.txt"

def key_function(item: Tuple[str, int]) -> int:
    return item[1]


character_map: Dict[str, int] = {}
try:
    with open(FILE_PATH) as file:
        character = None
        while True:
            character = file.read(1)
            if len(character) == 0:
                break
            elif not character.isalpha():
                continue
            character = character.upper()
            if character not in character_map:
                character_map[character] = 0
            character_map[character] += 1
except:
    print(f"Error reading file {FILE_PATH}", file=sys.stderr)
    exit(1)
characters_sorted: List[Tuple[str, int]] = sorted(
  character_map.items(),
  key=key_function,
  reverse=True
)
print("".join(item[0] for item in characters_sorted))
