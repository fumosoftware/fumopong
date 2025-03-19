//
// Created by fumosoftware on 3/18/2025.
//

#include <SDL3/SDL.h>
#include <iostream>
#include <memory>

#include "glad/glad.h"

[[nodiscard]] int run_game(int argc, char** argv) noexcept;

int main(int argc, char **argv) noexcept {
  if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
    return EXIT_FAILURE;
  }

  auto const app_status = run_game(argc, argv);

  SDL_Quit();
  return app_status;
}

[[nodiscard]] int run_game(int argc, char** argv) noexcept {
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window(
    SDL_CreateWindow("Fumo Pong", 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)
    , SDL_DestroyWindow);

  if(!window) {
    return EXIT_FAILURE;
  }

  std::unique_ptr<SDL_GLContextState, decltype(&SDL_GL_DestroyContext)> gl_context(
    SDL_GL_CreateContext(window.get()),
    SDL_GL_DestroyContext
  );
  if(!gl_context) {
    return EXIT_FAILURE;
  }

  if(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress)) == 0) {
    return EXIT_FAILURE;
  }

  SDL_Event event{};
  bool running{true};
  while(running) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_EVENT_QUIT) running = false;
    }

    glClearColor(0.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window.get());
  }

  return EXIT_SUCCESS;
}
