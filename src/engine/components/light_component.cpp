#include "engine/components/light_component.h"

struct LightData {
  LightComponent::LightType type;
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  glm::vec3 color;
  glm::vec3 position;
};

LightComponent::LightComponent()
{
  data_ = std::make_unique<LightData>();
}

LightComponent::LightComponent(std::weak_ptr<Entity> entity)
{
  this->entity = entity;
  this->id = entity.lock()->ID();
  this->type = ComponentType_Light;
  data_ = std::make_unique<LightData>();
}

LightComponent::~LightComponent()
{
}

void LightComponent::SetLightType(LightType type) {
  data_->type = type;
}

void LightComponent::SetAmbient(glm::vec3 ambient){
  data_->ambient = ambient;

}

void LightComponent::SetDiffuse(glm::vec3 diffuse) {
  data_->diffuse = diffuse;
}

void LightComponent::SetSpecular(glm::vec3 specular){
  data_->specular = specular;
}

void LightComponent::SetLightColor(glm::vec3 color){
  data_->color = color;
}

LightComponent::LightType LightComponent::GetLightType() const
{
  return data_->type;
}

glm::vec3 LightComponent::GetLightColor() const
{
  return data_->color;
}
