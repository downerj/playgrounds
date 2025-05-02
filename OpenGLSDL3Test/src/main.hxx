#include <glad/gl.h>

#include <SDL3/SDL.h>
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

/**
 * Declarations.
 */

#ifdef _DEBUG
# define DEBUG
#endif // _DEBUG

#ifdef DEBUG
#include <iostream>
# define LOG(x) do { std::cout << x; } while (false);
# define LOG_ERROR(x) do { std::cerr << x; } while (false);
#else
# define LOG(x)
# define LOG_ERROR(x)
#endif // DEBUG

namespace {

#ifdef DEBUG
auto debugMessageCallbackGL(
  GLenum source, GLenum type, GLuint id, GLenum severity,
  GLsizei length, const GLchar* message, const GLvoid* userParam
) -> void;
#endif // DEBUG

class Application {
public:
  Application() = delete;
  Application(SDL_Window* window, SDL_GLContext context);
  Application(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(const Application&) = delete;
  Application& operator=(Application&&) = delete;
  ~Application();

  // auto getWindow() const -> const SDL_Window*;
  auto getWindow() -> SDL_Window*;

private:
  SDL_Window* window;
  SDL_GLContext context;
};

} // namespace

auto SDL_AppInit(void** appState, int argc, char** argv) -> SDL_AppResult;
auto SDL_AppIterate(void* appState) -> SDL_AppResult;
auto SDL_AppEvent(void* appState, SDL_Event* event) -> SDL_AppResult;
auto SDL_AppQuit(void* appState, SDL_AppResult result) -> void;
