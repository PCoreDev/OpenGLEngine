//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//Main file of the engine.

#include <memory>
#include <fstream>
#include <string>

#include "engine/core.h"
#include "engine/entity_manager.h"
#include "engine/entity.h"
#include "engine/component.h"
#include "engine/window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "loguru/loguru.hpp"


#define PX_SCHED_IMPLEMENTATION 1

//TODO: Make it multi-threaded with PX_SCHED

int main(int argc, char** argv){
//First step initialize loguru and create the core of the engine.
//Initialize loguru
  loguru::init(argc, argv);
  loguru::add_file("../../../data/log/engine.log", loguru::Append, loguru::Verbosity_MAX);
  LOG_SCOPE_FUNCTION(INFO);

//Create the core of the engine and initialize it.
  std::unique_ptr<OpenGLEngine::Engine::Core> core = std::make_unique<OpenGLEngine::Engine::Core>();
  
  if (core->InitializeCore()) {
    LOG_F(INFO, "Core initialized correctly");
  }
  else {
    LOG_F(INFO, "Core failed to initialize");
  }
  
  //OpenGLEngine::main(argc, argv);

  std::shared_ptr<Entity> entity = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
  std::shared_ptr<Entity> camera = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
  camera->AddTransformComponent();
  camera->GetTransformComponent()->SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));
  camera->AddCameraComponent();
  camera->GetCameraComponent()->SetMainCamera();

  entity->AddMeshComponent();
  entity->AddTransformComponent();
  entity->GetTransformComponent()->SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
  entity->GetMeshComponent()->Cube();
  entity->AddShaderComponent();
  entity->AddMaterialComponent();
  entity->GetMaterialComponent()->LoadTexture("../../data/textures/wood.jpg");
  entity->GetShaderComponent()->SetVertexShaderPath("../../src/engine/shaders/default3D.vert");
  entity->GetShaderComponent()->SetFragmentShaderPath("../../src/engine/shaders/default3D.frag");
  entity->GetShaderComponent()->ProcessShader();


  while (!core->RunningState())
  {
    //Input
    if (EngineInput::IsKeyPressed(EngineInput::KeyNames::kKeyNames_KeyW))
    {
      entity->GetTransformComponent()->SetRotation(entity->GetTransformComponent()->GetRotation() + glm::vec3(0.3f, 0.0f, 0.0f));
    }

    //Input
    if (EngineInput::IsKeyPressed(EngineInput::KeyNames::kKeyNames_KeyS))
    {
      entity->GetTransformComponent()->SetRotation(entity->GetTransformComponent()->GetRotation() + glm::vec3(-0.3f, 0.0f, 0.0f));
    }

    //Input
    if (EngineInput::IsKeyPressed(EngineInput::KeyNames::kKeyNames_KeyA))
    {
      entity->GetTransformComponent()->SetRotation(entity->GetTransformComponent()->GetRotation() + glm::vec3(0.0f, 0.3f, 0.0f));
    }

    //Input
    if (EngineInput::IsKeyPressed(EngineInput::KeyNames::kKeyNames_KeyD))
    {
      entity->GetTransformComponent()->SetRotation(entity->GetTransformComponent()->GetRotation() + glm::vec3(0.0f, -0.3f, 0.0f));
    }

    //Update
    core->Update();
    ////Render
    core->Render();

    core->EventsHandler();
    core->BufferHandler();
  }

   core->DeinitializeCore();
  return 0;
}
