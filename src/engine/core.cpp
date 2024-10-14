//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//Core functionality of the engine.

#include "engine/core.h"
#include "engine/window.h"
#include "engine/command.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "loguru/loguru.hpp"

//Callback function for the window size
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//  glViewport(0, 0, width, height);
//}

namespace OpenGLEngine {

  namespace Engine {

    std::unique_ptr<EntityManager> Core::entity_manager_ = nullptr;

    struct Core::CoreData {
      std::unique_ptr<DisplayList> display_list;
      bool isRunning = true;
      std::unique_ptr<Window> window;
      void InitGLFW() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
      }
    };

    Core::Core() {
      data = std::make_unique<CoreData>();
      data->window = std::make_unique<Window>();
      entity_manager_ = std::make_unique<EntityManager>();
      data->display_list = std::make_unique<DisplayList>();
    }

    Core::~Core() {}

    bool Core::InitializeCore() {
      data->InitGLFW();
      data->window->SetWindowData("OpenGL Engine", 1280, 720); //TODO: Change this to a config file
      if (!data->window->InitWindow()) {
        return false;
      }
      return true;
    }

    void Core::DeinitializeCore() {
      glfwTerminate();
    }

    void* Core::GetWindow() const {
      if (data->window) {
        return data->window->GetWindow();
      }
      return nullptr;
    }

    bool Core::RunningState() const {
      return data->window->CloseWindow();
    }

    void Core::Input() {
      data->window->InputHandler();
    }

    void Core::BufferHandler() {
      data->window->SwapBuffers();
    }

    void Core::EventsHandler() {
      glfwPollEvents();
    }

    void Core::Update() {
      data->display_list->Clear();
      data->display_list->AddClearCommand(0.2f, 0.3f, 0.3f, 1.0f);
      /*for (auto& entity : entity_manager_->GetEntities()) {
        if (auto sharedEntity = entity.lock()) {
          data->display_list->AddDrawCommand(*sharedEntity);
        }
      }*/
    }

    void Core::Render() {
      data->display_list->Execute();
    }

  } // namespace Engine

} // namespace OpenGLEngine