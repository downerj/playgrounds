#include "main.hxx"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

/**
 * Defintions.
 */

auto SDL_AppInit(void** appState, int, char**) -> SDL_AppResult {
  // Initialize SDL.
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    LOG_ERROR("Failed to initialize SDL: " << SDL_GetError() << '\n');
    return SDL_APP_FAILURE;
  }

  // Create SDL window.
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(
    SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE
  );
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_Window* window{SDL_CreateWindow(
    "SDL & OpenGL Core", 400, 400,
    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
  )};
  if (!window) {
    LOG_ERROR("Failed to create SDL window: " << SDL_GetError() << '\n');
    return SDL_APP_FAILURE;
  }

  // Initialize OpenGL context.
  SDL_GLContext context{SDL_GL_CreateContext(window)};
  if (!context) {
    LOG_ERROR("Failed to initialize OpenGL context: " << SDL_GetError() << '\n');
    return SDL_APP_FAILURE;
  }
  if (!gladLoadGL(SDL_GL_GetProcAddress)) {
    LOG_ERROR("Failed to initialize OpenGL library\n");
    return SDL_APP_FAILURE;
  }
#ifdef DEBUG
  if (GLAD_GL_ARB_debug_output) {
    LOG("GL extension GL_ARB_debug_output available\n");
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
    glDebugMessageCallbackARB(debugMessageCallbackGL, nullptr /*userParam*/);
  } else {
    LOG_ERROR("Warning: GL extension GL_ARB_debug_output unavailable\n");
  }
#endif // DEBUG
  if (!SDL_GL_SetSwapInterval(1)) {
    LOG_ERROR("Warning: Unable to set VSync: " << SDL_GetError() << '\n');
  }

  *appState = static_cast<void*>(new Application{window, context});

  return SDL_APP_CONTINUE;
}

auto SDL_AppIterate(void* appState) -> SDL_AppResult {
  const auto app{static_cast<Application*>(appState)};
  int w;
  int h;
  SDL_GetWindowSize(app->getWindow(), &w, &h);
  glViewport(0, 0, w, h);
  glClearColor(0.f, .8f, 1.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(app->getWindow());
  return SDL_APP_CONTINUE;
}

auto SDL_AppEvent(void*, SDL_Event* event) -> SDL_AppResult {
  switch (event->type) {
    case SDL_EVENT_QUIT:
      return SDL_APP_SUCCESS;
    case SDL_EVENT_WINDOW_RESIZED:
    case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
      // LOG("Window was resized!\n");
      break;
    case SDL_EVENT_KEY_DOWN: {
      SDL_Keymod mods{SDL_GetModState()};
      if (mods & SDL_KMOD_CTRL && event->key.scancode == SDL_SCANCODE_Q) {
        return SDL_APP_SUCCESS;
      }
    }
  }
  return SDL_APP_CONTINUE;
}

auto SDL_AppQuit(void* appState, SDL_AppResult) -> void {
  const auto app{static_cast<Application*>(appState)};
  delete app;
  LOG("Goodbye.\n");
}

namespace {

#ifdef DEBUG
auto debugMessageCallbackGL(
  GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar* message, const GLvoid*
) -> void {
  LOG_ERROR("GL error: " << message << '\n');
}
#endif // DEBUG

Application::Application(SDL_Window* window_, SDL_GLContext context_)
: window{window_}, context{context_} {
  LOG("Constructing application\n");
}

Application::~Application() {
  LOG("Destroying application\n");
  SDL_GL_DestroyContext(context);
}

// auto Application::getWindow() const -> const SDL_Window* {
//   return window;
// }

auto Application::getWindow() -> SDL_Window* {
  return window;
}

} // namespace
