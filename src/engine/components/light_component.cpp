/*****************************************************************//**
 * \file   light_component.cpp
 * \brief  
 * 
 * \author pablo
 * \date   January 2025
 *********************************************************************/
#include "engine/components/light_component.h"

/**
 * For the Directional we use direction, ambient, diffuse, specular, color.
 * For the Point we use position, ambient, diffuse, specular, constant, linear, quadratic, color.
 * For the Spot we use position, direction, cut_off, color.
 */
struct LightData {
  LightComponent::LightType type;
  glm::vec3 direction;
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  float constant;
  float linear;
  float quadratic;
  float cut_off;
  glm::vec3 color;
};

LightComponent::LightComponent()
{
  data_ = std::make_unique<LightData>();
}

LightComponent::LightComponent(std::weak_ptr<Entity> entity) {
  this->entity = entity;
  this->id = entity.lock()->ID();
  this->type = ComponentType_Light;
  data_ = std::make_unique<LightData>();
}

LightComponent::LightComponent(const LightComponent& other) {
  this->entity = other.entity;
  this->id = other.id;
  this->type = other.type;
  data_ = std::make_unique<LightData>(*other.data_);
}

LightComponent::LightComponent(LightComponent&& other) noexcept {
  this->entity = std::move(other.entity);
  this->id = other.id;
  this->type = other.type;
  data_ = std::move(other.data_);
}

void LightComponent::operator=(LightComponent&& other) noexcept {
  if (this != &other) {
    this->entity = std::move(other.entity);
    this->id = other.id;
    this->type = other.type;
    data_ = std::move(other.data_);
  }
}

void LightComponent::operator=(const LightComponent& other) {
  this->entity = other.entity;
  this->id = other.id;
  this->type = other.type;
  data_ = std::make_unique<LightData>(*other.data_);
}

LightComponent::~LightComponent() {}

void LightComponent::SetLightType(LightType type) {
  data_->type = type;
}

void LightComponent::SetDirection(glm::vec3 direction) {
  data_->direction = direction;
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

void LightComponent::SetConstant(float constant) {
  data_->constant = constant;
}

void LightComponent::SetLinear(float linear) {
  data_->linear = linear;
}

void LightComponent::SetQuadratic(float quadratic) {
  data_->quadratic = quadratic;
}

void LightComponent::SetCutOff(float angle) {
  data_->cut_off = angle;
}

void LightComponent::SetLightColor(glm::vec3 color){
  data_->color = color;
}

LightComponent::LightType LightComponent::GetLightType() const
{
  return data_->type;
}

glm::vec3 LightComponent::GetDirection() const
{
  return data_->direction;
}

glm::vec3 LightComponent::GetAmbient() const
{
  return data_->ambient;
}

glm::vec3 LightComponent::GetDiffuse() const
{
  return data_->diffuse;
}

glm::vec3 LightComponent::GetSpecular() const {
  return data_->specular;
}

float LightComponent::GetConstant() const
{
  return data_->constant;
}

float LightComponent::GetLinear() const
{
  return data_->linear;
}

float LightComponent::GetQuadratic() const
{
  return data_->quadratic;
}


float LightComponent::GetCutOff() const
{
  return data_->cut_off;
}

glm::vec3 LightComponent::GetLightColor() const
{
  return data_->color;
}
