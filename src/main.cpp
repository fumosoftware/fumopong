//
// Created by fumosoftware on 3/18/2025.
//

#include <memory>

#include <SDL3/SDL.h>
#include <cstdlib>
#include <glad/glad.h>
#include <iostream>

namespace {

  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window{nullptr, SDL_DestroyWindow};
  std::unique_ptr<SDL_GLContextState, decltype(&SDL_GL_DestroyContext)> context{nullptr, SDL_GL_DestroyContext};

  bool initialize_sdl();
  bool create_window();
  bool create_opengl_context();
  bool load_opengl_functions();

}

int main(int argc, char** argv) {

  if(!initialize_sdl()) return -1;
  if(!create_window()) return -1;
  if(!create_opengl_context()) return -1;
  if(!load_opengl_functions()) return -1;

  SDL_Event event{};
  bool isRunning {true};

  while(isRunning) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_EVENT_QUIT) isRunning = false;
    }

    SDL_GL_SwapWindow(window.get());
  }
  return 0;
}

namespace {
  bool initialize_sdl() {
    if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
      return false;
    }

    atexit(SDL_Quit);
    return true;
  }

  bool create_window() {
    window.reset(SDL_CreateWindow("Pong", 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE));

    return window.get() != nullptr;
  }

  bool create_opengl_context() {
    if(!window) return false;
    context.reset(SDL_GL_CreateContext(window.get()));

    return context.get() != nullptr;
  }

  bool load_opengl_functions() {
    auto const version = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress)) != 0;
    std::cout << glGetString(GL_VERSION) <<"\n";

    return version;
  }
}