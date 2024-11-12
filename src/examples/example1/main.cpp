//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//Main file of the user.

#include "engine/core.h"
#include "engine/entity.h"
#include "engine/window.h"
#include "engine/components/camera_component.h"
#include "engine/components/mesh_component.h"
#include "engine/components/material_component.h"
#include "engine/components/shader_component.h"
#include "engine/components/transform_component.h"
#include "engine/components/render_component.h"



int OpenGLEngine::main(int argc, char** argv)
{
  std::shared_ptr<Entity> camera = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
  //camera->AddTransformComponent();
  camera->AddCameraComponent();
  camera->GetCameraComponent()->SetMainCamera();

  std::shared_ptr<Entity> entity1 = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
  entity1->AddMeshComponent();
  entity1->AddRenderComponent();
  entity1->AddTransformComponent();
  entity1->GetTransformComponent()->SetPosition(glm::vec3(0.0f, -130.0f, 0.0f));
  entity1->GetTransformComponent()->SetRotation(glm::vec3(-90.0f, 0.0f, 0.0f));
  entity1->GetTransformComponent()->SetScale(glm::vec3(100.0f, 100.0f, 100.0f));
  entity1->GetMeshComponent()->Square();
  //entity1->AddShaderComponent();
  //entity1->GetShaderComponent()->LoadShader("../../src/engine/shaders/default3D.vert", ShaderComponent::Vertex);
  //entity1->GetShaderComponent()->LoadShader("../../src/engine/shaders/default3D.frag", ShaderComponent::Fragment);
  //entity1->AddMaterialComponent();
  //entity1->GetMaterialComponent()->LoadTexture("../../data/textures/wood.jpg");
  //entity1->GetShaderComponent()->SetTexture("texture_sampler", 0);
  //entity1->GetShaderComponent()->SetMat4("model_matrix", entity1->GetTransformComponent()->GetModelMatrix());
  //entity1->GetShaderComponent()->SetMat4("view_matrix", OpenGLEngine::Engine::Core::camera_->GetViewMatrix());
  //entity1->GetShaderComponent()->SetMat4("projection_matrix", OpenGLEngine::Engine::Core::camera_->GetProjectionMatrix());
  
  int num_cubes = 3;
  for (int i = 0; i < num_cubes; i++) {
    for (int j = 0; j < num_cubes; j++) {
      for (int z = 0; z < num_cubes; z++) {
        std::shared_ptr<Entity> entity = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
        entity->AddMeshComponent();
        entity->AddRenderComponent();
        entity->AddTransformComponent();
        entity->GetTransformComponent()->SetPosition(glm::vec3(i * 10.0f, j * 10.0f, z * 10.0f));
        entity->GetMeshComponent()->Cube();
        entity->AddMaterialComponent();
        entity->GetMaterialComponent()->LoadTexture("../../data/textures/wood.jpg");
        entity->AddShaderComponent();
        entity->GetShaderComponent()->LoadShader("../../src/engine/shaders/default3D.vert", ShaderComponent::Vertex);
        entity->GetShaderComponent()->LoadShader("../../src/engine/shaders/default3D.frag", ShaderComponent::Fragment);
        //entity->GetShaderComponent()->SetTexture("texture_sampler", 0);
        //entity->GetShaderComponent()->SetMat4("model_matrix", entity->GetTransformComponent()->GetModelMatrix());
        //entity->GetShaderComponent()->SetMat4("view_matrix", OpenGLEngine::Engine::Core::camera_->GetViewMatrix());
        //entity->GetShaderComponent()->SetMat4("projection_matrix", OpenGLEngine::Engine::Core::camera_->GetProjectionMatrix());
      }
    }
  }

  std::shared_ptr<Entity> entity2 = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
  entity2->AddMeshComponent();
  entity2->AddRenderComponent();
  entity2->AddTransformComponent();
  entity2->GetTransformComponent()->SetPosition(glm::vec3(0.0f, 100.0f, 0.0f));
  entity2->GetTransformComponent()->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
  entity2->AddMaterialComponent();
  entity2->GetMeshComponent()->LoadOBJ("../../data/models/Overlord/Overlord.obj", "../../data/models/Overlord/textures/");
  entity2->GetMeshComponent()->SetBack(true);
  entity2->GetMaterialComponent()->LoadTexture("../../data/textures/wood.jpg");
  /*entity2->AddShaderComponent();
  
  entity2->GetShaderComponent()->LoadShader("../../src/engine/shaders/default3D.vert", ShaderComponent::Vertex);
  entity2->GetShaderComponent()->LoadShader("../../src/engine/shaders/default3D.frag", ShaderComponent::Fragment);*/
  //entity2->GetShaderComponent()->SetTexture("texture_sampler", 0);
  //entity2->GetShaderComponent()->SetMat4("model_matrix", entity2->GetTransformComponent()->GetModelMatrix());
  //entity2->GetShaderComponent()->SetMat4("view_matrix", OpenGLEngine::Engine::Core::camera_->GetViewMatrix());
  //entity2->GetShaderComponent()->SetMat4("projection_matrix", OpenGLEngine::Engine::Core::camera_->GetProjectionMatrix());

  std::shared_ptr<Entity> entity3 = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
  entity3->AddMeshComponent();
  entity3->AddRenderComponent();
  entity3->AddTransformComponent();
  entity3->GetTransformComponent()->SetPosition(glm::vec3(0.0f, 100.0f, 0.0f));
  entity3->GetTransformComponent()->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
  entity3->AddMaterialComponent();
  entity3->GetMeshComponent()->LoadOBJ("../../data/models/gomorrah/gomorrah.obj", "../../data/models/gomorrah/");
  entity3->GetMeshComponent()->SetBack(true);
  entity3->GetMaterialComponent()->LoadTexture("../../data/textures/wood.jpg");
 /* entity3->AddShaderComponent();
  entity3->GetShaderComponent()->LoadShader("../../src/engine/shaders/default3D.vert", ShaderComponent::Vertex);
  entity3->GetShaderComponent()->LoadShader("../../src/engine/shaders/default3D.frag", ShaderComponent::Fragment);*/
  //entity3->GetShaderComponent()->SetTexture("texture_sampler", 0);
  //entity3->GetShaderComponent()->SetMat4("model_matrix", entity3->GetTransformComponent()->GetModelMatrix());
  //entity3->GetShaderComponent()->SetMat4("view_matrix", OpenGLEngine::Engine::Core::camera_->GetViewMatrix());
  //entity3->GetShaderComponent()->SetMat4("projection_matrix", OpenGLEngine::Engine::Core::camera_->GetProjectionMatrix());

  return 0;
}
