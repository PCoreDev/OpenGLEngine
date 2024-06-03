//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//This header contains the functionality of the window class.

#include "engine/window.h"
#include <iostream>

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
    wdata_->window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (wdata_->window == NULL)
    {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
    }
    glfwMakeContextCurrent(wdata_->window);
    glViewport(0, 0, 800, 600);
    return 0;
  }


  void* Window::GetWindow() const
  {
    if (wdata_->window)
    {
      return wdata_->window;
    }
    return nullptr;
  }
}