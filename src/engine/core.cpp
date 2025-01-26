//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//Core functionality of the engine.

#include "engine/core.h"
#include "engine/window.h"
#include "engine/shader.h"
#include "engine/command.h"
#include "engine/component.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "loguru/loguru.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <windows.h>

#include <thread>

#include <array>

//Callback function for the window size
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//  glViewport(0, 0, width, height);
//}

namespace OpenGLEngine {

  namespace Engine {

    std::shared_ptr<EntityManager> Core::entity_manager_ = nullptr;
    std::shared_ptr<CameraComponent> Core::camera_ = nullptr;
    std::shared_ptr<Shader> Core::shader_ = nullptr;


    struct Core::CoreData {
      std::unique_ptr<DisplayList> display_list;
      bool isRunning;
      bool show_mouse;

      //Maybe change this to window
      float delta_time;
      float last_frame;
      float max_fps = 60.0f;

      std::unique_ptr<Window> window;
      std::shared_ptr<EngineInput> input;

      std::shared_ptr<Shader> framebuffer_shader;
      unsigned int framebuffer_texture;
      unsigned int screen_quad_vao;
      unsigned int screen_quad_vbo;
      unsigned int screen_quad_nbo;
      unsigned int screen_quad_ubo;
      unsigned int screen_quad_ibo;

      void InitGLFW() {
        glfwInit();
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

      }
    };

    Core::Core() {
      data_ = std::make_unique<CoreData>();
      data_->window = std::make_unique<Window>();
      shader_ = std::make_shared<Shader>();
      entity_manager_ = std::make_shared<EntityManager>();
      data_->display_list = std::make_unique<DisplayList>();
      data_->input = std::make_shared<EngineInput>();
      data_->framebuffer_shader = std::make_shared<Shader>();
      data_->isRunning = true;
      data_->delta_time = 0.0f;
      data_->last_frame = 0.0f;
      data_->show_mouse = false;
    }

    Core::~Core() {}

    bool Core::InitializeCore() {
      bool state = true;
      data_->InitGLFW();
      data_->window->SetWindowData("OpenGL Engine", GetSystemMetrics(SM_CXSCREEN) >> 1, GetSystemMetrics(SM_CYSCREEN) >> 1); //TODO: Change this to a config file
      if (!data_->window->InitWindow()) {
        state = false;
      }
      data_->input->BindCallbacks(data_->window->GetWindow());

      if (!shader_->LoadShader("../../src/engine/shaders/core/vertex_core.glsl", "../../src/engine/shaders/core/fragment_core.glsl")) {
        state = false;
      }

      if (!data_->framebuffer_shader->LoadShader("../../src/engine/shaders/core/framebuffer_vertex.glsl", "../../src/engine/shaders/core/framebuffer_fragment.glsl")) {
        state = false;
        LOG_F(ERROR, "Failed to load framebuffer shader");
      }

      CreateRenderTexture();
      CreateRenderBufferObject();
      CreateRenderQuad();
      auto fbo_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
      if (fbo_status != GL_FRAMEBUFFER_COMPLETE) {
        LOG_F(ERROR, "Framebuffer is not complete! %d", fbo_status);
      }
      else
      {
        LOG_F(INFO, "Framebuffer is complete!");
      }


      
      //Imgui
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      ImGuiIO& io = ImGui::GetIO(); (void)io;
      ImGui::StyleColorsDark();

      //Init imgui backends
      ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(data_->window->GetWindow()), true);
      ImGui_ImplOpenGL3_Init("#version 460");

      return state;
    }

