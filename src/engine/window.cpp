//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//This header contains the functionality of the window class.

#include "window.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace OpenGLEngine
{

  struct WData {
    unsigned int width;
    unsigned int height;
    GLFWwindow* window;

  };

  Window::Window()
  {
    wdata_ = std::make_unique<WData>();
  }

  Window::~Window()
  {
    wdata_.reset();
  }

  int Window::InitWindow(const char* title, int width, int height, bool fullscreen)
  {

    return 0;
  }
}