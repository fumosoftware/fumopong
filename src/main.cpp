//
// Created by fumosoftware on 3/18/2025.
//

#include <memory>

#include <SDL3/SDL.h>
#include <cstdlib>
#include <glad/glad.h>
#include <iostream>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

namespace {
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window{nullptr, SDL_DestroyWindow};
  std::unique_ptr<SDL_GLContextState, decltype(&SDL_GL_DestroyContext)> context{nullptr, SDL_GL_DestroyContext};

  unsigned int VBO{0};
  unsigned int VAO{0};
  unsigned int  EBO{0};
  unsigned int vertexShader{0};
  unsigned int fragmentShader{0};
  unsigned int shaderProgram{0};
  unsigned int textureID{0};

  float vertices[] = {
    // positions   // texture coords
    1.0, 1.0f,   1.0f, 1.0f,   // top right
    1.0f, -1.0f,   1.0f, 0.0f,   // bottom right
    -1.0, -1.0f,   0.0f, 0.0f,   // bottom left
    -1.0f,  1.0f,   0.0f, 1.0f    // top left
};

  unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};

  const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec4 aPos;\n"
  //"layout (location = 1) in vec2 aTexCoord;\n"
"\n"
  "out vec2 TexCoord;\n"
  "\n"
  "uniform mat4 projection;\n"
  "uniform mat4 view;\n"
  "uniform mat4 model;\n"
"\n"
  "void main()\n"
  "{\n"
    "TexCoord = aPos.zw;\n"
    "gl_Position = projection * view * model * vec4(aPos.xy, 0.0f, 1.0f);\n"
  "}\0";

  const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
  "\n"
  "in vec3 ourColor;\n"
  "in vec2 TexCoord;\n"
"\n"
  "uniform sampler2D ourTexture;\n"
"\n"
  "void main()\n"
  "{\n"
    "FragColor = texture(ourTexture, TexCoord);\n"
  "}\0";

  bool initialize_sdl();
  bool create_window();
  bool create_opengl_context();
  bool load_opengl_functions();
  bool initialize_opengl();
  void shutdown_opengl();


} // namespace

int main(int argc, char** argv) {

  if(!initialize_sdl()) return -1;
  if(!create_window()) return -1;
  if(!create_opengl_context()) return -1;
  if(!load_opengl_functions()) return -1;
  if(!initialize_opengl()) return -1;

  SDL_Event event{};
  bool isRunning {true};

  while(isRunning) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_EVENT_QUIT) isRunning = false;
    }
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);


    auto const w = 320.f;
    auto const h = 240.f;
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.f, 0.f, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(1.f * w, 1.f * h, 0.0f)); // move origin of rotation to center of quad
  //  model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-1.f * w, -1.f * h, 0.0f)); // move origin back
    model = glm::translate(model, glm::vec3(0.f, 64.f, 0.0f)); // move around
    //model = glm::translate(model, glm::vec3(320.f, 0.f, 0.f));

    model = glm::scale(model, glm::vec3(32.f, 32.f, 1.0f)); // last scale

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));

    glm::mat4 projection = glm::ortho(0.0f, 640.0f, 480.0f, 0.0f, -1.0f, 1.0f);
    //glm::mat4 projection = glm::mat4(1.0f);


    glUseProgram(shaderProgram);
    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    SDL_GL_SwapWindow(window.get());
  }

  return 0;
}

namespace {
  bool initialize_sdl() {
    if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
      return false;
    }

    atexit(SDL_Quit);
    return true;
  }

  bool create_window() {
    window.reset(SDL_CreateWindow("Pong", 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE));

    return window.get() != nullptr;
  }

  bool create_opengl_context() {
    if(!window) return false;
    context.reset(SDL_GL_CreateContext(window.get()));

    return context.get() != nullptr;
  }

  bool load_opengl_functions() {
    auto const version = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress)) != 0;
    std::cout << glGetString(GL_VERSION) <<"\n";

    return version;
  }

  bool initialize_opengl() {


    int width, height, nrChannels;
    unsigned char *data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    //glEnableVertexAttribArray(1);


    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    std::atexit(shutdown_opengl);
    return true;
  }

  void shutdown_opengl() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBO);

    glDeleteTextures(1, &textureID);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);
  }
}