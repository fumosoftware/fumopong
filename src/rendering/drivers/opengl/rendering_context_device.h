//
// Created by fumosoftware on 3/20/2025.
//

#ifndef RENDERING_CONTEXT_DEVICE_H
#define RENDERING_CONTEXT_DEVICE_H

#include "../rendering_context_device_interface.h"

#include <memory>

class OpenGLWindow;
class OpenGLRenderingContextDevice final : public virtual IRenderingContextDevice {
  public:
  explicit OpenGLRenderingContextDevice(std::unique_ptr<OpenGLWindow> &&window);
  ~OpenGLRenderingContextDevice() noexcept override = default;

  [[nodiscard]] IWindow* get_main_window() const noexcept override;
  private:
  std::unique_ptr<OpenGLWindow> m_window;
};


#endif // RENDERING_CONTEXT_DEVICE_H
