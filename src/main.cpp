//
// Created by fumosoftware on 5/20/2025.
//

#include <spdlog/spdlog.h>
#include <fmt/printf.h>
#include <SDL3/SDL.h>

#include <memory>

int main(int argc, char** argv)
{
    spdlog::info("Hello, World!");
    fmt::print("Hello, World!");

    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        spdlog::error("Failed to initialize SDL");
        return -1;
    }

    {
        SDL_Window* window_ptr{};
        SDL_Renderer* renderer_ptr{};
        if(!SDL_CreateWindowAndRenderer("Fumopong", 640, 480, SDL_WINDOW_RESIZABLE, &window_ptr, &renderer_ptr))
        {
            spdlog::error("Failed to create window and renderer");
            return -1;
        }
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window{window_ptr, SDL_DestroyWindow};
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer{renderer_ptr, SDL_DestroyRenderer};

        SDL_Event event{};
        bool is_running = true;
        while(is_running)
        {
            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_EVENT_QUIT) is_running = false;
            }

            SDL_RenderClear(renderer.get());
            SDL_RenderPresent(renderer.get());
        }
    }

    SDL_Quit();
    return 0;
}