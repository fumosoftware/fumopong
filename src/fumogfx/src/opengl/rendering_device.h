//
// Created by fumosoftware on 3/25/2025.
//

#ifndef OPENGL_RENDERING_DEVICE_H
#define OPENGL_RENDERING_DEVICE_H

#include "rendering_device_context.h"

#include <fumogfx/rendering_device.h>

namespace fumogfx::opengl {

  [[nodiscard]] std::unique_ptr<class RenderingDevice> create_rendering_device() noexcept;

  class RenderingDevice final : public virtual fumogfx::RenderingDevice {
public:
    RenderingDevice(
        std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> &&window,
        std::unique_ptr<SDL_GLContextState, bool (*)(SDL_GLContextState *)> &&gl) noexcept;
    ~RenderingDevice() noexcept override = default;

    void clear_impl() const noexcept override;
    void present_impl() const noexcept override;

private:
    RenderingDeviceContext m_context{
        std::unique_ptr<SDL_GLContextState, bool (*)(SDL_GLContextState *)>{nullptr,
                                                                            SDL_GL_DestroyContext}};
  };

} // namespace fumogfx::opengl

#endif // OPENGL_RENDERING_DEVICE_H
