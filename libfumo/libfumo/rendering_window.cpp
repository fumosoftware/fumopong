//
// Created by fumosoftware on 6/13/2025.
//

#include <libfumo/rendering_window.h>

#include <libfumo/rendering_engine.h>
#include <libfumo/details/opengl/rendering_window_opengl.h>

#include <utility>

namespace fumo {

  using RenderingWindowType = details::RenderingWindowOpenGL;

  RenderingWindow::RenderingWindow(RenderingEngine const* renderingEngine) noexcept :
    m_renderingEngine(renderingEngine)
  {
    static_assert(sizeof(m_windowBackend) == sizeof(RenderingWindowType),
                  "The size of RenderingEngine::Impl does not match the number of reserved bytes."
                  "Please update the number of reserved bytes.");

    SDL_assert(renderingEngine != nullptr);

    new(m_windowBackend.data()) RenderingWindowType();
  }

  RenderingWindow::~RenderingWindow() noexcept {
    std::destroy_at(std::launder(reinterpret_cast<RenderingWindowType *>(m_windowBackend.data())));
  }

  RenderingWindow::RenderingWindow(RenderingWindow &&rhs) noexcept :
    m_windowBackend(std::exchange(rhs.m_windowBackend, {})),
    m_renderingEngine(std::exchange(rhs.m_renderingEngine, nullptr))
  {}

  RenderingWindow &RenderingWindow::operator=(RenderingWindow &&rhs) noexcept {
    m_windowBackend = std::exchange(rhs.m_windowBackend, {});
    m_renderingEngine = std::exchange(rhs.m_renderingEngine, nullptr);
    return *this;
  }

  bool RenderingWindow::pollEvents() noexcept {
    SDL_assert(m_renderingEngine != nullptr);

    auto const window = std::launder(reinterpret_cast<RenderingWindowType *>(m_windowBackend.data()));
    return window->pollEvents();
  }
} // fumo