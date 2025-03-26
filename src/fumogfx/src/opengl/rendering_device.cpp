//
// Created by fumosoftware on 3/25/2025.
//

#include "rendering_device.h"

#include <utility>
#include "glad/glad.h"

namespace fumogfx::opengl {
  std::unique_ptr<class fumogfx::RenderingDevice> create_rendering_device() noexcept {
    std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> window{
        SDL_CreateWindow("Title", 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE),
        SDL_DestroyWindow};

    if (!window)
      return nullptr;

    std::unique_ptr<SDL_GLContextState, bool (*)(SDL_GLContextState *)> gl{
        SDL_GL_CreateContext(window.get()), SDL_GL_DestroyContext};
    if (!gl)
      return nullptr;

    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress)) == 0)
      return nullptr;

    return std::make_unique<fumogfx::opengl::RenderingDevice>(std::move(window), std::move(gl));
  }

  RenderingDevice::RenderingDevice(
      std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> &&window,
      std::unique_ptr<SDL_GLContextState, bool (*)(SDL_GLContextState *)> &&gl) noexcept :
      fumogfx::RenderingDevice(std::move(window)), m_context{std::move(gl)} {}

  void RenderingDevice::clear_impl() const noexcept { m_context.clear(); }
  void RenderingDevice::present_impl() const noexcept {
    SDL_assert(m_window != nullptr);
    SDL_GL_SwapWindow(m_window.get());
  }
} // namespace fumogfx::opengl
