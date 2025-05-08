#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

// Code point of the letter 'A'.
#define A (unsigned int)'A';

int main(void) {
  const char* FILE_PATH = "../res/words.txt";
 
  // Stores the count for each character in the file.
  unsigned int characterCounts[26] = {0};

  FILE* file = fopen(FILE_PATH, "r");
  if (file == NULL) {
    fprintf(stderr, "Error reading file %s\n", FILE_PATH);
    return 1;
  }

  while (true) {
    // Get the code point (signed) of the next character.
    int c = fgetc(file);
    if (c == EOF) {
      break;
    }
    // Skip non-letter characters.
    if (!isalpha(c)) {
      continue;
    }
    c = toupper(c);
    // Get the alphabet-index (0-25) of the letter.
    unsigned int index = c - A;
    characterCounts[index]++;
  }
  fclose(file);
  file = NULL;

  // Stores the letters in sorted order.
  unsigned char charactersSorted[26] = {};
  for (unsigned int i = 0; i < 26; i++) {
    // Represents the index where the letter will go, after sorting.
    unsigned int newIndex = 0;
    // Determine how many letters are "ahead of" (greater than) the current one in count.
    // The resulting number is the index where the letter belongs.
    // If the letters are equal in count, then alphabetic order is assumed.
    for (unsigned int j = 0; j < 26; j++) {
      if (characterCounts[j] > characterCounts[i]) {
        newIndex++;
      }
    }
    unsigned char letter = i + A;
    charactersSorted[newIndex] = letter;

#ifdef DEBUG
    printf(
      "DEBUG> %c (Count: %8d) [Index: %2d]\n",
      letter,
      characterCounts[i],
      newIndex
    );
#endif
  }

#ifdef DEBUG
  printf("\n");
#endif

  for (unsigned int l = 0; l < 26; l++) {
    printf("%c", charactersSorted[l]);
  }
  printf("\n");

  return 0;
}
