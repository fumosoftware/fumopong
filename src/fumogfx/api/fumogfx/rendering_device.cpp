//
// Created by fumosoftware on 3/25/2025.
//

#include "rendering_device.h"

#include <utility>

#include "opengl/rendering_device.h"

namespace fumogfx {
  std::unique_ptr<RenderingDevice> create_rendering_device() noexcept {
    if (!SDL_WasInit(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
      if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        return nullptr;
      }
    }

    return opengl::create_rendering_device();
  }

  RenderingDevice::RenderingDevice(
      std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> &&window) noexcept :
      m_window{std::exchange(window, nullptr)} {
    SDL_assert(m_window != nullptr);
  }

  void RenderingDevice::clear() const noexcept { clear_impl(); }
  void RenderingDevice::present() const noexcept { present_impl(); }
} // namespace fumogfx
