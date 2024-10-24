//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//Core functionality of the engine.

#include "engine/core.h"
#include "engine/window.h"
#include "engine/command.h"
#include "engine/component.h"

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
    std::shared_ptr<CameraComponent> Core::camera_;
    

    struct Core::CoreData {
      std::unique_ptr<DisplayList> display_list;
      bool isRunning;

      //Maybe change this to window
      float delta_time;
      float last_frame;
      float max_fps = 60.0f;

      std::unique_ptr<Window> window;
      std::shared_ptr<EngineInput> input;
      void InitGLFW() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
      }
    };

    Core::Core() {
      data_ = std::make_unique<CoreData>();
      data_->window = std::make_unique<Window>();
      entity_manager_ = std::make_unique<EntityManager>();
      data_->display_list = std::make_unique<DisplayList>();
      data_->input = std::make_shared<EngineInput>();
      data_->isRunning = true;
      data_->delta_time = 0.0f;
      data_->last_frame = 0.0f;
    }

    Core::~Core() {}

    bool Core::InitializeCore() {
      data_->InitGLFW();
      data_->window->SetWindowData("OpenGL Engine", 1280, 720); //TODO: Change this to a config file
      if (!data_->window->InitWindow()) {
        return false;
      }
      data_->input->BindCallbacks(data_->window->GetWindow());
      return true;
    }

    void Core::DeinitializeCore() {
      glfwTerminate();
    }

    void* Core::GetWindow() const {
      if (data_->window) {
        return data_->window->GetWindow();
      }
      return nullptr;
    }

    bool Core::RunningState() const {
      return data_->isRunning;
    }


    void Core::BufferHandler() {
      data_->window->SwapBuffers();
    }

    void Core::EventsHandler() {
      glfwPollEvents();
      //glfwWaitEvents();
    }

    void Core::Update() {
      data_->display_list->Clear();
      data_->display_list->AddClearCommand(0.2f, 0.3f, 0.3f, 1.0f);

      //TODO: Uncomment and check where is the error.
      for (auto& entity : entity_manager_->GetEntities()) {
        if (auto sharedEntity = entity.lock()) {
          data_->display_list->AddDrawCommand(*sharedEntity);
        }
      }
      if (camera_ != nullptr) {
        camera_->MoveCamera();
      }

      if (EngineInput::IsKeyPressed(EngineInput::KeyNames::kKeyNames_Escape))
      {
        data_->isRunning = false;
      }
    }

    void Core::Render() {
      data_->display_list->Execute();
    }

    void Core::FPS() {
      LOG_F(INFO, "FPS: %f", 1.0f / data_->delta_time);
        
      float currentFrame = static_cast<float>(glfwGetTime());
      data_->delta_time = currentFrame - data_->last_frame;
      data_->last_frame = currentFrame;
      delta_time = data_->delta_time;

      float frameTime = 1.0f / data_->max_fps;
      while (data_->delta_time < frameTime) {
        data_->delta_time = static_cast<float>(glfwGetTime()) - data_->last_frame;
      }
    }
  } // namespace Engine

} // namespace OpenGLEngine