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

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "loguru/loguru.hpp"


#define PX_SCHED_IMPLEMENTATION 1

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
  
  std::shared_ptr<Entity> entity = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
  LOG_F(INFO, "Entity created with id: %d", entity->ID());
  LOG_F(INFO, "Number of entities: %d", OpenGLEngine::Engine::Core::entity_manager_->GetNumberOfEntities());

  entity->AddMeshComponent();
  entity->GetMeshComponent()->Triangle();
  entity->AddShaderComponent();

  while (!core->RunningState())
  {
    //Input
    core->Input();
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
