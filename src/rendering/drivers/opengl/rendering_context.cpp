//
// Created by fumosoftware on 3/18/2025.
//

#include "rendering_context.h"
#include "glad/glad.h"

#include "device_driver.h"

std::expected<OpenGLRenderingContext, std::string>
OpenGLRenderingContext::create(SDL_Window *window) noexcept {
  if (!window)
    return std::unexpected{"Error: Window Handle does not exist."};

  auto const gl_context = SDL_GL_CreateContext(window);
  if (!gl_context)
    return std::unexpected{"Error: Could not create an OpenGL Context"};

  auto const did_load =
      gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress)) != 0;
  if (!did_load)
    return std::unexpected{"Error: Could not load OpenGL"};

  return OpenGLRenderingContext{gl_context};
}

OpenGLDeviceDriver *OpenGLRenderingContext::get_device_driver() const noexcept {
  return m_device.get();
}

OpenGLRenderingContext::OpenGLRenderingContext(SDL_GLContext context) noexcept :
    m_gl_context(context, SDL_GL_DestroyContext), m_device(new OpenGLDeviceDriver()) {}
