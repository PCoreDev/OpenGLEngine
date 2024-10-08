//Author: Pablo "Pau" Core Palmero
//Date: 5-June-2024
//Email: p.core.dev@outlook.com
//This file contains the component class's implementation of the engine to add differents properties to the objects.

#include "engine/component.h"
#include "loguru/loguru.hpp"

#include <memory>
#include <vector>


#pragma region TransformComponent

  TransformComponent::TransformComponent(int id) {
    this->id = id;
    this->type = ComponentType_Transform;
    data = std::make_unique<TransformData>();
  }

  void TransformComponent::operator=(const TransformComponent& other) {
    this->id = other.id;
    this->type = other.type;
    data = std::make_unique<TransformData>(*other.data);
  }

  //Position
  void TransformComponent::SetPosition(float x, float y, float z) {
    data->position = glm::vec3(x, y, z);
  }

  void TransformComponent::SetPosition(float position[3]) {
    data->position = glm::vec3(position[0], position[1], position[2]);
  }

  void TransformComponent::SetPosition(glm::vec3 position) {
    data->position = position;
  }

  //Rotation
  void TransformComponent::SetRotation(float x, float y, float z) {
    data->rotation = glm::vec3(x, y, z);
  
  }

  void TransformComponent::SetRotation(float rotation[3]) {
    data->rotation = glm::vec3(rotation[0], rotation[1], rotation[2]);
  }

  void TransformComponent::SetRotation(glm::vec3 rotation) {
    data->rotation = rotation;
  
  }

  //Scale
  void TransformComponent::SetScale(float x, float y, float z) {
    data->scale = glm::vec3(x, y, z);
  
  }

  void TransformComponent::SetScale(float scale[3]) {
    data->scale = glm::vec3(scale[0], scale[1], scale[2]);
  
  }

  void TransformComponent::SetScale(glm::vec3 scale) {
    data->scale = scale;
  
  
  }

#pragma endregion TransformComponent

#pragma region RenderComponent
  RenderComponent::RenderComponent(int id) {
    this->id = id;
    this->type = ComponentType_Render;
  }

  void RenderComponent::operator=(const RenderComponent& other) {
    this->id = other.id;
    this->type = other.type;
  }
#pragma endregion RenderComponent
  
#pragma region MeshComponent

  MeshComponent::MeshComponent(int id) {
    this->id = id;
    this->type = ComponentType_Mesh;
    data = std::make_unique<MeshData>();
  }

  void MeshComponent::operator=(const MeshComponent& other) {
    this->id = other.id;
    this->type = other.type;
    data = std::make_unique<MeshData>(*other.data);
  }

  void MeshComponent::Triangle() {
    if (data != nullptr) {
      if (data->vertex_data.size() != 0) { data->vertex_data.clear(); }

      data->vertex_data = {
        -0.5f, -0.5f, 0.0f, // bottom left
        0.5f, -0.5f, 0.0f, // bottom right
        0.0f, 0.5f, 0.0f // top
      };
    }
    data->n_vertex = 3;
  }

void MeshComponent::Square() {
    if(data != nullptr) {
        if(data->vertex_data.size() != 0) { data->vertex_data.clear(); }
    data->vertex_data = {
        -0.5f, -0.5f, 0.0f, // bottom left
        0.5f, -0.5f, 0.0f, // bottom right
        0.5f, 0.5f, 0.0f, // top right

        -0.5f, -0.5f, 0.0f, // top right
        0.5f, 0.5f, 0.0f, // top left
        -0.5f, 0.5f, 0.0f // bottom left
    };

      data->n_vertex = 6;

    }
}

float* MeshComponent::GetVertexData()
{
  if (data->vertex_data.size() > 0) {
    LOG_F(INFO, "Vertex data retrieved");
    return data->vertex_data.data();
  }
  return nullptr;
}

size_t MeshComponent::GetVertexSizeb()
{
  if (data->vertex_data.size() > 0) {
    LOG_F(INFO, "Vertex data size retrieved");
    return data->vertex_data.size() * sizeof(float);
  }
  return 0;
}

size_t MeshComponent::GetVertexCount()
{
  return data->n_vertex;
}
#pragma endregion MeshComponent
