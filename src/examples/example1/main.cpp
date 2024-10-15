//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//Main file of the user.

#include "engine/core.h"
#include "engine/entity.h"


int OpenGLEngine::main(int argc, char** argv)
{
  std::shared_ptr<Entity> entity = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();

  entity->AddMeshComponent();
  entity->GetMeshComponent()->Cube();
  entity->AddShaderComponent();
  entity->GetShaderComponent()->SetVertexShaderPath("../../src/engine/shaders/default3D.vert");
  entity->GetShaderComponent()->SetFragmentShaderPath("../../src/engine/shaders/default3D.frag");
  entity->GetShaderComponent()->ProcessShader();


  return 0;
}