    void Core::DeinitializeCore() {
      glfwDestroyWindow(static_cast<GLFWwindow*>(data_->window->GetWindow()));
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

      glFlush(); //check if this is necessary



      //TODO Change this to a function, this is for cleaning the buffer
      glBindVertexArray(0);
      glUseProgram(0);
      glActiveTexture(0);
      glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Core::EventsHandler() {
      glfwPollEvents();
    }

    void Core::Update() {

      //Imgui
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      DebugCoreStats();

      if (EngineInput::IsKeyPressed(EngineInput::KeyNames::kKeyNames_F1)) {
        data_->show_mouse = !data_->show_mouse;
      }


      if (data_->show_mouse) {
        glfwSetInputMode(static_cast<GLFWwindow*>(data_->window->GetWindow()), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      }
      else {
        glfwSetInputMode(static_cast<GLFWwindow*>(data_->window->GetWindow()), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      }


      std::thread cameraThread([this]() {
        if (camera_ != nullptr && !data_->show_mouse) {
          camera_->MoveCamera();
        }
      });

      std::thread inputThread([this]() {
        if (EngineInput::IsKeyPressed(EngineInput::KeyNames::kKeyNames_Escape)) {
          data_->isRunning = false;
        }
      });

      // Join threads to ensure they complete before exiting the function
      cameraThread.join();
      inputThread.join();

    }

    void Core::Render() {

      data_->display_list->Clear();

      ImGui::Render();
      data_->display_list->AddDrawRenderBufferCommand(*entity_manager_, *data_->framebuffer_shader, data_->window->GetFBO(), data_->framebuffer_texture, data_->screen_quad_vao, data_->screen_quad_ibo);

      data_->display_list->Execute();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Core::FPS() {
      float currentFrame = static_cast<float>(glfwGetTime());
      data_->delta_time = currentFrame - data_->last_frame;
      data_->last_frame = currentFrame;
      delta_time = data_->delta_time;

      float frameTime = 1.0f / data_->max_fps;
      while (data_->delta_time < frameTime) {
        data_->delta_time = static_cast<float>(glfwGetTime()) - data_->last_frame;
      }
    }

    void Core::CreateRenderTexture(){
      
      glGenTextures(1, &data_->framebuffer_texture);
      glBindTexture(GL_TEXTURE_2D, data_->framebuffer_texture);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data_->window->GetWidth(), data_->window->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, data_->framebuffer_texture, 0);
    }

    void Core::CreateRenderBufferObject(){
      unsigned int rbo;
      glGenRenderbuffers(1, &rbo);
      glBindRenderbuffer(GL_RENDERBUFFER, rbo);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, data_->window->GetWidth(), data_->window->GetHeight());
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

      if (auto fbostatus = glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOG_F(ERROR, "Framebuffer is not complete! %d", fbostatus);
      }
    }

    void Core::CreateRenderQuad(){
      constexpr std::array<float, 12> vertex_data = {
           -1.0f,  1.0f, 0.0f,
           -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            1.0f,  1.0f, 0.0f
      };

      constexpr std::array<unsigned int, 6> index_data = {
          0, 1, 3,
          1, 2, 3
      };

      constexpr std::array<float, 8> uv_data = {
             0.0f, 0.0f,
             0.0f, 1.0f,
             1.0f, 1.0f,
             1.0f, 0.0f
      };

      glCreateBuffers(1, &data_->screen_quad_vbo); //vertex buffer object
      glCreateBuffers(1, &data_->screen_quad_ubo); //uv buffer object
      glCreateBuffers(1, &data_->screen_quad_ibo); //index buffer object

      glNamedBufferStorage(data_->screen_quad_vbo, vertex_data.size() * sizeof(float), vertex_data.data(), GL_DYNAMIC_STORAGE_BIT);
      glNamedBufferStorage(data_->screen_quad_ubo, uv_data.size() * sizeof(float), uv_data.data(), GL_DYNAMIC_STORAGE_BIT);
      glNamedBufferStorage(data_->screen_quad_ibo, index_data.size() * sizeof(unsigned int), index_data.data(), GL_DYNAMIC_STORAGE_BIT);

      glCreateVertexArrays(1, &data_->screen_quad_vao);

      glVertexArrayVertexBuffer(data_->screen_quad_vao, 0, data_->screen_quad_vbo, 0, 3 * sizeof(float)); //Vertex
      glVertexArrayVertexBuffer(data_->screen_quad_vao, 1, data_->screen_quad_ubo, 0, 2 * sizeof(float)); //UV

      glEnableVertexArrayAttrib(data_->screen_quad_vao, 0);
      glEnableVertexArrayAttrib(data_->screen_quad_vao, 1);

      glVertexArrayAttribFormat(data_->screen_quad_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
      glVertexArrayAttribFormat(data_->screen_quad_vao, 1, 2, GL_FLOAT, GL_FALSE, 0);

      glVertexArrayAttribBinding(data_->screen_quad_vao, 0, 0);
      glVertexArrayAttribBinding(data_->screen_quad_vao, 1, 1);

    }

    void Core::DebugCoreStats(){
      ImGui::Begin("Core Stats");
      ImGui::Text("FPS: %f", 1.0f / data_->delta_time);
      ImGui::SliderFloat("Max FPS", &data_->max_fps, 1.0f, 120.0f);
      ImGui::Text("Number of entitites: %d", entity_manager_->GetNumberOfEntities());
      ImGui::End();
    }
  } // namespace Engine

} // namespace OpenGLEngine
