//
// Created by fumosoftware on 3/25/2025.
//

#ifndef RENDERING_CONTEXT_H
#define RENDERING_CONTEXT_H

#include <memory>

#include <SDL3/SDL.h>

namespace fumogfx::opengl {
  class RenderingDeviceContext {
public:
    explicit RenderingDeviceContext(
        std::unique_ptr<SDL_GLContextState, bool (*)(SDL_GLContextState *)> &&gl) noexcept;
    ~RenderingDeviceContext() noexcept = default;

    void clear() const noexcept;

private:
    std::unique_ptr<SDL_GLContextState, bool (*)(SDL_GLContextState *)> m_gl{nullptr,
                                                                             SDL_GL_DestroyContext};
  };
} // namespace fumogfx::opengl


#endif // RENDERING_CONTEXT_H
