//
// Created by fumosoftware on 6/13/2025.
//

#include <libfumo/rendering_window.h>

#include <libfumo/details/opengl/rendering_window_opengl.h>

#include <utility>

namespace fumo {

  using RenderingWindowType = details::RenderingWindowOpenGL;

  RenderingWindow::RenderingWindow() noexcept {
    static_assert(sizeof(m_windowBackend) == sizeof(RenderingWindowType),
                  "The size of RenderingEngine::Impl does not match the number of reserved bytes."
                  "Please update the number of reserved bytes.");

    new(m_windowBackend.data()) RenderingWindowType();
  }

  RenderingWindow::~RenderingWindow() noexcept {
    std::destroy_at(std::launder(reinterpret_cast<RenderingWindowType *>(m_windowBackend.data())));
  }

  RenderingWindow::RenderingWindow(RenderingWindow &&rhs) noexcept :
    m_windowBackend(std::exchange(rhs.m_windowBackend, {}))
  {}

  RenderingWindow &RenderingWindow::operator=(RenderingWindow &&rhs) noexcept {
    m_windowBackend = std::exchange(rhs.m_windowBackend, {});
    return *this;
  }

  bool RenderingWindow::pollEvents() noexcept {
    auto window = std::launder(reinterpret_cast<RenderingWindowType *>(m_windowBackend.data()));
    return window->pollEvents();
  }
} // fumo