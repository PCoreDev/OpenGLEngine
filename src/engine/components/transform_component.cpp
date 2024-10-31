#include "engine/components/transform_component.h"

#include "engine/core.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "engine/entity.h"

struct TransformData {
  int parent_id;
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;

  glm::mat4 m_traslation;
  glm::mat4 m_rotation;
  glm::mat4 m_scale;
  glm::mat4 m_model;

  void UpdateTraslationMatrix();
  void UpdateScaleMatrix();
  void UpdateRotationMatrix();
  void UpdateModelMatrix();
};

TransformComponent::TransformComponent(std::weak_ptr<Entity> e) {
  this->entity = e;
  this->id = entity.lock()->ID();
  this->type = ComponentType_Transform;
  data = std::make_unique<TransformData>();
  data->position = glm::vec3(0.0f, 0.0f, 0.0f);
  data->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
  data->scale = glm::vec3(1.0f, 1.0f, 1.0f);
  data->UpdateTraslationMatrix();
  data->UpdateRotationMatrix();
  data->UpdateScaleMatrix();
  data->parent_id = this->id;
}

TransformComponent::TransformComponent(const TransformComponent& other) {
  this->id = other.id;
  this->type = other.type;
  data = std::make_unique<TransformData>(*other.data);
}

TransformComponent::TransformComponent(TransformComponent&& other) {
  this->id = other.id;
  this->type = other.type;
  data = std::move(other.data);
}

TransformComponent& TransformComponent::operator=(TransformComponent&& other) {
  this->id = other.id;
  this->type = other.type;
  data = std::move(other.data);
  return *this;
}

void TransformComponent::operator=(const TransformComponent& other) {
  this->id = other.id;
  this->type = other.type;
  data = std::make_unique<TransformData>(*other.data);
}

//Position
void TransformComponent::SetPosition(float x, float y, float z) {
  glm::vec3 new_position = glm::vec3(x, y, z);
  if (data->position != new_position) {
    data->position = new_position;
    data->UpdateTraslationMatrix();
  }
}

void TransformComponent::SetPosition(float position[3]) {
  SetPosition(position[0], position[1], position[2]);
}

void TransformComponent::SetPosition(glm::vec3 position) {
  SetPosition(position.x, position.y, position.z);;
}

//Rotation
void TransformComponent::SetRotation(float x, float y, float z) {
  glm::vec3 new_rotation = glm::vec3(x, y, z);
  if (data->rotation != new_rotation) {
    data->rotation = new_rotation;
    data->UpdateRotationMatrix();
  }
}

void TransformComponent::SetRotation(float rotation[3]) {
  SetRotation(rotation[0], rotation[1], rotation[2]);
}

void TransformComponent::SetRotation(glm::vec3 rotation) {
  SetRotation(rotation.x, rotation.y, rotation.z);
}

//Scale
void TransformComponent::SetScale(float x, float y, float z) {
  glm::vec3 new_scale = glm::vec3(x, y, z);
  if (data->scale != new_scale) {
    data->scale = new_scale;
    data->UpdateScaleMatrix();
  }
}

void TransformComponent::SetScale(float scale[3]) {
  SetScale(scale[0], scale[1], scale[2]);
}

void TransformComponent::SetScale(glm::vec3 scale) {
  SetScale(scale.x, scale.y, scale.z);
}

void TransformComponent::SetParent(Entity entity) {
  data->parent_id = entity.ID();
}

//Getters
glm::vec3 TransformComponent::GetPosition() const { return data->position; }

glm::vec3 TransformComponent::GetRotation() const { return data->rotation; }

glm::vec3 TransformComponent::GetScale() const { return data->scale; }

glm::mat4 TransformComponent::GetTraslationMatrix() const {
  if (data->parent_id != id) {
    for (auto entity : OpenGLEngine::Engine::Core::entity_manager_->GetEntities()) {
      if (entity.lock()->ID() == data->parent_id) {
        return data->m_traslation * entity.lock()->GetTransformComponent()->GetModelMatrix();
      }
    }
  }
  return data->m_traslation;
}

glm::mat4 TransformComponent::GetScaleMatrix() const {
  if (data->parent_id != id) {
    for (auto entity : OpenGLEngine::Engine::Core::entity_manager_->GetEntities()) {
      if (entity.lock()->ID() == data->parent_id) {
        return data->m_scale * entity.lock()->GetTransformComponent()->GetScaleMatrix();
      }
    }
  }
  return data->m_scale;
}

glm::mat4 TransformComponent::GetRotationMatrix() const {
  if (data->parent_id != id) {
    for (auto entity : OpenGLEngine::Engine::Core::entity_manager_->GetEntities()) {
      if (entity.lock()->ID() == data->parent_id) {
        return data->m_rotation * entity.lock()->GetTransformComponent()->GetRotationMatrix();
      }
    }
  }
  return data->m_rotation;
}

glm::mat4 TransformComponent::GetModelMatrix() const {
  return data->m_model;
}

void TransformData::UpdateTraslationMatrix() {
  m_traslation = glm::mat4(1.0f);
  m_traslation = glm::translate(m_traslation, position);
  UpdateModelMatrix();
}

void TransformData::UpdateScaleMatrix() {
  m_scale = glm::mat4(1.0f);
  m_scale = glm::scale(m_scale, scale);
  UpdateModelMatrix();
}

void TransformData::UpdateRotationMatrix() {
  m_rotation = glm::mat4(1.0f);
  m_rotation = glm::rotate(m_rotation, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
  m_rotation = glm::rotate(m_rotation, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
  m_rotation = glm::rotate(m_rotation, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
  UpdateModelMatrix();
}

void TransformData::UpdateModelMatrix() {
  m_model = glm::mat4(1.0f);
  m_model = m_traslation * m_rotation * m_scale;
}