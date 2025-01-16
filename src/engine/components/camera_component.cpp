#include "engine/components/camera_component.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "engine/core.h"

#include "engine/entity.h"

//struct CameraData {
//  std::shared_ptr<class TransformComponent> transform;
//  //camera attributes
//  glm::vec3 camera_position;
//  glm::vec3 camera_direction;
//  glm::vec3 camera_front;
//  glm::vec3 camera_up;
//  glm::vec3 camera_right;
//  glm::mat4 camera_view_matrix;
//  glm::vec3 up;
//  glm::mat4 projection_matrix;
//  glm::mat4 ortho_matrix;
//
//  //euler Angles
//  float camera_pitch;
//  float camera_yaw;
//  float camera_roll;
//
//  //camera options
//  float fov;
//  float aspect_ratio;
//  float near_plane;
//  float far_plane;
//  float camera_sensitivity;
//  float camera_speed;
//
//  //Mouse variables
//  double last_x, last_y;
//  bool first_mouse;
//
//  void UpdateVectors();
//};

void CameraData::UpdateVectors() {
  up = glm::vec3(0.0f, 1.0f, 0.0f);

  camera_direction.x = cos(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));
  camera_direction.y = sin(glm::radians(camera_pitch));
  camera_direction.z = sin(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));

  camera_front = glm::normalize(camera_direction);
  camera_right = glm::normalize(glm::cross(camera_front, up));
  camera_up = glm::normalize(glm::cross(camera_right, camera_front));
}

CameraComponent::CameraComponent(std::weak_ptr<Entity> e) {
  this->entity = e;
  this->id = entity.lock()->ID();
  this->type = ComponentType_Camera;
  data = std::make_unique<CameraData>();

  data->camera_position = glm::vec3(100.0f, 0.0f, 0.0f);
  data->camera_direction = glm::vec3(0.0f, 0.0f, -1.0f);

  data->camera_up = glm::vec3(0.0f, 1.0f, 0.0f);

  data->fov = 90.0f;
  data->aspect_ratio = 1280.0f / 720.0f;
  data->near_plane = 0.1f;
  data->far_plane = 1000.0f;

  data->camera_yaw = -90.0f;
  data->first_mouse = true;
  data->camera_speed = 1.0f;
  data->camera_sensitivity = 0.1f;
  data->projection_matrix = glm::perspective(glm::radians(data->fov), data->aspect_ratio, data->near_plane, data->far_plane);
}

void CameraComponent::operator=(const CameraComponent& other) {
  this->id = other.id;
  this->type = other.type;
  data = std::make_unique<CameraData>(*other.data);
}

//void CameraComponent::SetTarget(glm::vec3 target) {
//  data->camera_target = target;
//}

void CameraComponent::SetFOV(float fov) {
  data->fov = fov;
  data->projection_matrix = glm::perspective(glm::radians(data->fov), data->aspect_ratio, data->near_plane, data->far_plane);
}

void CameraComponent::SetAspectRatio(float aspect_ratio) {
  data->aspect_ratio = aspect_ratio;
  data->projection_matrix = glm::perspective(glm::radians(data->fov), data->aspect_ratio, data->near_plane, data->far_plane);
}

void CameraComponent::SetNearPlane(float near_plane) {
  data->near_plane = near_plane;
  data->projection_matrix = glm::perspective(glm::radians(data->fov), data->aspect_ratio, data->near_plane, data->far_plane);
}

void CameraComponent::SetFarPlane(float far_plane) {
  data->far_plane = far_plane;
  data->projection_matrix = glm::perspective(glm::radians(data->fov), data->aspect_ratio, data->near_plane, data->far_plane);
}

void CameraComponent::SetMainCamera() {
  for (auto& entity : OpenGLEngine::Engine::Core::entity_manager_->GetEntities()) {
    if (entity.lock()->ID() == id) {
      if (entity.lock()->GetCameraComponent() != nullptr) {
        OpenGLEngine::Engine::Core::camera_ = entity.lock()->GetCameraComponent();
      }
    }
  }
}

void CameraComponent::MoveCamera() {
  MoveMouse();
  MoveKeyboard();
  data->camera_view_matrix = glm::lookAt(data->camera_position, data->camera_position + data->camera_front, data->camera_up);
}

void CameraComponent::MoveKeyboard()
{
  float camera_speed = data->camera_speed;
  //std::shared_ptr<TransformComponent> transform = entity.lock()->GetTransformComponent();

  //if (transform != nullptr) {
    //glm::vec3 position = transform->GetPosition();
  if (EngineInput::IsKeyPressed(EngineInput::KeyNames::kKeyNames_KeyW))
    data->camera_position += (camera_speed * data->camera_front);
  if (EngineInput::IsKeyPressed(EngineInput::KeyNames::kKeyNames_KeyS))
    data->camera_position -= (camera_speed * data->camera_front);
  if (EngineInput::IsKeyPressed(EngineInput::KeyNames::kKeyNames_KeyA))
    data->camera_position -= (glm::normalize(glm::cross(data->camera_front, data->camera_up)) * camera_speed);
  if (EngineInput::IsKeyPressed(EngineInput::KeyNames::kKeyNames_KeyD))
    data->camera_position += (glm::normalize(glm::cross(data->camera_front, data->camera_up)) * camera_speed);


  //if (position != transform->GetPosition()) {
  //  transform->SetPosition(position);
  //}
//  }
}

void CameraComponent::MoveMouse() {
  double xpos, ypos;
  EngineInput::GetMousePosition(xpos, ypos);

  if (data->first_mouse) {
    data->last_x = xpos;
    data->last_y = ypos;
    data->first_mouse = false;
  }

  float xoffset = static_cast<float>(xpos - data->last_x);
  float yoffset = static_cast<float>(data->last_y - ypos);
  data->last_x = xpos;
  data->last_y = ypos;


  xoffset *= data->camera_sensitivity;
  yoffset *= data->camera_sensitivity;

  data->camera_yaw += xoffset;
  data->camera_pitch += yoffset; //If you want to invert the mouse Y axis, you must do data->camera_pitch -= yoffset. or multiply by -1

  if (data->camera_pitch > 89.0f) {
    data->camera_pitch = 89.0f;
  }
  if (data->camera_pitch < -89.0f) {
    data->camera_pitch = -89.0f;
  }

  data->UpdateVectors();
}

//glm::vec3 CameraComponent::GetDirection() { return data->camera_direction; }
//
//glm::vec3 CameraComponent::GetUp() { return data->camera_up; }
//
float CameraComponent::GetFOV() { return data->fov; }
//
//float CameraComponent::GetAspectRatio() { return data->aspect_ratio; }
//
//float CameraComponent::GetNearPlane() { return data->near_plane; }
//
//float CameraComponent::GetFarPlane() { return data->far_plane; }
//
//glm::vec3 CameraComponent::GetRight() { return data->camera_right; }
//
glm::mat4 CameraComponent::GetViewMatrix() { return data->camera_view_matrix; }

glm::mat4 CameraComponent::GetProjectionMatrix() { return data->projection_matrix; }
glm::vec3 CameraComponent::GetPosition()
{
    return data->camera_position;
}
//
//glm::mat4 CameraComponent::GetOrthoMatrix() { return data->ortho_matrix; }
