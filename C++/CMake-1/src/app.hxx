#ifndef APP_HXX
#define APP_HXX

#include <glad/gl.h>
#include <SDL3/SDL_init.h>

namespace my {

class Application {
public:
  Application();
  ~Application() noexcept;

  Application(const Application&) = delete;
  Application(Application&&) = delete;
  auto operator=(const Application&) -> Application& = delete;
  auto operator=(Application&&) -> Application& = delete;

  auto getWindow() const -> SDL_Window*;
  auto getContext() const -> SDL_GLContext;
  auto handleEvents() -> bool;
  auto render() -> void;

private:
  SDL_Window* window;
  SDL_GLContext context;

  auto cleanUpWindow() noexcept -> void;
  auto cleanUpContext() noexcept -> void;
  auto cleanUpAll() noexcept -> void;
};

}

#endif
