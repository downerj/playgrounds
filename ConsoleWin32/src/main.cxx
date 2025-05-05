#include "debug.hxx"

int main(int, char**) {
  LOG_FG(Cyan);
  LOG("Hello, there!\n");
  LOG_FG_ERROR(Yellow);
  LOG_ERROR("This is a warning.\n");
  LOG_FG_ERROR(Red);
  LOG_ERROR("This is an error.\n");
  LOG_FG(Magenta);
  LOG_BG(Blue);
  LOG("Custom colors!\n");
  LOG_RESET();
  LOG_RESET_ERROR();
  LOG("Goodbye.\n");
}
