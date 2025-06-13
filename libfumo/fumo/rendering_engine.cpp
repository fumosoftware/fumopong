//
// Created by fumosoftware on 6/13/2025.
//

#include <fumo/rendering_engine.h>

#include <SDL3/SDL.h>

namespace
{
  constexpr auto SDL_SUBSYSTEMS = SDL_INIT_VIDEO | SDL_INIT_EVENTS;
}

namespace fumo {
  RenderingEngine::RenderingEngine() noexcept {
    SDL_assert(SDL_InitSubSystem(SDL_SUBSYSTEMS) == true);
  }
  RenderingEngine::~RenderingEngine() noexcept {
    SDL_QuitSubSystem(SDL_SUBSYSTEMS);
  }
} // fumo