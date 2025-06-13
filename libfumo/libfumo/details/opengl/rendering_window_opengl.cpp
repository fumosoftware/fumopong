//
// Created by fumosoftware on 6/13/2025.
//

#include <libfumo/details/opengl/rendering_window_opengl.h>

#include <utility>

namespace
{
  constexpr auto SDL_SUBSYSTEMS = SDL_INIT_VIDEO | SDL_INIT_EVENTS;
}

namespace fumo {
namespace details {
  RenderingWindowOpenGL::RenderingWindowOpenGL() noexcept {
    SDL_assert(SDL_WasInit(SDL_SUBSYSTEMS) == SDL_SUBSYSTEMS);

    m_window.reset(SDL_CreateWindow("Fumo", 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE));

    SDL_assert(m_window != nullptr);

    m_context.reset(SDL_GL_CreateContext(m_window.get()));

    SDL_assert(m_context != nullptr);
  }

  RenderingWindowOpenGL::RenderingWindowOpenGL(RenderingWindowOpenGL &&rhs) noexcept :
    m_window(std::exchange(rhs.m_window, nullptr)),
    m_context(std::exchange(rhs.m_context, nullptr))
  {}

  RenderingWindowOpenGL &RenderingWindowOpenGL::operator=(RenderingWindowOpenGL &&rhs) noexcept {
    m_window = std::exchange(rhs.m_window, nullptr);
    m_context = std::exchange(rhs.m_context, nullptr);

    return *this;
  }
  bool RenderingWindowOpenGL::pollEvents() const noexcept {
    SDL_Event events{};
    while(SDL_PollEvent(&events)) {
      switch(events.type) {
        case SDL_EVENT_QUIT: return false;

        default: break;
      }
    }

    return true;
  }


} // details
} // fumo