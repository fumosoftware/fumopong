//
// Created by fumosoftware on 5/29/2025.
//

#ifndef RENDERINGCONTEXT_H
#define RENDERINGCONTEXT_H

#include <SDL3/SDL.h>
#include <memory>

namespace fumo {

class RenderingContext {
public:
  RenderingContext();

  RenderingContext(const RenderingContext &) = delete;
  RenderingContext &operator=(const RenderingContext &) = delete;

  RenderingContext(RenderingContext &&) noexcept;
  RenderingContext &operator=(RenderingContext &&) noexcept;

  bool operator!() const { return m_glContext == nullptr; }
private:
  using GLContext = std::unique_ptr<SDL_GLContextState, decltype(&SDL_GL_DestroyContext)>;
  GLContext m_glContext{nullptr, SDL_GL_DestroyContext};

};

} // fumo

#endif //RENDERINGCONTEXT_H
