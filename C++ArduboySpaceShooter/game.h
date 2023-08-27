#ifndef GAME_HH
#define GAME_HH

#include <stdint.h>

#include <Arduboy2.h>

#include "ship.h"

class Game {
public:
  Game(Arduboy2& arduboy);
  void handleInput(void);
  void handleCollisions(void);
  void update(void);
  void draw(void);

private:
  Arduboy2& arduboy;
  Ship* ship;
  uint8_t buttonsState;
  uint16_t playerCooldown;
};

#endif
