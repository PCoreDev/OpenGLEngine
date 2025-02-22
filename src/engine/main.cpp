/*****************************************************************//**
 * \file   main.cpp
 * \brief  main file of the engine
 * 
 * \author Pablo "Pau" Core Palmero
 * \email p.core.dev@outlook.com
 * \date   28-May-2024
 *********************************************************************/

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <memory>
//#include <fstream>
//#include <string>

#include "engine/core.h"
#include "engine/entity_manager.h"
#include "engine/entity.h"
#include "engine/component.h"
#include "engine/window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "loguru/loguru.hpp"

#include "imgui/imgui.h"

int main(int argc, char** argv){
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//First step initialize loguru and create the core of the engine.
//Initialize loguru
  loguru::init(argc, argv);
  loguru::add_file("../../../data/log/engine.log", loguru::Truncate, loguru::Verbosity_MAX);
  LOG_SCOPE_FUNCTION(INFO);

//Create the core of the engine and initialize it.
  std::unique_ptr<OpenGLEngine::Engine::Core> core = std::make_unique<OpenGLEngine::Engine::Core>();
  
  if (core->InitializeCore()) {
    LOG_F(INFO, "Core initialized correctly");
  }
  else {
    LOG_F(INFO, "Core failed to initialize");
  }
  
  OpenGLEngine::main(argc, argv);

  float fov = core->camera_->GetFOV();

  while (core->RunningState())
  {
    //Poll events

    //Update application/game state

    //Render content into a framebuffer

    //Swap/Present framebuffer to the screen

    //Wait for next frame (1/60th of a second)



    if (EngineInput::IsKeyPressed(EngineInput::KeyNames::kKeyNames_Key9)) { core->camera_->SetFOV(++fov); }
    if (EngineInput::IsKeyPressed(EngineInput::KeyNames::kKeyNames_Key0)) { core->camera_->SetFOV(--fov); }
    //Update
    core->Update();
    ////Render
    core->Render();



    core->BufferHandler();
    core->EventsHandler();
    core->FPS();
  }

   core->DeinitializeCore();
  return 0;
}
