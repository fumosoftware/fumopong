//
// Created by fumosoftware on 6/13/2025.
//

#ifndef RENDERING_WINDOW_H
#define RENDERING_WINDOW_H

#include <array>
#include <cstddef>

namespace fumo {

class RenderingEngine;

class RenderingWindow {
public:
  explicit RenderingWindow(RenderingEngine* renderingEngine) noexcept;
  ~RenderingWindow() noexcept;
  RenderingWindow(const RenderingWindow &) = delete;
  RenderingWindow& operator=(const RenderingWindow &) = delete;
  RenderingWindow(RenderingWindow &&) noexcept;
  RenderingWindow& operator=(RenderingWindow &&) noexcept;

  bool pollEvents() noexcept;
  void present() noexcept;
  unsigned int windowId() noexcept;
private:
  alignas(std::max_align_t) std::array<std::byte, 32> m_windowBackend{};
  RenderingEngine* m_renderingEngine{nullptr};
};

} // fumo

#endif //RENDERING_WINDOW_H
