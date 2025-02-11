#ifndef __CAMERA_COMPONENT_H__
#define __CAMERA_COMPONENT_H__ 1

#include "engine/component.h"

class CameraComponent : public Component {
public:
  CameraComponent() = default;
  CameraComponent(std::weak_ptr<Entity> entity);
  CameraComponent(const CameraComponent& other);
  CameraComponent(CameraComponent&& other) noexcept;
  ~CameraComponent();
  CameraComponent& operator=(CameraComponent&& other) noexcept;
  void operator=(const CameraComponent& other);

  void SetFOV(float fov);
  void SetAspectRatio(float aspect_ratio);
  void SetNearPlane(float near_plane);
  void SetFarPlane(float far_plane);
  void SetMainCamera();
  void SetCameraPosition(glm::vec3 pos);

  glm::vec3 GetPosition() const;
  glm::vec3 GetDirection() const;

  glm::vec3 GetUp() const;
  glm::vec3 GetRight() const;

  glm::mat4 GetViewMatrix() const;
  glm::mat4 GetProjectionMatrix() const;
  glm::mat4 GetOrthoMatrix() const;

  float GetFOV() const;
  float GetAspectRatio() const;
  float GetNearPlane() const;
  float GetFarPlane() const;

  void MoveCamera();
  void MoveKeyboard();
  void MoveMouse();

private:
  std::unique_ptr<class CameraData> data;
};

#endif // !__CAMERA_COMPONENT_H__
