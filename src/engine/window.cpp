//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//This header contains the functionality of the window class.

#include "engine/window.h"
#include <iostream>



#include "glad/glad.h"
#include "GLFW/glfw3.h"




#include "loguru/loguru.hpp"



namespace OpenGLEngine
{
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    glViewport(0, 0, width, height);
    //LOG_F(INFO, "FrameBuffer size changed to %d x %d", width, height);
  }

  //void window_size_callback(GLFWwindow* window, int width, int height)
  //{
  //  glfwSetWindowSize(window, width, height);
  //  //LOG_F(INFO, "Window size changed to %d x %d", width, height);
  //}

  struct WData {

    std::string name;
    int width, height;

    int framebuffer_width, framebuffer_height;

    GLFWwindow* window;
    bool close = false;

    bool CreateOpenGLContext()
    {
      glfwMakeContextCurrent(window);
      if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
      {
        LOG_F(INFO, "Failed to initialize GLAD");
        return false;
      }

      return true;
    }
  };

  Window::Window()
  {
    wdata_ = std::make_unique<WData>();
    wdata_->name = "OpenGL Engine";
    wdata_->width = 800;
    wdata_->height = 600;
    wdata_->framebuffer_width = 0;
    wdata_->framebuffer_width = 0;
  }

  Window::Window(std::string name, int width, int height)
  {
    wdata_ = std::make_unique<WData>();
    wdata_->name = name;
    wdata_->width = width;
    wdata_->height = height;
  }

  Window::~Window()
  {
    wdata_.reset();
  }

  void Window::SetWindowData(std::string name, int width, int height)
  {
    wdata_->name = name;
    wdata_->width = width;
    wdata_->height = height;
  }

  bool Window::InitWindow()
  {
    wdata_->window = glfwCreateWindow(wdata_->width, wdata_->height, wdata_->name.c_str(), NULL, NULL);
    if (wdata_->window == NULL)
    {
      //std::cout << "Failed to create GLFW window" << std::endl;
      LOG_F(ERROR, "Failed to create GLFW window");
      glfwTerminate();
      return false;
    }

    LOG_F(INFO, "Succeed to create GLFW window");

    glfwSetInputMode(wdata_->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //glfwSetWindowSizeCallback(wdata_->window, window_size_callback);
    glfwSetFramebufferSizeCallback(wdata_->window, framebuffer_size_callback);

    glfwMakeContextCurrent(wdata_->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      LOG_F(ERROR, "Failed to initialize GLAD");
      return false;
    }

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  

    return true;
  }

  void* Window::GetWindow() const
  {
    if (wdata_->window)
    {
      return wdata_->window;
    }
    return nullptr;
  }

  void Window::SwapBuffers()
  {
    glfwSwapBuffers(wdata_->window);
  }

  bool Window::CloseWindow()
  {
    return wdata_->close;
  }

}