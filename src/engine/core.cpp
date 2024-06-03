//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//Core functionality of the engine.

#include "engine/core.h"
#include "engine/window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "loguru/loguru.hpp"

namespace OpenGLEngine {

  namespace Engine {

    struct Core::CoreData
    {
      std::unique_ptr<Window> window;
    };

    Core::Core()
    {
      data = std::make_unique<CoreData>();
      data->window = std::make_unique<Window>();
    }
    Core::~Core()
    {
    }
    bool Core::InitializeCore()
    {
      if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
      {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
      }

      glfwInit();
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      data->window->InitWindow("OpenGL Engine", 1280, 720);
      //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


      return true;
    }
    void Core::DeinitializeCore()
    {

    }

    void* Core::GetWindow() const
    {
      if (data->window)
      {
        return data->window->GetWindow();
      }
      return nullptr;
    }

  }
}

