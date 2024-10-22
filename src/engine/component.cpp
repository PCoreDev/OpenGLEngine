//Author: Pablo "Pau" Core Palmero
//Date: 5-June-2024
//Email: p.core.dev@outlook.com
//This file contains the component class's implementation of the engine to add differents properties to the objects.

#include "engine/component.h"
#include "loguru/loguru.hpp"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "engine/core.h"
#include "engine/entity.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include <memory>
#include <vector>
#include <fstream>



#pragma region TransformComponent

TransformComponent::TransformComponent(int id) {
  this->id = id;
  this->type = ComponentType_Transform;
  data = std::make_unique<TransformData>();
  data->position = glm::vec3(0.0f, 0.0f, 0.0f);
  data->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
  data->scale = glm::vec3(1.0f, 1.0f, 1.0f);
  data->m_traslation = glm::translate(glm::mat4(1.0f), data->position);
  data->m_rotation = glm::rotate(glm::mat4(1.0f), glm::radians(data->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
  data->m_rotation *= glm::rotate(data->m_rotation, glm::radians(data->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
  data->m_rotation *= glm::rotate(data->m_rotation, glm::radians(data->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
  data->m_scale = glm::scale(glm::mat4(1.0f), data->scale);
  data->parent_id = id;
}

void TransformComponent::operator=(const TransformComponent& other) {
  this->id = other.id;
  this->type = other.type;
  data = std::make_unique<TransformData>(*other.data);
}

//Position
void TransformComponent::SetPosition(float x, float y, float z) {
  //TODO Check if the position changes.
  glm::vec3 new_position = glm::vec3(x, y, z);
  if (data->position != new_position) {
    data->position = new_position;

    //Update traslation matrix
    if (data->parent_id != id) {
      for (auto entity : OpenGLEngine::Engine::Core::entity_manager_->GetEntities()) {
        if (entity.lock()->ID() == data->parent_id) {
          data->m_traslation = entity.lock()->GetTransformComponent()->GetModelMatrix() * glm::translate(glm::mat4(1.0f), data->position);
        }
      }
    }
    else {
      data->m_traslation = glm::translate(glm::mat4(1.0f), data->position);
    }
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

    //Update rotation matrix
    if (data->parent_id != id) {
      for (auto entity : OpenGLEngine::Engine::Core::entity_manager_->GetEntities()) {
        if (entity.lock()->ID() == data->parent_id) {
          data->m_rotation = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
          data->m_rotation *= glm::rotate(data->m_rotation, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
          data->m_rotation *= glm::rotate(data->m_rotation, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
          data->m_rotation *= entity.lock()->GetTransformComponent()->GetModelMatrix();
        }
      }
    }
    else {

      data->m_rotation = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
      data->m_rotation *= glm::rotate(data->m_rotation, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
      data->m_rotation *= glm::rotate(data->m_rotation, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
    }
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
  //TODO Check if the scale changes.
  glm::vec3 new_scale = glm::vec3(x, y, z);
  if (data->scale != new_scale) {
    data->scale = new_scale;

    //Update scale matrix
    data->m_scale = glm::scale(glm::mat4(1.0f), data->scale);
  }
}

void TransformComponent::SetScale(float scale[3]) {
  SetScale(scale[0], scale[1], scale[2]);
}

void TransformComponent::SetScale(glm::vec3 scale) {
  SetScale(scale.x, scale.y, scale.z);
}

void TransformComponent::SetParent(Entity entity){
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
  else {
    return data->m_traslation;
  }
}

glm::mat4 TransformComponent::GetScaleMatrix() const {
  if (data->parent_id != id) {
    for (auto entity : OpenGLEngine::Engine::Core::entity_manager_->GetEntities()) {
      if (entity.lock()->ID() == data->parent_id) {
        return data->m_scale * entity.lock()->GetTransformComponent()->GetScaleMatrix();
      }
    }
  }
  else {
    return data->m_scale;
  }
}

glm::mat4 TransformComponent::GetRotationMatrix() const {
  if (data->parent_id != id) {
    for (auto entity : OpenGLEngine::Engine::Core::entity_manager_->GetEntities()) {
      if (entity.lock()->ID() == data->parent_id) {
        return data->m_rotation * entity.lock()->GetTransformComponent()->GetRotationMatrix();
      }
    }
  }
  else {
    return data->m_rotation;
  }
}

glm::mat4 TransformComponent::GetModelMatrix() const {
  if (data->parent_id != id) {
    for (auto entity : OpenGLEngine::Engine::Core::entity_manager_->GetEntities()) {
      if (entity.lock()->ID() == data->parent_id) {
        return data->m_traslation * data->m_rotation * data->m_scale * entity.lock()->GetTransformComponent()->GetModelMatrix();
      }
    }
  }
  else {
    return data->m_traslation * data->m_rotation * data->m_scale;
  }
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

void MeshData::Bind() {
  //TODO: Change all to one buffer (vertex, normal, uv)

    glCreateBuffers(1, &vbo); //vertex buffer object
    glCreateBuffers(1, &nbo); //normal buffer object
    glCreateBuffers(1, &ubo); //uv buffer object
    glCreateBuffers(1, &ibo); //index buffer object
                                          

    glNamedBufferStorage(vbo, vertex_data.size() * sizeof(float), vertex_data.data(), GL_DYNAMIC_STORAGE_BIT);

    glNamedBufferStorage(nbo, normal_data.size() * sizeof(float), normal_data.data(), GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferStorage(ubo, uv_data.size() * sizeof(float), uv_data.data(), GL_DYNAMIC_STORAGE_BIT);

    glNamedBufferStorage(ibo, index_data.size() * sizeof(unsigned int), index_data.data(), GL_DYNAMIC_STORAGE_BIT);

    glCreateVertexArrays(1, &vao);

    glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3 * sizeof(float)); //Vertex
    glVertexArrayVertexBuffer(vao, 1, nbo, 0, 3 * sizeof(float)); //Normals
    glVertexArrayVertexBuffer(vao, 2, ubo, 0, 2 * sizeof(float)); //UV

    glEnableVertexArrayAttrib(vao, 0);
    glEnableVertexArrayAttrib(vao, 1);
    glEnableVertexArrayAttrib(vao, 2);

    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, false, 0);
    glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, false, 0);
    glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, false, 0);

    glVertexArrayAttribBinding(vao, 0, 0);
    glVertexArrayAttribBinding(vao, 1, 1);
    glVertexArrayAttribBinding(vao, 2, 2);
}

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

      data->normal_data = {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
      };

      data->index_data = {
        0, 1, 2
      };
    }
    data->n_vertex = 3;
    data->Bind();
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

    data->index_data = {
        0, 1, 2,
        3, 4, 5
    };

    data->normal_data = {
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
    };
    data->uv_data = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

      data->n_vertex = 6;

    }
    data->Bind();
}

void MeshComponent::Cube(){
  if(data != nullptr){
    if(data->vertex_data.size() != 0) { data->vertex_data.clear(); }
    data->vertex_data = {
      //Front
         -0.5f, 0.5f, 0.5f,
         -0.5f, -0.5f, 0.5f,
         0.5f, -0.5f, 0.5f,
         0.5f, 0.5f, 0.5f,

         //Bottom
         -0.5f, -0.5f, -0.5f,
         -0.5f, -0.5f, 0.5f,
         0.5f, -0.5f, 0.5f,
         0.5f, -0.5f, -0.5f,

         //Back
         -0.5f, 0.5f, -0.5f,
         -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, 0.5f, -0.5f,

         //Right
         0.5f, 0.5f, 0.5f,
         0.5f, -0.5f, 0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, 0.5f, -0.5f,

         //Left
         -0.5f, 0.5f, -0.5f,
         -0.5f, -0.5f, -0.5f,
         -0.5f, -0.5f, 0.5f,
         -0.5f, 0.5f, 0.5f,

         //UP
         -0.5f, 0.5f, -0.5f,
         -0.5f, 0.5f, 0.5f,
          0.5f, 0.5f, 0.5f,
          0.5f, 0.5f, -0.5f
    };

    data->normal_data = {
      //Front
          0.0f, 0.0f, 0.5f,
          0.0f, 0.0f, 0.5f,
          0.0f, 0.0f, 0.5f,
          0.0f, 0.0f, 0.5f,

          //Bottom
          0.0f, -0.5f, 0.0f,
          0.0f, -0.5f, 0.0f,
          0.0f, -0.5f, 0.0f,
          0.0f, -0.5f, 0.0f,

          //Back
          0.0f, 0.0f, -0.5f,
          0.0f, 0.0f, -0.5f,
          0.0f, 0.0f, -0.5f,
          0.0f, 0.0f, -0.5f,

          //Right
          0.5f, 0.0f, 0.0f,
          0.5f, 0.0f, 0.0f,
          0.5f, 0.0f, 0.0f,
          0.5f, 0.0f, 0.0f,

          //Left
          -0.5f, 0.0f, 0.0f,
          -0.5f, 0.0f, 0.0f,
          -0.5f, 0.0f, 0.0f,
          -0.5f, 0.0f, 0.0f,

          //Up
          0.0f, 0.5f, 0.0f,
          0.0f, 0.5f, 0.0f,
          0.0f, 0.5f, 0.0f,
          0.0f, 0.5f, 0.0f
    };

    data->uv_data = {
      //Front
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f,

           //Bottom
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f,

           //Back
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f,

           //Right
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f,

           //Left
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f,

           //Up
           0.0f, 0.0f,
           0.0f, 1.0f,
           1.0f, 1.0f,
           1.0f, 0.0f
    };
    /*
    data->vertex_data = {
      //Front
      -0.5f, 0.5f, 0.5f,
      -0.5f, -0.5f, 0.5f,
      0.5f, -0.5f, 0.5f,
      0.5f, 0.5f, 0.5f,

      //Bottom
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f, 0.5f,
      0.5f, -0.5f, 0.5f,
      0.5f, -0.5f, -0.5f,

      //Back
      -0.5f, 0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, 0.5f, -0.5f,

      //Right
      0.5f, 0.5f, 0.5f,
      0.5f, -0.5f, 0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, 0.5f, -0.5f,

      //Left
      -0.5f, 0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f, 0.5f,
      -0.5f, 0.5f, 0.5f,

      //UP
      -0.5f, 0.5f, -0.5f,
      -0.5f, 0.5f, 0.5f,
      0.5f, 0.5f, 0.5f,
      0.5f, 0.5f, -0.5f, 

      //Front
      0.0f, 0.0f, 0.5f,
      0.0f, 0.0f, 0.5f,
      0.0f, 0.0f, 0.5f,
      0.0f, 0.0f, 0.5f,

      //Bottom
      0.0f, -0.5f, 0.0f,
      0.0f, -0.5f, 0.0f,
      0.0f, -0.5f, 0.0f,
      0.0f, -0.5f, 0.0f,

      //Back
      0.0f, 0.0f, -0.5f,
      0.0f, 0.0f, -0.5f,
      0.0f, 0.0f, -0.5f,
      0.0f, 0.0f, -0.5f,

      //Right
      0.5f, 0.0f, 0.0f,
      0.5f, 0.0f, 0.0f,
      0.5f, 0.0f, 0.0f,
      0.5f, 0.0f, 0.0f,

      //Left
      -0.5f, 0.0f, 0.0f,
      -0.5f, 0.0f, 0.0f,
      -0.5f, 0.0f, 0.0f,
      -0.5f, 0.0f, 0.0f,

      //Up
      0.0f, 0.5f, 0.0f,
      0.0f, 0.5f, 0.0f,
      0.0f, 0.5f, 0.0f,
      0.0f, 0.5f, 0.0f,

      //Front
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,

      //Bottom
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,

      //Back
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,

      //Right
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,

      //Left
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,

      //Up
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,
    };
*/
    data->index_data = {
      //Front 0, 1, 2, 3
        0,1,3,
        1,2,3,

        //Bottom 4, 5, 6, 7
        7,6,5,
        7,5,4,

        //Back 8, 9, 10, 11
        11,9,8,
        11,10,9,

        //Right 12, 13, 14, 15
        12,13,15,
        13,14,15,

        //Left 16, 17, 18, 19
        16,17,19,
        17,18,19,

        //Up 20, 21, 22, 23
        20,21,23,
        21,22,23
    };

    data->n_vertex = 24;

    data->Bind();
  }
}

void MeshComponent::LoadOBJ(const std::string& path){
  //TODO: Implement with tiny obj loader

}

float* MeshComponent::GetVertexData() {
  if (data->vertex_data.size() > 0) {
    LOG_F(INFO, "Vertex data retrieved");
    return data->vertex_data.data();
  }
  return nullptr;
}

size_t MeshComponent::GetVertexSizeb() {
  if (data->vertex_data.size() > 0) {
    LOG_F(INFO, "Vertex data size retrieved");
    return data->vertex_data.size() * sizeof(float);
  }
  return 0;
}

size_t MeshComponent::GetVertexCount() {
  return data->n_vertex;
}

unsigned int MeshComponent::GetVAO() {
  return data->vao;
}

unsigned int MeshComponent::GetVBO() {
  return data->vbo;
}

unsigned int MeshComponent::GetIBO(){
  return data->ibo;
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

void ShaderComponent::SetUniforms(Entity& entity){
//Set Color
int color_location = glGetUniformLocation(data->shader_program, "color");
glUniform4f(color_location, 1.0f, 0.0f, 1.0f, 1.0f);
}

int ShaderComponent::GetShaderProgram() {
  return data->shader_program;
}

#pragma endregion ShaderComponent

#pragma region CameraComponent

CameraComponent::CameraComponent(int id) {
  this->id = id;
  this->type = ComponentType_Camera;
  data = std::make_unique<CameraData>();
  glm::vec3 position;

  //Set Camera default target
  data->target = glm::vec3(0.0f, 0.0f, 0.0f);

  //Get Transform component
  std::shared_ptr<TransformComponent> transform;
  for (auto& entity : OpenGLEngine::Engine::Core::entity_manager_->GetEntities()) {
    if (entity.lock()->ID() == id) { transform = entity.lock()->GetTransformComponent(); }
  }

  //Set Position
  position = (transform != nullptr) ? transform->GetPosition() : glm::vec3(0.0f, 0.0f, 0.0f);


  data->direction = glm::normalize(position - data->target);

  glm::vec3 up_vector = glm::vec3(0.0f, 1.0f, 0.0f);
  data->right = glm::normalize(glm::cross(up_vector, data->direction));
  data->up = glm::cross(data->direction, data->right);

  data->view_matrix = glm::lookAt(position, position + data->direction, data->up);


  data->fov = 90.0f;
  data->aspect_ratio = 1280.0f / 720.0f;
  data->near_plane = 0.1f;
  data->far_plane = 1000.0f;

  data->projection_matrix = glm::perspective(glm::radians(data->fov), data->aspect_ratio, data->near_plane, data->far_plane);

  data->ortho_matrix = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, 0.1f, 1000.0f);
}

void CameraComponent::operator=(const CameraComponent& other) {
  this->id = other.id;
  this->type = other.type;
  data = std::make_unique<CameraData>(*other.data);
}

void CameraComponent::SetTarget(glm::vec3 target) {
  data->target = target;
}

void CameraComponent::SetFOV(float fov) {
  data->fov = fov;
}

void CameraComponent::SetAspectRatio(float aspect_ratio) {
  data->aspect_ratio = aspect_ratio;
}

void CameraComponent::SetNearPlane(float near_plane) {
  data->near_plane = near_plane;
}

void CameraComponent::SetFarPlane(float far_plane) {
  data->far_plane = far_plane;
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

glm::vec3 CameraComponent::GetTarget() { return data->target; }

glm::vec3 CameraComponent::GetDirection() { return data->direction; }

glm::vec3 CameraComponent::GetUp() { return data->up; }

float CameraComponent::GetFOV() { return data->fov; }

float CameraComponent::GetAspectRatio() { return data->aspect_ratio; }

float CameraComponent::GetNearPlane() { return data->near_plane; }

float CameraComponent::GetFarPlane() { return data->far_plane; }

void CameraComponent::UpdateMatrices(){

  std::shared_ptr<TransformComponent> transform;
  for (auto& entity : OpenGLEngine::Engine::Core::entity_manager_->GetEntities()) {
    if (entity.lock()->ID() == id) { transform = entity.lock()->GetTransformComponent(); }
  }
  //glm::vec3 position = (transform != nullptr) ? transform->GetPosition() : glm::vec3(0.0f, 0.0f, 0.0f);

  glm::vec3 position = transform->GetPosition();


  data->direction = glm::normalize(position - data->target);

  glm::vec3 up_vector = glm::vec3(0.0f, 1.0f, 0.0f);
  data->right = glm::normalize(glm::cross(up_vector, data->direction));
  data->up = glm::cross(data->direction, data->right);

  data->view_matrix = glm::lookAt(position, position + data->direction, data->up);

  data->projection_matrix = glm::perspective(glm::radians(data->fov), data->aspect_ratio, data->near_plane, data->far_plane);

  data->ortho_matrix = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, data->near_plane, data->far_plane);
}

glm::vec3 CameraComponent::GetRight() { return data->right; }

glm::mat4 CameraComponent::GetViewMatrix() { return data->view_matrix; }

glm::mat4 CameraComponent::GetProjectionMatrix() { return data->projection_matrix; }

glm::mat4 CameraComponent::GetOrthoMatrix() { return data->ortho_matrix; }

#pragma endregion CameraComponent

#pragma region MeterialComponent

MaterialComponent::MaterialComponent(int id) {
  this->id = id;
  this->type = ComponentType_Material;
  data = std::make_unique<MaterialData>();
}

void MaterialComponent::operator=(const MaterialComponent& other){
  this->id = other.id;
  this->type = other.type;
  data = std::make_unique<MaterialData>(*other.data);
}

void MaterialComponent::LoadTexture(const std::string& path){
  data->m_texture.data = stbi_load(path.c_str(), &data->m_texture.width, &data->m_texture.height, &data->m_texture.n_channels, 0);

  if (data->m_texture.data) {
    LOG_F(INFO, "Texture loaded correctly");
    Process();
  }
  else {
    LOG_F(ERROR, "Failed to load texture");
  }


}

unsigned int MaterialComponent::GetTexture() { return data->m_texture.texture; }

void MaterialComponent::Process(){
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, data->m_texture.border_color);
  

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glGenTextures(1, &data->m_texture.texture);

  glBindTexture(GL_TEXTURE_2D, data->m_texture.texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data->m_texture.width, data->m_texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data->m_texture.data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data->m_texture.data);
}

#pragma endregion MeterialComponent
