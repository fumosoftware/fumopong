//
// Created by fumosoftware on 3/18/2025.
//

/*

#include <SDL3/SDL.h>
#include <iostream>

#include "rendering/drivers/window_interface.h"
#include "rendering/rendering_context.h"


int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) noexcept {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
    return EXIT_FAILURE;
  }
  std::atexit(SDL_Quit);

  auto rendering_context_expected = create_rendering_context();
  if(!rendering_context_expected) {
    std::cerr << rendering_context_expected.error() << std::endl;
    return EXIT_FAILURE;
  }

  auto rendering_context = std::move(rendering_context_expected.value());
  auto const window = rendering_context.get_main_window();

  SDL_Event event{};
  bool isRunning = true;
  while(isRunning) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_EVENT_QUIT) isRunning = false;
    }

    window->clear();
    window->present();
  }
}
*/
#include <SDL3/SDL.h>

#include <cstdlib>

#include "fumogfx/rendering_device.h"

int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv) {
  if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
    return -1;
  }
  std::atexit(SDL_Quit);

  auto const rendering_device = fumogfx::create_rendering_device();
  if(!rendering_device) return -1;

  SDL_Event event{};
  bool is_running{true};
  while(is_running) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_EVENT_QUIT) is_running = false;
    }

    rendering_device->clear();
    rendering_device->present();
  }

  return 0;
}