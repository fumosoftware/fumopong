//
// Created by fumosoftware on 6/13/2025.
//

#ifndef RENDERING_WINDOW_OPENGL_H
#define RENDERING_WINDOW_OPENGL_H

#include <memory>

#include <SDL3/SDL.h>

namespace fumo {
namespace details {

class RenderingWindowOpenGL {
  using SDLWindow = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
  using SDLGLContext = std::unique_ptr<SDL_GLContextState, decltype(&SDL_GL_DestroyContext)>;

public:
  RenderingWindowOpenGL() noexcept;
  ~RenderingWindowOpenGL() noexcept = default;
  RenderingWindowOpenGL(const RenderingWindowOpenGL&) = delete;
  RenderingWindowOpenGL& operator=(const RenderingWindowOpenGL&) = delete;
  RenderingWindowOpenGL(RenderingWindowOpenGL&& rhs) noexcept;
  [[nodiscard]]
  RenderingWindowOpenGL& operator=(RenderingWindowOpenGL&& rhs) noexcept;

  [[nodiscard]] bool pollEvents() const noexcept;
private:
  SDLWindow m_window{nullptr, SDL_DestroyWindow};
  SDLGLContext m_context{nullptr, SDL_GL_DestroyContext};
};

} // details
} // fumo

#endif //RENDERING_WINDOW_OPENGL_H
