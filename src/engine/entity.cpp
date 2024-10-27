#include "engine/entity.h"
#include "engine/component.h"

#include <vector>

struct EntityData {
    int id_;
    std::vector<std::shared_ptr<Component>> components_;
    EntityData() : id_(0) {}
};

Entity::Entity() {
}

Entity::Entity(int id)
{
  data_ = std::make_unique<EntityData>();
  data_->id_ = id;
}

Entity::Entity(const Entity& entity)
{
  data_ = std::make_unique<EntityData>();
  data_->id_ = entity.data_->id_;
  for (auto& component : entity.data_->components_) {
    data_->components_.push_back(component);
  }
}

Entity::Entity(Entity&& entity)
{
  data_ = std::move(entity.data_);
}

Entity& Entity::operator=(const Entity& entity)
{
  data_ = std::make_unique<EntityData>();
  data_->id_ = entity.data_->id_;
  for (auto& component : entity.data_->components_) {
    data_->components_.push_back(component);
  }
  return *this;
}

Entity::~Entity() {
}

//Setters

int Entity::ID() {
    return data_->id_;
}

std::shared_ptr<MeshComponent> Entity::GetMeshComponent() {
  for (auto& component : data_->components_) {
    if (component->GetType() == ComponentType::ComponentType_Mesh) {
      return std::static_pointer_cast<MeshComponent>(component);
    }
  }
  return nullptr;
}

std::shared_ptr<ShaderComponent> Entity::GetShaderComponent() {
  for (auto& component : data_->components_) {
    if (component->GetType() == ComponentType::ComponentType_Shader) {
      return std::static_pointer_cast<ShaderComponent>(component);
    }
  }
  return nullptr;
}

std::shared_ptr<class TransformComponent> Entity::GetTransformComponent()
{
  for (auto& component : data_->components_) {
    if (component->GetType() == ComponentType::ComponentType_Transform) {
      return std::static_pointer_cast<TransformComponent>(component);
    }
  }
  return std::shared_ptr<class TransformComponent>();
}

std::shared_ptr<class CameraComponent> Entity::GetCameraComponent()
{
  for (auto& component : data_->components_) {
    if (component->GetType() == ComponentType::ComponentType_Camera) {
      return std::static_pointer_cast<CameraComponent>(component);
    }
  }
  return nullptr;
}

std::shared_ptr<class MaterialComponent> Entity::GetMaterialComponent(){
  for (auto& component : data_->components_) {
    if (component->GetType() == ComponentType::ComponentType_Material) {
      return std::static_pointer_cast<MaterialComponent>(component);
    }
  }
  return nullptr;
}

std::shared_ptr<class RenderComponent> Entity::GetRenderComponent()
{
  for (auto& component : data_->components_) {
    if (component->GetType() == ComponentType::ComponentType_Render) {
      return std::static_pointer_cast<RenderComponent>(component);
    }
  }
  return nullptr;
}

void Entity::AddRenderComponent() {
    data_->components_.push_back(std::make_shared<RenderComponent>(weak_from_this()));
}

void Entity::AddTransformComponent() {
    data_->components_.push_back(std::make_shared<TransformComponent>(weak_from_this()));
}
/*
void Entity::AddPhysicsComponent() {
    data_->components_.push_back(std::make_shared<PhysicsComponent>());
}

void Entity::AddNodeComponent() {
    data_->components_.push_back(std::make_shared<NodeComponent>());
}

void Entity::AddSoundComponent() {
    data_->components_.push_back(std::make_shared<SoundComponent>());
}

void Entity::AddLightComponent() {
    data_->components_.push_back(std::make_shared<LightComponent>());
}

void Entity::AddCameraComponent() {
    data_->components_.push_back(std::make_shared<CameraComponent>());
}
*/

void Entity::AddCameraComponent()
{
  data_->components_.push_back(std::make_shared<CameraComponent>(weak_from_this()));
}

void Entity::AddMeshComponent() {
    data_->components_.push_back(std::make_shared<MeshComponent>(weak_from_this()));
}

void Entity::AddShaderComponent() {
    data_->components_.push_back(std::make_shared<ShaderComponent>(weak_from_this()));
}

void Entity::AddMaterialComponent(){
  data_->components_.push_back(std::make_shared<MaterialComponent>(weak_from_this()));
}

//Getters
