#include "main.hxx"

#include <exception>

#include <SDL3/SDL_main.h>

#include "app.hxx"
#include "debug.hxx"

/**
 * Defintions.
 */

auto SDL_AppInit(void** appState, int, char**) -> SDL_AppResult {
  try {
    *appState = static_cast<void*>(new Application{});
    return SDL_APP_CONTINUE;
  } catch (std::exception&) {
    return SDL_APP_FAILURE;
  }
}

auto SDL_AppIterate(void* appState) -> SDL_AppResult {
  auto app{static_cast<Application*>(appState)};
  app->onIterate();
  return SDL_APP_CONTINUE;
}

auto SDL_AppEvent(void* appState, SDL_Event* event) -> SDL_AppResult {
  auto app{static_cast<Application*>(appState)};
  return app->onEvent(event) ? SDL_APP_CONTINUE : SDL_APP_SUCCESS;
}

auto SDL_AppQuit(void* appState, SDL_AppResult) -> void {
  const auto app{static_cast<Application*>(appState)};
  delete app;
  LOG("Goodbye.\n");
}
