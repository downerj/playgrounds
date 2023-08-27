#include "game.h"
#include "ship.h"
#include "bitmaps.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define PLAYABLE_SCREEN_LEFT 0
#define PLAYABLE_SCREEN_TOP 0
#define PLAYABLE_SCREEN_RIGHT SCREEN_WIDTH
#define PLAYABLE_SCREEN_BOTTOM SCREEN_HEIGHT
#define PLAYABLE_SCREEN_WIDTH (PLAYABLE_SCREEN_RIGHT - PLAYABLE_SCREEN_LEFT)
#define PLAYABLE_SCREEN_HEIGHT (PLAYABLE_SCREEN_BOTTOM - PLAYABLE_SCREEN_TOP)
#define SHIP_START_Y (PLAYABLE_SCREEN_BOTTOM * 0.5) - (SPRITE_HEIGHT * 0.5)
#define PLAYER_COOLDOWN_START 300

Game::Game(Arduboy2& arduboy) :
  arduboy(arduboy),
  ship(new Ship(SHIP_START_Y)),
  buttonsState(0),
  playerCooldown(0)
{}

#define SHIP_VELOCITY 1

void Game::handleInput(void) {
  buttonsState = arduboy.buttonsState();

  if ((ship != nullptr) && ship->alive) {
    if (buttonsState & A_BUTTON) {
      ship->alive = false;
    } else {
      if (buttonsState & UP_BUTTON) {
        ship->dy = -SHIP_VELOCITY;
      } else if (buttonsState & DOWN_BUTTON) {
        ship->dy = +SHIP_VELOCITY;
      } else {
        ship->dy = 0;
      }
    }
  }
}

void Game::handleCollisions(void) {
  if ((ship != nullptr) && ship->alive) {
    if ((ship->dy < 0) && (ship->y <= PLAYABLE_SCREEN_TOP)) {
      ship->dy = 0;
      ship->y = PLAYABLE_SCREEN_TOP;
    } else if ((ship->dy > 0) && (ship->y + SPRITE_HEIGHT >= PLAYABLE_SCREEN_BOTTOM)) {
      ship->dy = 0;
      ship->y = PLAYABLE_SCREEN_BOTTOM - SPRITE_HEIGHT;
    }
  }
}

void Game::update(void) {
  if ((ship != nullptr) && !ship->update()) {
    ship = nullptr;
    playerCooldown = PLAYER_COOLDOWN_START;
  }
  if (ship == nullptr) {
    if (playerCooldown > 0) {
      playerCooldown--;
    } else {
      ship = new Ship(SHIP_START_Y);
    }
  }
}

void Game::draw(void) {
  if (ship != nullptr) {
    arduboy.drawBitmap(
      PLAYABLE_SCREEN_LEFT,
      ship->y,
      ship->bitmap,
      SPRITE_WIDTH,
      SPRITE_HEIGHT,
      WHITE
    );
  }
}
