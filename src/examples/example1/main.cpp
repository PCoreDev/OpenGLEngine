//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//Main file of the user.

#include "engine/core.h"
#include "engine/entity.h"
#include "engine/window.h"


int OpenGLEngine::main(int argc, char** argv)
{
  std::shared_ptr<Entity> camera = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
  camera->AddTransformComponent();
  camera->AddCameraComponent();
  camera->GetCameraComponent()->SetMainCamera();

  std::shared_ptr<Entity> entity1 = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
  entity1->AddMeshComponent();
  entity1->AddRenderComponent();
  entity1->AddTransformComponent();
  entity1->GetTransformComponent()->SetPosition(glm::vec3(0.0f, -10.0f, 0.0f));
  entity1->GetTransformComponent()->SetScale(glm::vec3(1000.0f, 1.0f, 1000.0f));
  entity1->GetMeshComponent()->Cube();
  entity1->AddShaderComponent();
  entity1->AddMaterialComponent();
  entity1->GetMaterialComponent()->LoadTexture("../../data/textures/wood.jpg");
  entity1->GetShaderComponent()->SetVertexShaderPath("../../src/engine/shaders/default3D.vert");
  entity1->GetShaderComponent()->SetFragmentShaderPath("../../src/engine/shaders/default3D.frag");
  entity1->GetShaderComponent()->ProcessShader();

  for (int i = 0; i < 10; i++) {
    std::shared_ptr<Entity> entity = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
    entity->AddMeshComponent();
    entity->AddRenderComponent();
    entity->AddTransformComponent();
    entity->GetTransformComponent()->SetPosition(glm::vec3((i + 1) * 10.0f, 0.0f, 0.0f));
    entity->GetMeshComponent()->Cube();
    entity->AddShaderComponent();
    entity->AddMaterialComponent();
    entity->GetMaterialComponent()->LoadTexture("../../data/textures/wood.jpg");
    entity->GetShaderComponent()->SetVertexShaderPath("../../src/engine/shaders/default3D.vert");
    entity->GetShaderComponent()->SetFragmentShaderPath("../../src/engine/shaders/default3D.frag");
    entity->GetShaderComponent()->ProcessShader();
  }

  return 0;
}
