#include "engine/entity.h"
#include "engine/components/render_component.h"
#include "engine/components/transform_component.h"
#include "engine/components/mesh_component.h"
#include "engine/components/shader_component.h"
#include "engine/components/camera_component.h"
#include "engine/components/material_component.h"
#include "engine/components/light_component.h"
#include "engine/components/skybox_component.h"

#include "loguru/loguru.hpp"

//#include <vector>

struct EntityData {
    int id;
    //std::vector<std::shared_ptr<Component>> components_;

    std::shared_ptr<MeshComponent> mesh_component;
    std::shared_ptr<ShaderComponent> shader_component;
    std::shared_ptr<TransformComponent> transform_component;
    std::shared_ptr<CameraComponent> camera_component;
    std::shared_ptr<MaterialComponent> material_component;
    std::shared_ptr<RenderComponent> render_component;
    std::shared_ptr<LightComponent> light_component;
    std::shared_ptr<SkyBoxComponent> skybox_component;
    //std::shared_ptr<PhysicsComponent> physics_component;
    //std::shared_ptr<SoundComponent> sound_component;

    EntityData() : id(-1), mesh_component(nullptr), shader_component(nullptr), transform_component(nullptr), camera_component(nullptr), material_component(nullptr), render_component(nullptr), light_component(nullptr), skybox_component(nullptr)  {}
};

//Entity::Entity() {}

Entity::Entity(int id){
  data_ = std::make_unique<EntityData>();
  data_->id = id;
}

Entity::Entity(const Entity& entity) {
  data_ = std::make_unique<EntityData>();
  data_->id = entity.data_->id;
  data_->mesh_component = std::shared_ptr<MeshComponent>(entity.data_->mesh_component);
  data_->shader_component = std::shared_ptr<ShaderComponent>(entity.data_->shader_component);
  data_->transform_component = std::shared_ptr<TransformComponent>(entity.data_->transform_component);
  data_->camera_component = std::shared_ptr<CameraComponent>(entity.data_->camera_component);
  data_->material_component = std::shared_ptr<MaterialComponent>(entity.data_->material_component);
  data_->render_component = std::shared_ptr<RenderComponent>(entity.data_->render_component);
  data_->light_component = std::shared_ptr<LightComponent>(entity.data_->light_component);
  data_->skybox_component = std::shared_ptr<SkyBoxComponent>(entity.data_->skybox_component);
}

Entity::Entity(Entity&& entity) noexcept { data_ = std::move(entity.data_); }

Entity& Entity::operator=(const Entity& entity) {
  if (this == &entity) {
    return *this;
  }

  data_ = std::make_unique<EntityData>();
  data_->id = entity.data_->id;
  data_->mesh_component = std::shared_ptr<MeshComponent>(entity.data_->mesh_component);
  data_->shader_component = std::shared_ptr<ShaderComponent>(entity.data_->shader_component);
  data_->transform_component = std::shared_ptr<TransformComponent>(entity.data_->transform_component);
  data_->camera_component = std::shared_ptr<CameraComponent>(entity.data_->camera_component);
  data_->material_component = std::shared_ptr<MaterialComponent>(entity.data_->material_component);
  data_->render_component = std::shared_ptr<RenderComponent>(entity.data_->render_component);
  data_->light_component = std::shared_ptr<LightComponent>(entity.data_->light_component);
  data_->skybox_component = std::shared_ptr<SkyBoxComponent>(entity.data_->skybox_component);

  return *this;
}

void Entity::operator=(Entity&& entity) noexcept {
  if (this == &entity) {
    return;
  }
  data_ = std::move(entity.data_);
}

Entity::~Entity() {
  data_->mesh_component.reset();
  data_->shader_component.reset();
  data_->transform_component.reset();
  data_->camera_component.reset();
  data_->material_component.reset();
  data_->render_component.reset();
  data_->light_component.reset();
  data_->skybox_component.reset();
  //data_->physics_component.reset();
  //data_->sound_component.reset();
  data_.reset();
}

//Setters

int Entity::ID() { return data_->id; }

std::shared_ptr<MeshComponent> Entity::GetMeshComponent() { return data_->mesh_component; }

std::shared_ptr<ShaderComponent> Entity::GetShaderComponent() { return data_->shader_component; }

std::shared_ptr<TransformComponent> Entity::GetTransformComponent() { return data_->transform_component; }

std::shared_ptr<CameraComponent> Entity::GetCameraComponent() { return data_->camera_component; }

std::shared_ptr<MaterialComponent> Entity::GetMaterialComponent() { return data_->material_component; }

std::shared_ptr<class RenderComponent> Entity::GetRenderComponent() { return data_->render_component; }

std::shared_ptr<class LightComponent> Entity::GetLightComponent() { return data_->light_component; }

std::shared_ptr<class SkyBoxComponent> Entity::GetSkyBoxComponent() { return data_->skybox_component; }

void Entity::AddRenderComponent() {
  if (data_->render_component == nullptr) {
    data_->render_component = std::make_shared<RenderComponent>(weak_from_this());
  }
  else {
    LOG_F(ERROR, "RenderComponent already exists");
  }
}

void Entity::AddTransformComponent() {
  if (data_->transform_component == nullptr) {
    data_->transform_component = std::make_shared<TransformComponent>(weak_from_this());
  }
  else {
    LOG_F(ERROR, "TransformComponent already exists");
  }
}

void Entity::AddLightComponent() {
  if (data_->light_component == nullptr) {
    data_->light_component = std::make_shared<LightComponent>(weak_from_this());
  }
  else {
    LOG_F(ERROR, "LightComponent already exists");
  }
}

void Entity::AddCameraComponent() {
  if (data_->camera_component == nullptr) {
    data_->camera_component = std::make_shared<CameraComponent>(weak_from_this());
  }
  else {
    LOG_F(ERROR, "CameraComponent already exists");
  }
}

void Entity::AddMeshComponent() {
  if (data_->mesh_component == nullptr) {
    data_->mesh_component = std::make_shared<MeshComponent>(weak_from_this());
  }
  else {
    LOG_F(ERROR, "MeshComponent already exists");
  }
}

void Entity::AddShaderComponent() {
  if (data_->shader_component == nullptr) {
    data_->shader_component = std::make_shared<ShaderComponent>(weak_from_this());
  }
  else {
    LOG_F(ERROR, "ShaderComponent already exists");
  }
}

void Entity::AddMaterialComponent(){
  if (data_->material_component == nullptr) {
    data_->material_component = std::make_shared<MaterialComponent>(weak_from_this());
  }
  else {
    LOG_F(ERROR, "MaterialComponent already exists");
  }
}

void Entity::AddSkyBoxComponent(){
  if (data_->skybox_component == nullptr) {
    data_->skybox_component = std::make_shared<SkyBoxComponent>(weak_from_this());
  }
  else {
    LOG_F(ERROR, "SkyBoxComponent already exists");
  }
}

/*
void Entity::AddPhysicsComponent() {
  if (data_->physics_component == nullptr) {
    data_->physics_component = std::make_shared<PhysicsComponent>(weak_from_this());
  }
  else {
    LOG_F(ERROR, "PhysicsComponent already exists");
  }
}

void Entity::AddSoundComponent() {
  if (data_->sound_component == nullptr) {
    data_->sound_component = std::make_shared<SoundComponent>(weak_from_this());
  }
  else {
    LOG_F(ERROR, "SoundComponent already exists");
  }
*/

//Getters
