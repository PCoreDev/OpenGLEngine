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
#include "engine/components/skybox_component.h"



int OpenGLEngine::main(int argc, char** argv)
{
  //std::shared_ptr<Entity> camera = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
  ////camera->AddTransformComponent();
  //camera->AddCameraComponent();
  //camera->GetCameraComponent()->SetMainCamera();

  std::shared_ptr<Entity> skybox = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
  skybox->AddMeshComponent();
  skybox->GetMeshComponent()->SkyBox();
  skybox->AddRenderComponent();
  skybox->AddSkyBoxComponent();
  skybox->AddShaderComponent();
  skybox->GetShaderComponent()->LoadShader("../../src/engine/shaders/skybox.vert", "../../src/engine/shaders/skybox.frag");
  std::vector<std::string> faces {
    "../../data/textures/skybox/skybox_right.jpg",
    "../../data/textures/skybox/skybox_left.jpg",
    "../../data/textures/skybox/skybox_top.jpg",
    "../../data/textures/skybox/skybox_bottom.jpg",
    "../../data/textures/skybox/skybox_back.jpg",
    "../../data/textures/skybox/skybox_front.jpg",
  };
  skybox->GetSkyBoxComponent()->LoadSkyBox(faces);


  
  std::shared_ptr<Entity> entity1 = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
  entity1->AddMeshComponent();
  entity1->AddRenderComponent();
  entity1->AddTransformComponent();
  entity1->GetTransformComponent()->SetPosition(glm::vec3(0.0f, -130.0f, 0.0f));
  entity1->GetTransformComponent()->SetRotation(glm::vec3(-90.0f, 0.0f, 0.0f));
  entity1->GetTransformComponent()->SetScale(glm::vec3(100.0f, 100.0f, 100.0f));
  entity1->GetMeshComponent()->Square();
  entity1->AddMaterialComponent();
  entity1->GetMaterialComponent()->AddNewMaterial("Square",
    "../../data/textures/metal.png","",
    "../../data/textures/metal.png",
    "", "", "",
    glm::vec3(0.5f),
    glm::vec3(0.2f),
    glm::vec3(1.0f),
    0.0f, 0.0f, 0.0f, 0);


  std::shared_ptr<Entity> light = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
  light->AddMeshComponent();
  light->AddRenderComponent();
  light->AddTransformComponent();
  light->GetTransformComponent()->SetPosition(glm::vec3(0.0f, 100.0f, 0.0f));
  light->GetTransformComponent()->SetScale(glm::vec3(10.0f, 10.0f, 10.0f));
  light->AddMaterialComponent();
  light->GetMeshComponent()->LoadOBJ("../../data/models/sphere.obj", "../../data/models/");
  light->GetMaterialComponent()->AddNewMaterial("Light",
    "../../data/textures/white.png","",
    "../../data/textures/metal.png",
    "", "", "",
    glm::vec3(0.5f),
    glm::vec3(0.2f),
    glm::vec3(1.0f),
    0.0f, 0.0f, 0.0f, 0);
  light->AddLightComponent();
  light->GetLightComponent()->SetLightType(LightComponent::LightType::Directional);
  light->GetLightComponent()->SetDirection(glm::vec3(-1.0f, -1.0f, 0.0f));
  light->GetLightComponent()->SetAmbient(glm::vec3(0.2f));
  light->GetLightComponent()->SetDiffuse(glm::vec3(0.5f));
  light->GetLightComponent()->SetSpecular(glm::vec3(1.0f));
  light->GetLightComponent()->SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));

 
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
        entity->GetMaterialComponent()->AddNewMaterial("Wooden",
          "../../data/textures/container.png", "",
          "../../data/textures/container_specular.png",
          "", "", "",
          glm::vec3(0.5f),
          glm::vec3(0.2f),
          glm::vec3(1.0f),
          0.0f, 0.0f, 0.0f, 0);
        if (i == 0 && j == 0 && z == 0) {
          entity->AddLightComponent();
          entity->GetLightComponent()->SetLightType(LightComponent::LightType::Spot);
          entity->GetLightComponent()->SetDirection(glm::vec3(0.0f, -1.0f, 0.0f));
          entity->GetLightComponent()->SetAmbient(glm::vec3(1.0f));
          entity->GetLightComponent()->SetDiffuse(glm::vec3(1.0f));
          entity->GetLightComponent()->SetSpecular(glm::vec3(1.0f));
          entity->GetLightComponent()->SetConstant(1.0f);
          entity->GetLightComponent()->SetLinear(1.0f);
          entity->GetLightComponent()->SetQuadratic(1.0f);
          entity->GetLightComponent()->SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
        }

        if (i == 1 && j == 1 && z == 1) {
          entity->AddLightComponent();
          entity->GetLightComponent()->SetLightType(LightComponent::LightType::Point);
          entity->GetLightComponent()->SetAmbient(glm::vec3(0.2f));
          entity->GetLightComponent()->SetDiffuse(glm::vec3(0.5f));
          entity->GetLightComponent()->SetSpecular(glm::vec3(1.0f));
          entity->GetLightComponent()->SetConstant(1.0f);
          entity->GetLightComponent()->SetLinear(0.09f);
          entity->GetLightComponent()->SetQuadratic(0.032f);
          entity->GetLightComponent()->SetLightColor(glm::vec3(1.0f, 0.0f, 0.0f));
        }
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
  entity3->GetTransformComponent()->SetScale(glm::vec3(11.0f, 11.0f, 11.0f));
  entity3->AddMaterialComponent();
  entity3->GetMeshComponent()->LoadOBJ("../../data/models/Echidna/Echidna.obj", "../../data/models/Echidna/");

  std::shared_ptr<Entity> entity4 = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
  entity4->AddMeshComponent();
  entity4->AddRenderComponent();
  entity4->AddTransformComponent();
  entity4->GetTransformComponent()->SetPosition(glm::vec3(50.0f, -30.0f, 0.0f));
  //entity4->GetTransformComponent()->SetRotation(glm::vec3(-90.0f, 90.0f, 90.0f));
  entity4->GetTransformComponent()->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
  entity4->AddMaterialComponent();
  entity4->GetMeshComponent()->LoadOBJ("../../data/models/Pikachu/pikachu.obj", "../../data/models/Pikachu/");


  //std::shared_ptr<Entity> entity5 = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
  //entity5->AddMeshComponent();
  //entity5->AddRenderComponent();
  //entity5->AddTransformComponent();
  //entity5->GetTransformComponent()->SetPosition(glm::vec3(500.0f, -30.0f, -50.0f));
  ////entity5->GetTransformComponent()->SetRotation(glm::vec3(-90.0f, 90.0f, 90.0f));
  //entity5->GetTransformComponent()->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
  //entity5->AddMaterialComponent();
  ////entity5->GetMeshComponent()->LoadOBJ("../../data/models/Yamato/Space_Battleship_Yamato_[Clean]_v003.obj", "../../data/Yamato/");
  //entity5->GetMeshComponent()->LoadOBJ("../../data/models/Bayonetta/Bayonetta.obj", "../../data/models/Bayonetta/");

  //std::shared_ptr<Entity> entity7 = OpenGLEngine::Engine::Core::entity_manager_->CreateEntity();
  //entity7->AddMeshComponent();
  //entity7->AddRenderComponent();
  //entity7->AddTransformComponent();
  //entity7->GetTransformComponent()->SetPosition(glm::vec3(500.0f, -30.0f, 50.0f));
  ////entity7->GetTransformComponent()->SetRotation(glm::vec3(-90.0f, 90.0f, 90.0f));
  //entity7->GetTransformComponent()->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
  //entity7->AddMaterialComponent();
  ////entity7->GetMeshComponent()->LoadOBJ("../../data/models/Yamato/Space_Battleship_Yamato_[Clean]_v003.obj", "../../data/Yamato/");
  //entity7->GetMeshComponent()->LoadOBJ("../../data/models/Yamato/Space_Battleship_Yamato_[Clean]_v003.obj", "../../data/models/Yamato/");


  return 0;
}
