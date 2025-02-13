/*****************************************************************//**
 * \file   shader_component.cpp
 * \brief  
 * 
 * \author pablo
 * \date   January 2025
 *********************************************************************/
#include "engine/components/shader_component.h"
#include "engine/entity.h"

struct ShaderComponentdata {
  std::shared_ptr<Shader> shader;
  ShaderComponentdata() { shader = std::make_shared<Shader>(); }
  ShaderComponentdata(const ShaderComponentdata& other) {
    shader = std::make_shared<Shader>(*other.shader);
  }
  ShaderComponentdata(ShaderComponentdata&& other) noexcept {
    shader = std::move(other.shader);
  }
  ~ShaderComponentdata() {}

  void operator=(const ShaderComponentdata& other) {
    shader = std::make_shared<Shader>(*other.shader);
  }

  ShaderComponentdata& operator=(ShaderComponentdata&& other) noexcept {
    if (this != &other) {
      shader = std::move(other.shader);
    }
    return *this;
  }
};

ShaderComponent::ShaderComponent() {
  data_ = std::make_unique<ShaderComponentdata>();
}

ShaderComponent::ShaderComponent(std::weak_ptr<Entity> e) {
  entity = e;
  this->id = entity.lock()->ID();
  this->type = ComponentType_Shader;
  data_ = std::make_unique<ShaderComponentdata>();
}

ShaderComponent::ShaderComponent(const ShaderComponent& other) {
  entity = other.entity;
  this->id = other.id;
  this->type = other.type;
  data_ = std::make_unique<ShaderComponentdata>(*other.data_);
}

ShaderComponent::ShaderComponent(ShaderComponent&& other) noexcept {
  entity = other.entity;
  this->id = other.id;
  this->type = other.type;
  data_ = std::move(other.data_);
}

ShaderComponent::~ShaderComponent() {}

void ShaderComponent::operator=(const ShaderComponent& other) {
  entity = other.entity;
  this->id = other.id;
  this->type = other.type;
  data_ = std::make_unique<ShaderComponentdata>(*other.data_);
}

ShaderComponent& ShaderComponent::operator=(ShaderComponent&& other) noexcept {
  if (this != &other) {
    entity = other.entity;
    this->id = other.id;
    this->type = other.type;
    data_ = std::move(other.data_);
  }
  return *this;
}

bool ShaderComponent::LoadShader(std::string vert, std::string frag) {
  return data_->shader->LoadShader(vert, frag);
}

int ShaderComponent::GetProgram() {
  return data_->shader->GetProgram();
}

std::shared_ptr<Shader> ShaderComponent::GetShader(){
  return data_->shader;
}

void ShaderComponent::SetBool(const std::string& name, bool value) const {
  data_->shader->SetBool(name, value);
}

void ShaderComponent::SetInt(const std::string& name, int value) const {
  data_->shader->SetInt(name, value);
}

void ShaderComponent::SetFloat(const std::string& name, float value) const {
  data_->shader->SetFloat(name, value);
}

void ShaderComponent::SetVec2(const std::string& name, glm::vec2 value) const {
  data_->shader->SetVec2(name, value);
}

void ShaderComponent::SetVec3(const std::string& name, glm::vec3 value) const {
  data_->shader->SetVec3(name, value);
}

void ShaderComponent::SetMat4(const std::string& name, glm::mat4 value) const {
  data_->shader->SetMat4(name, value);
}

void ShaderComponent::SetTexture(const std::string& name, int value) const {
  data_->shader->SetTexture(name, value);
}

void ShaderComponent::UseShader() {
  data_->shader->UseShader();
}

void ShaderComponent::ShowStats(){
}


