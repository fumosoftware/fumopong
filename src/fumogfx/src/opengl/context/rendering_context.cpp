//
// Created by fumosoftware on 3/25/2025.
//

#include "rendering_context.h"
#include "opengl/glad/glad.h"
#include <utility>

fumogfx::opengl::context::RenderingContext::RenderingContext(
    std::unique_ptr<SDL_GLContextState, bool (*)(SDL_GLContextState *)> &&gl) noexcept :
    m_gl{std::exchange(gl, nullptr)} {
  glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
}

void fumogfx::opengl::context::RenderingContext::clear() const noexcept {
  SDL_assert(m_gl != nullptr);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}