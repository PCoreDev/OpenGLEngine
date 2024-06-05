//Author: Pablo "Pau" Core Palmero
//Date: 5-June-2024
//Email: p.core.dev@outlook.com
//This file contains the component class's implementation of the engine to add differents properties to the objects.

#include "engine/component.h"

namespace OpenGLEngine {

  enum ComponentType {
    ComponentType_Invalid = 0,
    ComponentType_Render,
    ComponentType_Transform,
    ComponentType_Physics,
    ComponentType_Node,
    ComponentType_Sound,
    ComponentType_Light,
    ComponentType_Camera,
    ComponentType_MAX,
  };


  struct TransformData{
  public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
  private:

    glm::mat4 m_translation;
    glm::mat4 m_rotation;
    glm::mat4 m_scale;
    glm::mat4 m_model;
  };


  TransformComponent::TransformComponent(int id)
  {

    this->id = id;
    this->type = ComponentType_Transform;
    data = std::make_unique<TransformData>();
  }

  void TransformComponent::operator=(const TransformComponent& other)
  {
    this->id = other.id;
    this->type = other.type;
    data = std::make_unique<TransformData>(*other.data);
  }

} // namespace OpenGLEngine