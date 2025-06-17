//
// Created by fumosoftware on 6/13/2025.
//

#include <libfumo/details/opengl/rendering_engine_opengl.h>
#include <libfumo/details/opengl/glad/glad.h>
#include <SDL3/SDL.h>

namespace fumo {
namespace details {
  RenderingEngineOpenGL::RenderingEngineOpenGL() noexcept {
    m_mainWindow.reset(
      SDL_CreateWindow("Fumo", 1, 1, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN)
    );
    SDL_assert(m_mainWindow != nullptr);

    m_context.reset(SDL_GL_CreateContext(m_mainWindow.get()));
    SDL_assert(m_context != nullptr);

    SDL_assert(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress)) != 0);
  }

  RenderingEngineOpenGL::~RenderingEngineOpenGL() noexcept {}

  void RenderingEngineOpenGL::makeWindowCurrent(SDL_Window *window) const noexcept {
    if(window == nullptr) SDL_GL_MakeCurrent(m_mainWindow.get(), m_context.get());
    else SDL_GL_MakeCurrent(window, m_context.get());
  }
} // details
} // fumo