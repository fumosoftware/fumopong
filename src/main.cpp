//
// Created by fumosoftware on 5/20/2025.
//

#include "fumo/renderer/renderingcontext.h"
#include <SDL3/SDL.h>

int main(int argc, char** argv)
{
  if(!SDL_Init(SDL_INIT_VIDEO)) {
    return -1;
  }

  fumo::RenderingContext ctx;
    return 0;
}