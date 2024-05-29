//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//Core functionality of the engine.

#include "core.h"
#include "window.h"

//#include "glad/glad.h"
//#include "GLFW/glfw3.h"

#include "loguru.hpp"

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
      data->window->InitWindow("OpenGL Engine", 1280, 720);
      return true;
    }
    void Core::DeinitializeCore()
    {

    }

  }
}

