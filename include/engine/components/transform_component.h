#ifndef __TRANSFORM_COMPONENT__
#define __TRANSFORM_COMPONENT__ 1

#include "engine/component.h"

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

class TransformComponent : public Component
{
public:
  //TODO: review the component transformations.

  TransformComponent() = default;
  TransformComponent(std::weak_ptr<Entity> entity);
  TransformComponent(const TransformComponent& other);
  TransformComponent(TransformComponent&& other);
  ~TransformComponent() = default;
  TransformComponent& operator=(TransformComponent&& other);
  void operator=(const TransformComponent& other);

  //Setters
  void SetPosition(float x, float y, float z);
  void SetPosition(float position[3]);
  void SetPosition(glm::vec3 position);

  void SetRotation(float x, float y, float z);
  void SetRotation(float rotation[3]);
  void SetRotation(glm::vec3 rotation);

  void SetScale(float x, float y, float z);
  void SetScale(float scale[3]);
  void SetScale(glm::vec3 scale);
  void SetParent(class Entity entity);

  //TODO:Make local transformations

  //Getters

  glm::vec3 GetPosition() const;
  glm::vec3 GetRotation() const;
  glm::vec3 GetScale() const;
  glm::mat4 GetTraslationMatrix() const;
  glm::mat4 GetScaleMatrix() const;
  glm::mat4 GetRotationMatrix() const;
  glm::mat4 GetModelMatrix() const;

  void ShowStats() override;

private:

  std::unique_ptr<TransformData> data;
};

#endif //__TRANSFORM_COMPONENT__