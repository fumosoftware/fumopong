//
// Created by fumosoftware on 6/13/2025.
//

#ifndef FUMO_RENDERING_ENGINE_H
#define FUMO_RENDERING_ENGINE_H

#include <array>
#include <cstddef>

namespace fumo {

class RenderingEngine {
public:
  RenderingEngine() noexcept;
  ~RenderingEngine() noexcept;
  RenderingEngine(const RenderingEngine&) = delete;
  RenderingEngine& operator=(const RenderingEngine&) = delete;
  RenderingEngine(RenderingEngine&&) noexcept;
  RenderingEngine& operator=(RenderingEngine&&) noexcept;

private:
  alignas(std::max_align_t) std::array<std::byte, 1> m_renderingBackend{};

};

} // fumo

#endif //FUMO_RENDERING_ENGINE_H
