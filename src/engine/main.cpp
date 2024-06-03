//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//Main file of the engine.

#include <iostream>
#include <memory>

#include "engine/core.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "loguru/loguru.hpp"


#define PX_SCHED_IMPLEMENTATION 1

int main(int argc, char** argv){
  //Initialize loguru
  loguru::init(argc, argv);
  loguru::add_file("../../data/log/engine.log", loguru::Append, loguru::Verbosity_MAX);
  LOG_SCOPE_FUNCTION(INFO);

  std::unique_ptr<OpenGLEngine::Engine::Core> core = std::make_unique<OpenGLEngine::Engine::Core>();
  
  if (core->InitializeCore()) {
    LOG_F(INFO, "Core initialized correctly");
  }
  else {
    LOG_F(INFO, "Core failed to initialize");
  }

  while (!core->RunningState())
  {
    //Input
    core->Input();
    //Update
    //Render
    core->EventsHandler();
    core->BufferHandler();
  }

   core->DeinitializeCore();
  return 0;
}
