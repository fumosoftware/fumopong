//
// Created by fumosoftware on 5/29/2025.
//

#include "window.h"

#include <utility>

#include "../renderer/renderingcontext.h"

namespace fumo {
  Window::Window(RenderingContext const& ctx)
    : m_sdlWindow {
      SDL_CreateWindow("Fumo", 640, 480, SDL_WINDOW_OPENGL)
      , SDL_DestroyWindow
    }
  {
    auto const _ = ctx.makeCurrent(*this);
  }

  Window::Window(Window&& rhs) noexcept
    : m_sdlWindow {
        std::exchange(rhs.m_sdlWindow, nullptr)
    }
  {}

  Window &Window::operator=(Window &&rhs) noexcept {
    this->m_sdlWindow = std::exchange(rhs.m_sdlWindow, nullptr);

    return *this;
  }

  std::optional<Uint32> Window::getWindowId() const noexcept {
    auto const id = SDL_GetWindowID(m_sdlWindow.get());
    if(id == 0) return std::nullopt;

    return {id};
  }

  bool Window::display() const {
    return SDL_GL_SwapWindow(m_sdlWindow.get());
  }

} // fumo