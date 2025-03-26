//
// Created by fumosoftware on 3/25/2025.
//

#ifndef RENDERING_CONTEXT_H
#define RENDERING_CONTEXT_H

#include <SDL3/SDL.h>
#include <memory>

namespace fumogfx::opengl::context {
  class RenderingContext {
public:
    explicit RenderingContext(
        std::unique_ptr<SDL_GLContextState, bool (*)(SDL_GLContextState *)> &&gl) noexcept;
    ~RenderingContext() noexcept = default;

    void clear() const noexcept;
private:
    std::unique_ptr<SDL_GLContextState, bool (*)(SDL_GLContextState *)> m_gl{nullptr,
                                                                             SDL_GL_DestroyContext};
  };
} // namespace fumogfx::opengl::context


#endif // RENDERING_CONTEXT_H
