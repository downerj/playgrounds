#ifndef SHIP_HH
#define SHIP_HH

#include <stdint.h>

class Ship {
public:
  uint16_t y;
  int16_t dy;
  bool alive;
  const uint8_t* bitmap;

  Ship(uint16_t y);
  bool update(void);

private:
  uint8_t explosionState;
};

#endif
