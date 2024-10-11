//Author: Pablo "Pau" Core Palmero
//Date: 5-June-2024
//Email: p.core.dev@outlook.com
//This file contains the component class's implementation of the engine to add differents properties to the objects.

#include "engine/component.h"
#include "loguru/loguru.hpp"
#include "glad/glad.h"

#include <memory>
#include <vector>
#include <fstream>



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

#pragma region ShaderComponent

  ShaderComponent::ShaderComponent(int id) {
    this->id = id;
    this->type = ComponentType_Shader;
    data = std::make_unique<ShaderData>();
    data->vertex_shader_path = "../../src/engine/shaders/default.vert";
    data->fragment_shader_path = "../../src/engine/shaders/default.frag";
  }

  //void ShaderComponent::operator=(const ShaderComponent& other) {
  //  this->id = other.id;
  //  this->type = other.type;
  //}


void ShaderComponent::SetVertexShaderPath(const std::string& path) {
  data->vertex_shader_path = path;
}

void ShaderComponent::SetFragmentShaderPath(const std::string& path) {
  data->fragment_shader_path = path;
}

void ShaderComponent::SetGeometryShaderPath(const std::string& path) {
  data->geometry_shader_path = path;
}

std::string ShaderComponent::LoadShader(const std::string& path, std::string& shader_code)
{
  //Open the file
  std::ifstream shader(path);
  //Check if the file is open
  if (!shader.is_open()) {
    LOG_F(ERROR, "Failed to open file %s", path.c_str());
    return "";
  }
  //Read the file
  std::string loaded_code;
  std::string line;
  while (std::getline(shader, line)) {
    loaded_code += line + "\n";
  }
  //Close the file
  shader.close();
  //Copy the code to the destination
  shader_code = loaded_code;
  return shader_code;
}

int ShaderComponent::ProcessShader(){
//Vertex shader
LoadShader(data->vertex_shader_path, data->vertex_shader_code);
data->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
const char* vertex_shader_code_char = data->vertex_shader_code.c_str();
glShaderSource(data->vertex_shader, 1, &vertex_shader_code_char, nullptr);
glCompileShader(data->vertex_shader);
int success;
char infoLog[512];
glGetShaderiv(data->vertex_shader, GL_COMPILE_STATUS, &success);
if(!success) {
  glGetShaderInfoLog(data->vertex_shader, 512, nullptr, infoLog);
  LOG_F(ERROR, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog);
  return success;
}
else {
  LOG_F(INFO, "Vertex shader compiled correctly");
}

//Fragment shader
LoadShader(data->fragment_shader_path, data->fragment_shader_code);
data->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
const char* fragment_shader_code_char = data->fragment_shader_code.c_str();
glShaderSource(data->fragment_shader, 1, &fragment_shader_code_char, nullptr);
glCompileShader(data->fragment_shader);
glGetShaderiv(data->fragment_shader, GL_COMPILE_STATUS, &success);
if(!success) {
  glGetShaderInfoLog(data->fragment_shader, 512, nullptr, infoLog);
  LOG_F(ERROR, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s", infoLog);
  return success;
}
else {
  LOG_F(INFO, "Fragment shader compiled correctly");
}

//Shader program
data->shader_program = glCreateProgram();
glAttachShader(data->shader_program, data->vertex_shader);
glAttachShader(data->shader_program, data->fragment_shader);
glLinkProgram(data->shader_program);
glGetProgramiv(data->shader_program, GL_LINK_STATUS, &success);
if(!success) {
  glGetProgramInfoLog(data->shader_program, 512, nullptr, infoLog);
  LOG_F(ERROR, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", infoLog);
  return success;
}
else {
  LOG_F(INFO, "Shader program linked correctly");
}

glUseProgram(data->shader_program);
glDeleteShader(data->vertex_shader);
glDeleteShader(data->fragment_shader);

return 0;
}

#pragma endregion ShaderComponent

