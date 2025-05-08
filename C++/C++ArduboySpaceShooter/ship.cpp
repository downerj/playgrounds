#include "ship.h"
#include "bitmaps.h"

Ship::Ship(uint16_t y) :
  y(y),
  dy(0),
  alive(true),
  bitmap(SHIP_BITMAP),
  explosionState(0)
{}

#define EXPLOSION_INTERVAL 15
#define EXPLOSION_MAX_LOOPS 4
#define EXPLOSION_MAX (EXPLOSION_INTERVAL * NUM_EXPLOSION_BITMAPS * EXPLOSION_MAX_LOOPS)

bool Ship::update(void) {
  if (alive) {
    y += dy;
  } else {
    uint8_t bitmapIndex = (explosionState / EXPLOSION_INTERVAL) % NUM_EXPLOSION_BITMAPS;
    bitmap = EXPLOSION_BITMAPS[bitmapIndex];
    if (++explosionState >= EXPLOSION_MAX) {
      return false;
    }
  }

  return true;
}
