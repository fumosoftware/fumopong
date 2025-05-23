//
// Created by fumosoftware on 5/23/2025.
//

#include "window.h"

#include <utility>

#include "../drivers//graphics/opengl/context.h"
#include "spdlog/spdlog.h"

using namespace display;

Window::Window() noexcept :
    m_window{SDL_CreateWindow("", 620, 480, SDL_WINDOW_OPENGL), SDL_DestroyWindow}
{
}

Window::Window(drivers::graphics::opengl::Context const& context) noexcept : Window()
{
    if(!context.claimWindow(m_window.get()))
    {
        spdlog::error("Failed to claim window");
    }
}

Window::Window(
    std::unique_ptr<
        SDL_Window,
        decltype(&SDL_DestroyWindow)>&& window) noexcept :
    m_window{std::exchange(window, nullptr)}
{
}

void Window::display() const noexcept
{
    SDL_GL_SwapWindow(m_window.get());
}

bool Window::makeCurrent(drivers::graphics::opengl::Context const& context) const noexcept
{
    return context.claimWindow(m_window.get());
}

bool Window::pollEvents() noexcept
{
    SDL_Event event{};
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_EVENT_QUIT) return false;
    }

    return true;
}
