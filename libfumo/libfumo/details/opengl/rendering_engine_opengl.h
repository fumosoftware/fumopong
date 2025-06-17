//
// Created by fumosoftware on 6/13/2025.
//

#ifndef FUMO_DETAILS_RENDERING_ENGINE_OPENGL_H
#define FUMO_DETAILS_RENDERING_ENGINE_OPENGL_H

#include <memory>

#include <SDL3/SDL.h>

namespace fumo {
namespace details {

class RenderingEngineOpenGL {
  using SDLGLContext = std::unique_ptr<SDL_GLContextState, decltype(&SDL_GL_DestroyContext)>;
  using SDLWindow = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
public:
  RenderingEngineOpenGL() noexcept;
  ~RenderingEngineOpenGL() noexcept;

  void makeWindowCurrent(SDL_Window* window) const noexcept;
private:
  SDLGLContext m_context{nullptr, SDL_GL_DestroyContext};
  SDLWindow m_mainWindow{nullptr, SDL_DestroyWindow};
};

} // details
} // fumo

#endif //FUMO_DETAILS_RENDERING_ENGINE_OPENGL_H
