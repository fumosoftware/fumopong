//
// Created by fumosoftware on 3/20/2025.
//

#ifndef WINDOW_H
#define WINDOW_H

#include "../window_interface.h"

#include <SDL3/SDL_video.h>
#include <memory>

class OpenGLWindow final : public virtual IWindow {
  using SDLWindow = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
  using SDLGLContext = std::unique_ptr<SDL_GLContextState, decltype(&SDL_GL_DestroyContext)>;

  public:
  OpenGLWindow(SDLWindow &&window, SDLGLContext &&context);
  ~OpenGLWindow() noexcept override = default;

  void present() noexcept override;
  void clear() noexcept override;

  private:
  SDLWindow m_window{nullptr, SDL_DestroyWindow};
  SDLGLContext m_glcontext{nullptr, SDL_GL_DestroyContext};
};

#endif // WINDOW_H
