//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//Main file of the engine.

#include <iostream>
#include <memory>

#include "Core.h"


#define PX_SCHED_IMPLEMENTATION 1

int main(int argc, char** argv){
   std::unique_ptr<OpenGLEngine::Engine::Core> core = std::make_unique<OpenGLEngine::Engine::Core>();

   OpenGLEngine::main(argc, argv);

  return 0;
}
