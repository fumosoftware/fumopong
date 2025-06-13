//
// Created by fumosoftware on 6/13/2025.
//

#include <libfumo/rendering_engine.h>

#include <libfumo/details/opengl/rendering_engine_opengl.h>

#include <memory>
#include <utility>

#include <SDL3/SDL.h>

namespace
{
  constexpr auto SDL_SUBSYSTEMS = SDL_INIT_VIDEO | SDL_INIT_EVENTS;
}

namespace fumo {

  using RenderingEngineType = details::RenderingEngineOpenGL;

  RenderingEngine::RenderingEngine() noexcept {
    static_assert(sizeof(m_renderingBackend) == sizeof(RenderingEngineType),
                  "The size of RenderingEngine::Impl does not match the number of reserved bytes."
                  "Please update the number of reserved bytes.");

    SDL_assert(SDL_InitSubSystem(SDL_SUBSYSTEMS) == true);

    new(m_renderingBackend.data()) RenderingEngineType();
  }

  RenderingEngine::~RenderingEngine() noexcept {
    SDL_QuitSubSystem(SDL_SUBSYSTEMS);

    std::destroy_at(std::launder(reinterpret_cast<RenderingEngineType *>(m_renderingBackend.data())));
  }

  RenderingEngine::RenderingEngine(RenderingEngine &&rhs) noexcept :
      m_renderingBackend(std::exchange(rhs.m_renderingBackend, {})) {}

  RenderingEngine &RenderingEngine::operator=(RenderingEngine &&rhs) noexcept {
    m_renderingBackend = std::exchange(rhs.m_renderingBackend, {});

    return *this;
  }


} // fumo