//
// Created by fumosoftware on 5/22/2025.
//

#include "context.h"

#include <utility>

#include "glad.h"
#include "spdlog/spdlog.h"

using namespace drivers::graphics::opengl;

Context::Context() noexcept :
    m_glContext{
        []()->SDL_GLContext {
            using Window = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
            // hack to create a headless opengl context
            // Request an OpenGL 4.5 context (should be core)
            SDL_GL_LoadLibrary(nullptr);
            SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
            // Also request a depth buffer
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

            Window const window{SDL_CreateWindow("", 1, 1, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL), SDL_DestroyWindow};
            auto ctx = SDL_GL_CreateContext(window.get());
            if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress)))
            {
                spdlog::error("Failed to load OpenGL with GLAD");
            }
            return ctx;
        }(), SDL_GL_DestroyContext}
{
    // load opengl functions with glad here
}

Context::Context(std::unique_ptr<
    SDL_GLContextState, decltype(&SDL_GL_DestroyContext)
    >&& glContext) noexcept : m_glContext{std::exchange(glContext, nullptr)}
{

}

Context::Context(Context&& other) noexcept :
    m_glContext {std::exchange(other.m_glContext, nullptr)}
{}

Context& Context::operator=(Context&& other) noexcept
{
    this->m_glContext = std::exchange(other.m_glContext, nullptr);
    return *this;
}

DriverInfo Context::getDriverInfo() const noexcept
{
    return DriverInfo{
        .driverVersionString = reinterpret_cast<char const*>(glGetString(GL_VERSION)),
    };
}

bool Context::claimWindow(SDL_Window* window) noexcept
{
    return SDL_GL_MakeCurrent(window, m_glContext.get());
}
