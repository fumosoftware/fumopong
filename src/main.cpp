//
// Created by fumosoftware on 3/18/2025.
//

#include <SDL3/SDL.h>
#include <iostream>
#include <memory>

#include "rendering/rendering_device.h"

[[nodiscard]] int run_game(SDL_Window *window, RenderingDevice const &rendering_device) noexcept;

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) noexcept {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
    return EXIT_FAILURE;
  }
  std::atexit(SDL_Quit);

  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window(
      SDL_CreateWindow("Fumo Pong", 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE),
      SDL_DestroyWindow);

  if (!window) {
    return EXIT_FAILURE;
  }

  auto const rendering_device = RenderingDevice::create(window.get());
  if (!rendering_device) {
    return EXIT_FAILURE;
  }

  return run_game(window.get(), rendering_device.value());
}

[[nodiscard]] int run_game(SDL_Window *window, RenderingDevice const &rendering_device) noexcept {
  rendering_device.set_clear_color(0.5f, 0.f, 0.35f, 0.23f);

  SDL_Event event{};
  bool running{true};
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT)
        running = false;
    }

    rendering_device.clear();
    SDL_GL_SwapWindow(window);
  }

  return EXIT_SUCCESS;
}
