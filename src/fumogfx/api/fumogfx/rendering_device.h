//
// Created by fumosoftware on 3/25/2025.
//

#ifndef RENDERING_DEVICE_H
#define RENDERING_DEVICE_H

#include <memory>

#include <SDL3/SDL.h>

namespace fumogfx {

  [[nodiscard]] std::unique_ptr<class RenderingDevice> create_rendering_device() noexcept;

  class RenderingDevice {
public:
    virtual ~RenderingDevice() noexcept = default;

    void clear() const noexcept;
    void present() const noexcept;
protected:
    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> m_window{nullptr, SDL_DestroyWindow};

    explicit RenderingDevice(std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> &&window) noexcept;
    virtual void clear_impl() const noexcept = 0;
    virtual void present_impl() const noexcept = 0;
  };

} // namespace fumogfx

#endif // RENDERING_DEVICE_H
