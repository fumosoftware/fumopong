//
// Created by fumosoftware on 5/20/2025.
//

#include "fumo/renderer/renderingcontext.h"
#include "fumo/display/window.h"
#include <SDL3/SDL.h>

int main(int argc, char** argv) {
  if(!SDL_Init(SDL_INIT_VIDEO)) {
    return -1;
  }

  fumo::RenderingContext const ctx;
  fumo::Window window{ctx};

  bool isRunning = true;
  SDL_Event event{};
  while(isRunning) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_EVENT_QUIT) isRunning = false;
    }

    if(!isRunning) break;

    auto const _ = window.display();
  }

  return 0;
}