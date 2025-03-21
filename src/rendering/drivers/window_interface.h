//
// Created by fumosoftware on 3/20/2025.
//

#ifndef WINDOW_INTERFACE_H
#define WINDOW_INTERFACE_H

class IWindow {
public:
  virtual ~IWindow() noexcept = default;

  virtual void present() noexcept = 0;
  virtual void clear() noexcept = 0;
protected:
  IWindow() = default;
};
#endif //WINDOW_INTERFACE_H
