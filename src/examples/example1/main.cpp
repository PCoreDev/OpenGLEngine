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
#include "engine/components/light_component.h"



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
  entity1->AddMaterialComponent();
  entity1->GetMaterialComponent()->LoadTexture("../../data/textures/metal.png", MaterialComponent::TextureFormat::Texture2D, MaterialComponent::TextureTarget::Diffuse);
  entity1->GetMaterialComponent()->LoadTexture("../../data/textures/metal.png", MaterialComponent::TextureFormat::Texture2D, MaterialComponent::TextureTarget::Specular);
  entity1->GetMaterialComponent()->SetAmbient(glm::vec3(0.5f));
  entity1->GetMaterialComponent()->SetDiffuse(glm::vec3(0.2f));
  entity1->GetMaterialComponent()->SetSpecular(glm::vec3(1.0f));
  entity1->GetMaterialComponent()->SetShininess(0.0f);

  std::shared_ptr<Entity> light = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
  light->AddMeshComponent();
  light->AddRenderComponent();
  light->AddTransformComponent();
  light->GetTransformComponent()->SetPosition(glm::vec3(0.0f, 100.0f, 0.0f));
  light->GetTransformComponent()->SetScale(glm::vec3(10.0f, 10.0f, 10.0f));
  light->GetMeshComponent()->LoadOBJ("../../data/models/sphere.obj", "../../data/models/");
  light->AddMaterialComponent();
  light->GetMaterialComponent()->LoadTexture("../../data/textures/white.png", MaterialComponent::TextureFormat::Texture2D, MaterialComponent::TextureTarget::Diffuse);
  //light->GetMaterialComponent()->LoadTexture("../../data/textures/metal.png", MaterialComponent::TextureFormat::Texture2D, MaterialComponent::TextureTarget::Specular);
  light->GetMaterialComponent()->SetAmbient(glm::vec3(1.0f, 1.0f, 1.0f));
  light->GetMaterialComponent()->SetDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
  light->GetMaterialComponent()->SetSpecular(glm::vec3(0.0f));
  light->GetMaterialComponent()->SetShininess(0.0f);

  
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
        entity->GetMaterialComponent()->LoadTexture("../../data/textures/container.png", MaterialComponent::TextureFormat::Texture2D, MaterialComponent::TextureTarget::Diffuse);
        entity->GetMaterialComponent()->LoadTexture("../../data/textures/container_specular.png", MaterialComponent::TextureFormat::Texture2D, MaterialComponent::TextureTarget::Specular);
        entity->GetMaterialComponent()->SetAmbient(glm::vec3(0.5f));
        entity->GetMaterialComponent()->SetDiffuse(glm::vec3(0.2f));
        entity->GetMaterialComponent()->SetSpecular(glm::vec3(20.0f));
        entity->GetMaterialComponent()->SetShininess(32.0f);
        //entity->AddShaderComponent();
        //entity->GetShaderComponent()->LoadShader("../../src/engine/shaders/default3D.vert", ShaderComponent::Vertex);
        //entity->GetShaderComponent()->LoadShader("../../src/engine/shaders/default3D.frag", ShaderComponent::Fragment);
      }
    }
  }

  std::shared_ptr<Entity> entity2 = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
  entity2->AddMeshComponent();
  entity2->AddRenderComponent();
  entity2->AddTransformComponent();
  entity2->GetTransformComponent()->SetPosition(glm::vec3(0.0f, 0.0f, 120.0f));
  entity2->GetTransformComponent()->SetScale(glm::vec3(1000.0f, 1000.0f, 1000.0f));
  entity2->AddMaterialComponent();

  entity2->GetMeshComponent()->LoadOBJ("../../data/models/Axe/VikingAxe.obj", "../../data/models/Axe/");


  std::shared_ptr<Entity> entity3 = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
  entity3->AddMeshComponent();
  entity3->AddRenderComponent();
  entity3->AddTransformComponent();
  entity3->GetTransformComponent()->SetPosition(glm::vec3(0.0f, -30.0f, 0.0f));
  //entity3->GetTransformComponent()->SetRotation(glm::vec3(-90.0f, 90.0f, 90.0f));
  entity3->GetTransformComponent()->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
  entity3->AddMaterialComponent();
  entity3->GetMeshComponent()->LoadOBJ("../../data/models/Pikachu/pikachu.obj", "../../data/models/Pikachu/");
 
  return 0;
}
