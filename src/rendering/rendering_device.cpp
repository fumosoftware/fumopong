//
// Created by fumosoftware on 3/19/2025.
//

#include "rendering_device.h"

#include "drivers/opengl/device_driver.h"
std::expected<RenderingDevice, std::string> RenderingDevice::create(SDL_Window *window) noexcept {
  auto rendering_context = OpenGLRenderingContext::create(window);
  if (!rendering_context)
    return std::unexpected{rendering_context.error()};

  return RenderingDevice{std::move(rendering_context.value())};
}
void RenderingDevice::set_clear_color(float r, float g, float b, float a) const noexcept {
  m_rendering_context.get_device_driver()->set_clear_color(r, g, b, a);
}
void RenderingDevice::clear() const noexcept {
  m_rendering_context.get_device_driver()->clear_buffer();
}

RenderingDevice::RenderingDevice(OpenGLRenderingContext &&context) noexcept :
    m_rendering_context{std::move(context)} {}
