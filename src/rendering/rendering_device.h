//
// Created by fumosoftware on 3/19/2025.
//

#ifndef RENDERING_DEVICE_H
#define RENDERING_DEVICE_H

#include <SDL3/SDL.h>
#include <expected>
#include <string>

#include "drivers/opengl/rendering_context.h"

class RenderingDevice {
  public:
  [[nodiscard]] static std::expected<RenderingDevice, std::string>
  create(SDL_Window *window) noexcept;

  void set_clear_color(float r, float g, float b, float a) const noexcept;
  void clear() const noexcept;

  private:
  explicit RenderingDevice(OpenGLRenderingContext &&context) noexcept;
  OpenGLRenderingContext m_rendering_context;
};


#endif // RENDERING_DEVICE_H
