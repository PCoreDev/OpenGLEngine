//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//This header contains the functionality of the window class.

#include "engine/window.h"
#include <iostream>



#include "glad/glad.h"
#include "GLFW/glfw3.h"




#include "loguru/loguru.hpp"



namespace OpenGLEngine {


  struct WData {

    std::string name;
    static int width, height;
    static bool update;

    unsigned int fbo;

    GLFWwindow* window;
    GLFWmonitor* monitor;

    bool close;
    bool vsync;
    bool fullscreen;

    WData() : name("OpenGL Engine"), fbo(-1), window(nullptr), monitor(nullptr), close(false), vsync(true), fullscreen(false) {}

    bool CreateOpenGLContext() {
      glfwMakeContextCurrent(window);
      if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
      {
        LOG_F(INFO, "Failed to initialize GLAD");
        return false;
      }

      return true;
    }

    void UpdateData() {
      if (WData::update) {
        if (fullscreen) {
          const GLFWvidmode* mode = glfwGetVideoMode  (monitor);
          glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
          glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mode->width, mode->height);
          //Render Texture
          glBindTexture(GL_TEXTURE_2D, fbo);
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mode->width, mode->height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        }
        else {
          glfwSetWindowMonitor(window, nullptr, 0, 0, width, height, 0);
          glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
          //Render Texture
          glBindTexture(GL_TEXTURE_2D, fbo);
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

        }
        glBindTexture(GL_TEXTURE_2D, 0);
        WData::update = false;
      }
    }
  };

  int WData::width = 1920;
  int WData::height = 1080;
  bool WData::update = false;

  void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
  }

  void window_size_callback(GLFWwindow* window, int width, int height) {
    glfwSetWindowSize(window, width, height);
    WData::width = width;
    WData::height = height;
    WData::update = true;
  }

  Window::Window() {
    wdata_ = std::make_unique<WData>();
    wdata_->name = "OpenGL Engine";
    wdata_->width = 800;
    wdata_->height = 600;
  }

  Window::Window(std::string name, int width, int height) {
    wdata_ = std::make_unique<WData>();
    wdata_->name = name;
    wdata_->width = width;
    wdata_->height = height;
  }

  Window::~Window() {
    wdata_.reset();
  }

  void Window::SetWindowData(std::string name, int width, int height) {
    wdata_->name = name;
    wdata_->width = width;
    wdata_->height = height;
  }

  bool Window::InitWindow() {
    wdata_->monitor = glfwGetPrimaryMonitor();
    wdata_->window = glfwCreateWindow(wdata_->width, wdata_->height, wdata_->name.c_str(), nullptr, nullptr);
    //monitor width >> 1 - Window widht >>1, monitor height >> 1 - Window height >> 1
    int xpos = (glfwGetVideoMode(wdata_->monitor)->width >> 1) - (wdata_->width >> 1);
    int ypos = (glfwGetVideoMode(wdata_->monitor)->height >> 1) - (wdata_->height >> 1);
    glfwSetWindowPos(wdata_->window, xpos, ypos);
    //wdata_->window = glfwCreateWindow(wdata_->width, wdata_->height, wdata_->name.c_str(), wdata_->monitor, wdata_->window);

    if (wdata_->window == NULL) {
      LOG_F(ERROR, "Failed to create GLFW window");
      glfwTerminate();
      return false;
    }


    glfwSetInputMode(wdata_->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetWindowSizeCallback(wdata_->window, window_size_callback);

    glfwSetFramebufferSizeCallback(wdata_->window, framebuffer_size_callback);

    glfwMakeContextCurrent(wdata_->window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
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

  
    LOG_F(INFO, "Succeed to create GLFW window");

    CreateFrameBuffer();

    return true;
  }

  void* Window::GetWindow() const {
    if (wdata_->window) {
      return wdata_->window;
    }

    return nullptr;
  }

  void Window::SwapBuffers() {
    glfwSwapBuffers(wdata_->window);
  }

  bool Window::CloseWindow() {
    return wdata_->close;
  }

  int Window::GetWidth() const {
    return wdata_->width;
  }

  int Window::GetHeight() const {
    return wdata_->height;
  }

  unsigned int Window::GetFBO() const {
    return wdata_->fbo;
  }

  void Window::CreateFrameBuffer() {
    glGenFramebuffers(1, &wdata_->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, wdata_->fbo);
  }

  void Window::Update() {
    wdata_->UpdateData();
  }
  void Window::FullScreen(){
    wdata_->fullscreen = !wdata_->fullscreen;
    WData::update = true;
  }
}
