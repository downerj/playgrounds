#include "app.hxx"

#include <iostream>
#include <stdexcept>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

/**
 * Declarations.
 */

namespace {

#ifdef DEBUG
auto debugMessageCallbackGL(GLenum source, GLenum type,
  GLuint id, GLenum severity, GLsizei length,
  const GLchar* message, const GLvoid* userParam)
-> void;
#endif

}

/**
 * Definitions.
 */

namespace {

#ifdef DEBUG
auto debugMessageCallbackGL(GLenum, GLenum, GLuint, GLenum,
  GLsizei, const GLchar* message, const GLvoid*)
-> void {
  std::cout << "OpenGL error: " << message << '\n';
}
#endif

}

my::Application::Application() {
  std::cout << "Initializing SDL...";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
    SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  window = SDL_CreateWindow("SDL + OpenGL Core",
    400, 400, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if (window == nullptr) {
    std::cout << "Failed\n";
    std::cerr << "SDL Error: " << SDL_GetError() << '\n';
    throw std::runtime_error("SDL init failure");
  }
  std::cout << "Succeeded\n";

  std::cout << "Initializing SDL OpenGL context...";
  context = SDL_GL_CreateContext(window);
  if (context == nullptr) {
    std::cout << "Failed\n";
    std::cerr << "SDL OpenGL Error: " << SDL_GetError() << '\n';
    cleanUpWindow();
    throw std::runtime_error("SDL OpenGL init failure");
  }
  std::cout << "Succeeded\n";

  std::cout << "Initializing GLAD OpenGL...";
  if (!gladLoadGL(SDL_GL_GetProcAddress)) {
    std::cout << "Failed\n";
    std::cerr << "Failed to load GLAD OpenGL library\n";
    cleanUpAll();
    throw std::runtime_error("GLAD OpenGL init failure");
  }
  std::cout << "Succeeded\n";

#ifdef DEBUG
  if (GLAD_GL_ARB_debug_output) {
    std::cout << "OpenGL extension GL_ARB_debug_output avaiable\n";
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
    glDebugMessageCallbackARB(debugMessageCallbackGL,
      nullptr /*userParam*/);
  } else {
    std::cerr << "Warning: OpenGL extension GL_ARB_debug_output not available";
  }
#endif
  if (!SDL_GL_SetSwapInterval(1)) {
    std::cerr << "Warning: Failed to set VSync for SDL OpenGL: "
      << SDL_GetError() << '\n';
  }
}

my::Application::~Application() noexcept {
  cleanUpAll();
}

auto my::Application::getWindow() const -> SDL_Window* {
  return window;
}

auto my::Application::getContext() const -> SDL_GLContext {
  return context;
}

auto my::Application::handleEvents() -> bool {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT:
        return false;
      case SDL_EVENT_WINDOW_RESIZED:
        // TODO: Implement.
        break;
      case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
        // TODO: Implement.
        break;
      case SDL_EVENT_KEY_DOWN: {
        SDL_Keymod mods{SDL_GetModState()};
        bool isCtrl = mods == SDL_KMOD_LCTRL || mods == SDL_KMOD_RCTRL;
        bool isCtrlQ = isCtrl && event.key.scancode == SDL_SCANCODE_Q;
        bool isCtrlW = isCtrl && event.key.scancode == SDL_SCANCODE_W;
        if (isCtrlQ || isCtrlW) {
          return false;
        }
      }
    }
  }
  return true;
}

auto my::Application::cleanUpWindow() noexcept -> void {
  if (window != nullptr) {
    std::cout << "Cleaning up SDL window...";
    SDL_DestroyWindow(window);
    std::cout << "Done\n";
  }
}

auto my::Application::cleanUpContext() noexcept -> void {
  if (context != nullptr) {
    std::cout << "Cleaning up SDL OpenGL context...";
    SDL_GL_DestroyContext(context);
    std::cout << "Done\n";
  }
}

auto my::Application::cleanUpAll() noexcept -> void {
  cleanUpContext();
  cleanUpWindow();
}

auto my::Application::render() -> void {
  int w;
  int h;
  SDL_GetWindowSize(window, &w, &h);
  glViewport(0, 0, w, h);
  glClearColor(0.0f, 0.8f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(window);
}
