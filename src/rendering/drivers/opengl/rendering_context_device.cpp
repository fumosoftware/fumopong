//
// Created by fumosoftware on 3/20/2025.
//

#include "rendering_context_device.h"

#include <SDL3/SDL_assert.h>
#include <utility>

#include "window.h"

OpenGLRenderingContextDevice::OpenGLRenderingContextDevice(std::unique_ptr<OpenGLWindow> &&window) :
    IRenderingContextDevice(), m_window(std::exchange(window, nullptr)) {}

IWindow *OpenGLRenderingContextDevice::get_main_window() const noexcept {
  SDL_assert(m_window != nullptr);
  return m_window.get();
}