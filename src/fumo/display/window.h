//
// Created by fumosoftware on 5/29/2025.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <optional>
#include <SDL3/SDL.h>

namespace fumo {
class RenderingContext;

class Window {
public:
  explicit Window(RenderingContext const& ctx);

  Window(Window const&) = delete;
  Window& operator=(Window const&) = delete;

  Window(Window&&) noexcept;
  Window& operator=(Window&&) noexcept;

  explicit operator bool() const noexcept { return m_sdlWindow != nullptr; }
  bool operator!() const { return m_sdlWindow == nullptr; }

  [[nodiscard]] std::optional<Uint32> getWindowId() const noexcept;
  [[nodiscard]] bool display() const;
private:
  using SDLWindow = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
  SDLWindow m_sdlWindow{nullptr, SDL_DestroyWindow};
};

} // fumo

#endif //WINDOW_H
