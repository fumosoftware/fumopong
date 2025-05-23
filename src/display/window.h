//
// Created by fumosoftware on 5/23/2025.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <memory>
#include <SDL3/SDL_video.h>


namespace drivers::graphics::opengl
{
    class Context;
}

namespace display {

class Window {
    using SDLWindow = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
public:
    Window() noexcept;
    explicit Window(drivers::graphics::opengl::Context const& context) noexcept;
    explicit Window(std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>&& window) noexcept;

    explicit operator bool() const noexcept { return m_window != nullptr; }

    [[nodiscard]] SDL_Window* getSdlWindow() const noexcept { return m_window.get(); };

    void display() const noexcept;
    bool makeCurrent(drivers::graphics::opengl::Context const& context) const noexcept;
    bool pollEvents() noexcept;
private:
    SDLWindow m_window{nullptr, SDL_DestroyWindow};
};

} // display

#endif //WINDOW_H
