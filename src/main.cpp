//
// Created by fumosoftware on 5/20/2025.
//

#include <spdlog/spdlog.h>
#include <fmt/printf.h>
#include <SDL3/SDL.h>

#include "display/window.h"
#include "drivers/graphics/opengl/context.h"

int main(int argc, char** argv)
{
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        spdlog::error("Failed to initialize SDL");
        return -1;
    }

    drivers::graphics::opengl::Context context{};
    if(!context)
    {
        spdlog::error("Failed to create OpenGL context");
    }

    auto window = display::Window(context);
    auto const [_, version] = context.getDriverInfo();
    fmt::print("Driver version: {}", version);

    while(window.pollEvents())
    {
       window.display();
    }

    SDL_Quit();
    return 0;
}