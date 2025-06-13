//
// Created by fumosoftware on 5/20/2025.
//

#include <iostream>

#include <libfumo/rendering_engine.h>
#include <libfumo/rendering_window.h>

int main(int argc, char** argv)
{
  fumo::RenderingEngine re{};
  fumo::RenderingWindow win{&re};

  while(true) {
    if(auto const res = win.pollEvents(); res == false) {
      break;
    }

    std::cout << "Running...\n";
  }
  return 0;
}