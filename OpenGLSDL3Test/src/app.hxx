#ifndef APP_HXX
#define APP_HXX

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>

class Application {
public:
  Application();
  Application(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(const Application&) = delete;
  Application& operator=(Application&&) = delete;
  ~Application();

  auto onIterate() -> void;
  auto onEvent(SDL_Event* event) -> bool;

private:
  SDL_Window* _window{nullptr};
  SDL_GLContext _context{nullptr};
};

#endif // APP_HXX
