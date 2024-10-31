#ifndef __CAMERA_COMPONENT_H__
#define __CAMERA_COMPONENT_H__ 1

#include "engine/component.h"


class CameraComponent : public Component {
public:
  CameraComponent() = default;
  CameraComponent(std::weak_ptr<Entity> entity);
  void operator=(const CameraComponent& other);
  void SetFOV(float fov);
  void SetAspectRatio(float aspect_ratio);
  void SetNearPlane(float near_plane);
  void SetFarPlane(float far_plane);
  void SetMainCamera();
  void MoveCamera();
  void MoveKeyboard();
  void MoveMouse();

  //glm::vec3 GetDirection();
  //glm::vec3 GetUp();
  //glm::vec3 GetRight();
  glm::mat4 GetViewMatrix();
  glm::mat4 GetProjectionMatrix();
  //glm::mat4 GetOrthoMatrix();
  float GetFOV();
  //float GetAspectRatio();
  //float GetNearPlane();
  //float GetFarPlane();
private:
  std::unique_ptr<class CameraData> data;
};







#endif // !__CAMERA_COMPONENT_H__
