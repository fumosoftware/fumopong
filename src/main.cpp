//
// Created by fumosoftware on 5/20/2025.
//

#include <spdlog/spdlog.h>
#include <fmt/printf.h>
#include <SDL3/SDL.h>

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

    SDL_Window* window = SDL_CreateWindow("Pong", 250, 250, SDL_WINDOW_OPENGL);
    if(window && context.claimWindow(window))
    {
        auto const [_, version] = context.getDriverInfo();
        fmt::print("Driver version: {}", version);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}