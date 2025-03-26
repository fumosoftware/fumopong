//
// Created by fumosoftware on 3/25/2025.
//

#include "rendering_device_context.h"
#include <utility>
#include "glad/glad.h"

fumogfx::opengl::RenderingDeviceContext::RenderingDeviceContext(
    std::unique_ptr<SDL_GLContextState, bool (*)(SDL_GLContextState *)> &&gl) noexcept :
    m_gl{std::exchange(gl, nullptr)} {
  SDL_assert(m_gl != nullptr);

  glClearColor(0.f, 0.f, 1.f, 1.f);
}

void fumogfx::opengl::RenderingDeviceContext::clear() const noexcept {
  SDL_assert(m_gl != nullptr);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
