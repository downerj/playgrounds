#include "app.hxx"

#include <stdexcept>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#include <SDL3/SDL_init.h>

#include "debug.hxx"

/**
 * Declarations.
 */

namespace {

#ifdef DEBUG
auto debugMessageCallbackGL(
  GLenum source, GLenum type, GLuint id, GLenum severity,
  GLsizei length, const GLchar* message, const GLvoid* userParam
) -> void;
#endif // DEBUG

} // namespace

/**
 * Definitions.
 */

Application::Application() {
  LOG("Constructing application\n");
  // Initialize SDL.
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    LOG_ERROR("Failed to initialize SDL: " << SDL_GetError() << '\n');
    throw std::runtime_error{"Failed to initialize SDL"};
  }

  // Create SDL window.
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(
    SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE
  );
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  _window = SDL_CreateWindow(
    "SDL & OpenGL Core", 400, 400,
    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
  );
  if (!_window) {
    LOG_ERROR("Failed to create SDL window: " << SDL_GetError() << '\n');
    throw std::runtime_error{"Failed to create SDL window"};
  }

  // Initialize OpenGL context.
  _context = SDL_GL_CreateContext(_window);
  if (!_context) {
    LOG_ERROR("Failed to initialize OpenGL context: " << SDL_GetError() << '\n');
    throw std::runtime_error{"Failed to initialize OpenGL context"};
  }
  if (!gladLoadGL(SDL_GL_GetProcAddress)) {
    LOG_ERROR("Failed to load OpenGL library\n");
    throw std::runtime_error{"Failed to load OpenGL library"};
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
}

Application::~Application() {
  LOG("Destroying application\n");
  SDL_GL_DestroyContext(_context);
}

auto Application::handleEvents() -> bool {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT:
        return false;
      case SDL_EVENT_WINDOW_RESIZED:
      case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
        break;
      case SDL_EVENT_KEY_DOWN: {
        SDL_Keymod mods{SDL_GetModState()};
        if (mods & SDL_KMOD_CTRL && event.key.scancode == SDL_SCANCODE_Q) {
          return false;
        }
      }
    }
  }

  return true;
}

auto Application::render() -> void {
  int w;
  int h;
  SDL_GetWindowSize(_window, &w, &h);
  glViewport(0, 0, w, h);
  glClearColor(0.f, .8f, 1.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(_window);
}

namespace {

#ifdef DEBUG
auto debugMessageCallbackGL(
  GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar* message, const GLvoid*
) -> void {
  LOG_ERROR("GL error: " << message << '\n');
}
#endif // DEBUG

} // namespace
