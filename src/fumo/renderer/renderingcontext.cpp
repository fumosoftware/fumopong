//
// Created by fumosoftware on 5/29/2025.
//

#include "renderingcontext.h"

#include <utility>

#include <SDL3/SDL.h>

#include "../display/window.h"

namespace fumo {
  RenderingContext::RenderingContext()
    : m_glContext {
      []() -> GLContext {
        auto const tempWindow =
          std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>
            (SDL_CreateWindow(nullptr, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN), SDL_DestroyWindow);

        return GLContext{SDL_GL_CreateContext(tempWindow.get()), SDL_GL_DestroyContext};
      }()
    }
  {}

  RenderingContext::RenderingContext(RenderingContext &&rhs) noexcept
    : m_glContext {
        std::exchange(rhs.m_glContext, nullptr)
    }
  {}

  RenderingContext &RenderingContext::operator=(RenderingContext &&rhs) noexcept {
    this->m_glContext = std::exchange(rhs.m_glContext, nullptr);

    return *this;
  }

  bool RenderingContext::makeCurrent(Window const &window) const noexcept {
    auto const rawWindow = [&window]() -> SDL_Window* {
      if(auto const id = window.getWindowId(); id) {
        return SDL_GetWindowFromID(*id);
      }

      return nullptr;
    }();

    return SDL_GL_MakeCurrent(rawWindow, m_glContext.get());
  }

} // fumo