//
// Created by fumosoftware on 5/22/2025.
//

#ifndef DRIVERS_GRAPHISC_OPENGL_CONTEXT_H
#define DRIVERS_GRAPHICS_OPENGL_CONTEXT_H

#include <memory>
#include <SDL3/SDL.h>

namespace drivers {
namespace graphics {
namespace opengl {

struct DriverInfo
{
    std::string_view driverName{};
    std::string_view driverVersionString{};
};

class Context {
    using GLContext = std::unique_ptr<SDL_GLContextState, decltype(&SDL_GL_DestroyContext)>;

public:
    Context() noexcept;
    explicit Context(std::unique_ptr<SDL_GLContextState, decltype(&SDL_GL_DestroyContext)>&& glContext) noexcept;

    Context(Context&& other) noexcept;
    Context& operator=(Context&& other) noexcept;

    explicit operator bool() const noexcept { return m_glContext != nullptr; }

    [[nodiscard]] DriverInfo getDriverInfo() const noexcept;

    [[nodiscard]] bool claimWindow(SDL_Window* window) noexcept;
private:
    GLContext m_glContext{nullptr, SDL_GL_DestroyContext};
};

} // opengl
} // graphics
} // drivers

#endif //DRIVERS_GRAPHICS_OPENGL_CONTEXT_H
