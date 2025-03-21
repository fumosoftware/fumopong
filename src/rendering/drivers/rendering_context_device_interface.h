//
// Created by fumosoftware on 3/20/2025.
//

#pragma once

#ifndef RENDERING_CONTEXT_INTERFACE_H
#define RENDERING_CONTEXT_INTERFACE_H

class IWindow;
class IRenderingContextDevice {
public:
  virtual ~IRenderingContextDevice() noexcept = default;

  [[nodiscard]] virtual IWindow* get_main_window() const noexcept = 0;
protected:
  IRenderingContextDevice() = default;
};

#endif //RENDERING_CONTEXT_INTERFACE_H
