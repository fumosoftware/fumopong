//
// Created by fumosoftware on 3/20/2025.
//

#include "window.h"
#include <SDL3/SDL_assert.h>
#include <utility>

#include <glad/glad.h>


OpenGLWindow::OpenGLWindow(SDLWindow &&window, SDLGLContext &&context) :
    IWindow(),
    m_window(std::exchange(window, nullptr)),
    m_glcontext(std::exchange(context, nullptr)) {
  SDL_assert(m_window != nullptr);
  SDL_assert(m_glcontext != nullptr);

  glClearColor(1.0, 0.0, 1.0, 0.45);
}

void OpenGLWindow::present() noexcept {
  SDL_assert(m_window != nullptr);
  SDL_GL_SwapWindow(m_window.get());
}
void OpenGLWindow::clear() noexcept {
  SDL_assert(m_window != nullptr);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
