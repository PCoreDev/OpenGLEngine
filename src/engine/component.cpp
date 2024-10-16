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
  data->m_translation = glm::translate(glm::mat4(1.0f), data->position);
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

    //Update translation matrix
    if (data->parent_id != id) {
      for (auto entity : OpenGLEngine::Engine::Core::entity_manager_->GetEntities()) {
        if (entity.lock()->ID() == data->parent_id) {
          data->m_translation = entity.lock()->GetTransformComponent()->GetModelMatrix() * glm::translate(glm::mat4(1.0f), data->position);
        }
      }
    }
    else {
      data->m_translation = glm::translate(glm::mat4(1.0f), data->position);
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

glm::mat4 TransformComponent::GetModelMatrix() const {
  if (data->parent_id != id) {
    for (auto entity : OpenGLEngine::Engine::Core::entity_manager_->GetEntities()) {
      if (entity.lock()->ID() == data->parent_id) {
        return data->m_translation * data->m_rotation * data->m_scale * entity.lock()->GetTransformComponent()->GetModelMatrix();
      }
    }
  }
  else {
    return data->m_translation * data->m_rotation * data->m_scale;
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

