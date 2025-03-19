//
// Created by fumosoftware on 3/18/2025.
//

#include "device_driver.h"
#include "glad/glad.h"

void OpenGLDeviceDriver::set_clear_color(float r, float g, float b, float a) {
  glClearColor(r, g, b, a);
}

void OpenGLDeviceDriver::clear_buffer() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
