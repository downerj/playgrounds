#include <Arduboy2.h>

#include "game.h"

Arduboy2 arduboy;
Game game(arduboy);

#define FRAMERATE 255

void setup(void) {
  arduboy.begin();
  arduboy.setFrameRate(FRAMERATE);
}

#define DO_CLEAR true

void loop(void) {
  if (!arduboy.nextFrame()) {
    return;
  }

  arduboy.pollButtons();

  game.handleInput();
  game.handleCollisions();
  game.update();
  game.draw();

  arduboy.display(DO_CLEAR);
}
