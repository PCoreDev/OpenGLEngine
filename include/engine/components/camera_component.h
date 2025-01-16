#ifndef __CAMERA_COMPONENT_H__
#define __CAMERA_COMPONENT_H__ 1

#include "engine/component.h"

struct CameraData {
  std::shared_ptr<class TransformComponent> transform;
  //camera attributes
  glm::vec3 camera_position;
  glm::vec3 camera_direction;
  glm::vec3 camera_front;
  glm::vec3 camera_up;
  glm::vec3 camera_right;
  glm::mat4 camera_view_matrix;
  glm::vec3 up;
  glm::mat4 projection_matrix;
  glm::mat4 ortho_matrix;

  //euler Angles
  float camera_pitch;
  float camera_yaw;
  float camera_roll;

  //camera options
  float fov;
  float aspect_ratio;
  float near_plane;
  float far_plane;
  float camera_sensitivity;
  float camera_speed;

  //Mouse variables
  double last_x, last_y;
  bool first_mouse;

  void UpdateVectors();
};



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

  glm::vec3 GetPosition();
  //glm::mat4 GetOrthoMatrix();
  float GetFOV();
  //float GetAspectRatio();
  //float GetNearPlane();
  //float GetFarPlane();
private:
  std::unique_ptr<CameraData> data;
};

#endif // !__CAMERA_COMPONENT_H__
