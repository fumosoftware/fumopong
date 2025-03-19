//
// Created by fumosoftware on 3/18/2025.
//

#ifndef RENDERING_CONTEXT_H
#define RENDERING_CONTEXT_H

#include <SDL3/SDL.h>
#include <expected>
#include <memory>
#include <string>

class OpenGLDeviceDriver;
class OpenGLRenderingContext {
  using OpenGLDeviceDriverPtr = std::shared_ptr<OpenGLDeviceDriver>;
  using OpenGLContextPtr = std::unique_ptr<SDL_GLContextState, decltype(&SDL_GL_DestroyContext)>;

  public:
  [[nodiscard]] static std::expected<OpenGLRenderingContext, std::string>
  create(SDL_Window *window) noexcept;

  [[nodiscard]] OpenGLDeviceDriver *get_device_driver() const noexcept;

  private:
  explicit OpenGLRenderingContext(SDL_GLContext context) noexcept;

  OpenGLContextPtr m_gl_context{nullptr, SDL_GL_DestroyContext};
  OpenGLDeviceDriverPtr m_device{nullptr};
};

#endif // RENDERING_CONTEXT_H
