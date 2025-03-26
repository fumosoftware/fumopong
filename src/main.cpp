//
// Created by fumosoftware on 3/18/2025.
//

#include <cstdlib>

#include <SDL3/SDL.h>

#include "fumogfx/rendering_device.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
    return -1;
  }
  std::atexit(SDL_Quit);

  auto const rendering_device = fumogfx::create_rendering_device();
  if (!rendering_device)
    return -1;

  SDL_Event event{};
  bool is_running{true};
  while (is_running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT)
        is_running = false;
    }

    rendering_device->clear();
    rendering_device->present();
  }

  return 0;
}
