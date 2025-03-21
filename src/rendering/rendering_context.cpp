//
// Created by fumosoftware on 3/20/2025.
//

#include "rendering_context.h"

#include <SDL3/SDL_assert.h>
#include <glad/glad.h>
#include <iostream>
#include <utility>

#include "drivers/opengl/rendering_context_device.h"
#include "drivers/opengl/window.h"

namespace {
  using SDLWindow = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
  using SDLGLContext = std::unique_ptr<SDL_GLContextState, decltype(&SDL_GL_DestroyContext)>;
  using OpenGLWindowPtr = std::unique_ptr<OpenGLWindow>;

  std::expected<std::unique_ptr<IRenderingContextDevice>, std::string>
  create_gl_rendering_context_device() {
    SDLWindow window{
        SDL_CreateWindow("fumopong", 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE),
        SDL_DestroyWindow};
    if (!window)
      return std::unexpected{"Failed to create window"};

    SDLGLContext context{SDL_GL_CreateContext(window.get()), SDL_GL_DestroyContext};
    if (!context)
      return std::unexpected{"Failed to create OpenGL context"};

    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress)) == 0)
      return std::unexpected{"Failed to load OpenGL functions"};

    OpenGLWindowPtr gl_window(new OpenGLWindow{std::move(window), std::move(context)});

    return std::unique_ptr<IRenderingContextDevice>{
        new OpenGLRenderingContextDevice{std::move(gl_window)}};
  }
} // namespace

RenderingContext::RenderingContext(std::unique_ptr<IRenderingContextDevice> &&context_device) :
    m_context_device(std::exchange(context_device, nullptr)) {}

RenderingContext::~RenderingContext() {}

RenderingContext::RenderingContext(RenderingContext && rhs) noexcept : m_context_device{std::exchange(rhs.m_context_device, nullptr)} {}

RenderingContext &RenderingContext::operator=(RenderingContext &&rhs) noexcept {
  m_context_device = std::exchange(rhs.m_context_device, nullptr);
  return *this;
}
IWindow *RenderingContext::get_main_window() const noexcept {
  SDL_assert(m_context_device != nullptr);
  return m_context_device->get_main_window();
}

std::expected<RenderingContext, std::string> create_rendering_context() {
  auto context_device_expected = create_gl_rendering_context_device();
  if (!context_device_expected)
    return std::unexpected{context_device_expected.error()};

  return RenderingContext{std::move(context_device_expected.value())};
}
