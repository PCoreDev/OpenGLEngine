//Author: Pablo "Pau" Core Palmero
//Date: 5-June-2024
//Email: p.core.dev@outlook.com
//This file contains the component class's implementation of the engine to add differents properties to the objects.

#include "engine/component.h"
#include "loguru/loguru.hpp"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "engine/core.h"
#include "engine/entity.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include <memory>
#include <vector>
#include <fstream>



#pragma region TransformComponent

TransformComponent::TransformComponent(std::weak_ptr<Entity> e) {
  this->entity = e;
  this->id = entity.lock()->ID();
  this->type = ComponentType_Transform;
  data = std::make_unique<TransformData>();
  data->position = glm::vec3(0.0f, 0.0f, 0.0f);
  data->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
  data->scale = glm::vec3(1.0f, 1.0f, 1.0f);
  data->UpdateTraslationMatrix();
  data->UpdateRotationMatrix();
  data->UpdateScaleMatrix();
  data->parent_id = this->id;
}

void TransformComponent::operator=(const TransformComponent& other) {
  this->id = other.id;
  this->type = other.type;
  data = std::make_unique<TransformData>(*other.data);
}

//Position
void TransformComponent::SetPosition(float x, float y, float z) {
  glm::vec3 new_position = glm::vec3(x, y, z);
  if (data->position != new_position) {
    data->position = new_position;
    data->UpdateTraslationMatrix();
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
    data->UpdateRotationMatrix();
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
  glm::vec3 new_scale = glm::vec3(x, y, z);
  if (data->scale != new_scale) {
    data->scale = new_scale;
    data->UpdateScaleMatrix();
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
  return data->m_traslation;
}

glm::mat4 TransformComponent::GetScaleMatrix() const {
  if (data->parent_id != id) {
    for (auto entity : OpenGLEngine::Engine::Core::entity_manager_->GetEntities()) {
      if (entity.lock()->ID() == data->parent_id) {
        return data->m_scale * entity.lock()->GetTransformComponent()->GetScaleMatrix();
      }
    }
  }
  return data->m_scale;
}

glm::mat4 TransformComponent::GetRotationMatrix() const {
  if (data->parent_id != id) {
    for (auto entity : OpenGLEngine::Engine::Core::entity_manager_->GetEntities()) {
      if (entity.lock()->ID() == data->parent_id) {
        return data->m_rotation * entity.lock()->GetTransformComponent()->GetRotationMatrix();
      }
    }
  }
  return data->m_rotation;
}

glm::mat4 TransformComponent::GetModelMatrix() const {
  return data->m_model;
}

void TransformData::UpdateTraslationMatrix() {
  m_traslation = glm::mat4(1.0f);
  m_traslation = glm::translate(m_traslation, position);
  UpdateModelMatrix();
}

void TransformData::UpdateScaleMatrix() {
  m_scale = glm::mat4(1.0f);
  m_scale = glm::scale(m_scale, scale);
  UpdateModelMatrix();
}

void TransformData::UpdateRotationMatrix() {
  m_rotation = glm::mat4(1.0f);
  m_rotation = glm::rotate(m_rotation, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
  m_rotation = glm::rotate(m_rotation, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
  m_rotation = glm::rotate(m_rotation, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
  UpdateModelMatrix();
}

void TransformData::UpdateModelMatrix(){
  m_model = glm::mat4(1.0f);
  m_model = m_traslation * m_rotation * m_scale;
}

#pragma endregion TransformComponent

#pragma region RenderComponent
  RenderComponent::RenderComponent(std::weak_ptr<Entity> e) {
    this->entity = e;
    this->id = entity.lock()->ID();
    this->type = ComponentType_Render;
    data = std::make_unique<RenderData>();
    data->enabled = true;
  }

  void RenderComponent::operator=(const RenderComponent& other) {
    this->id = other.id;
    this->type = other.type;
  }

  bool RenderComponent::IsEnabled()
  {
    return data->enabled;
  }

  void RenderComponent::SetEnabled(bool enabled) {
    data->enabled = enabled;
  }

  void RenderComponent::Render() {
    if (data->enabled == true) {
      std::shared_ptr<ShaderComponent> shader = entity.lock()->GetShaderComponent();
      std::shared_ptr<MaterialComponent> material = entity.lock()->GetMaterialComponent();
      std::shared_ptr<MeshComponent> mesh = entity.lock()->GetMeshComponent();

      if (shader != nullptr) {
        if (shader->UseShader()) {
          glUseProgram(shader->GetShaderProgram());
          shader->SetUniforms();
        }
      }

      glEnable(GL_CULL_FACE);
      glCullFace(GL_BACK);

      if (material != nullptr) {
        glBindTexture(GL_TEXTURE_2D, material->GetTexture());
      }

      if (mesh != nullptr) {
        glBindVertexArray(mesh->GetVAO());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->GetIBO());
        glDrawElements(GL_TRIANGLES, mesh->GetVertexCount() * 3, GL_UNSIGNED_INT, nullptr);
      }
    }
  }

#pragma endregion RenderComponent
  
#pragma region MeshComponent

void MeshData::Bind() {
  //TODO: Change all to one buffer (vertex, normal, uv)

    glCreateBuffers(1, &vbo); //vertex buffer object
    glCreateBuffers(1, &nbo); //normal buffer object
    glCreateBuffers(1, &ubo); //uv buffer object
    glCreateBuffers(1, &ibo); //index buffer object
                                          


    glNamedBufferStorage(vbo, static_cast<GLsizei>(vertex_data.size() * sizeof(float)), vertex_data.data(), GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferStorage(nbo, static_cast<GLsizei>(normal_data.size() * sizeof(float)), normal_data.data(), GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferStorage(ubo, static_cast<GLsizei>(uv_data.size() * sizeof(float)), uv_data.data(), GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferStorage(ibo, static_cast<GLsizei>(index_data.size() * sizeof(unsigned int)), index_data.data(), GL_DYNAMIC_STORAGE_BIT);

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

  MeshComponent::MeshComponent(std::weak_ptr<Entity> e) {
    this->entity = e;
    this->id = entity.lock()->ID();
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

  ShaderComponent::ShaderComponent(std::weak_ptr<Entity> e) {
    this->entity = e;
    this->id = entity.lock()->ID();
    this->type = ComponentType_Shader;
    data = std::make_unique<ShaderData>();
    data->vertex_shader_path = "../../src/engine/shaders/default.vert";
    data->fragment_shader_path = "../../src/engine/shaders/default.frag";
    data->active = true;
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

void ShaderComponent::SetUniforms(){
  std::shared_ptr<TransformComponent> transform = entity.lock()->GetTransformComponent();
  std::shared_ptr<MaterialComponent> material = entity.lock()->GetMaterialComponent();

  if (material != nullptr) {
      //bind texture
      int texture_location = glGetUniformLocation(data->shader_program, "texture_sampler");
      if (texture_location != -1) {
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(texture_location, 0);
      } else { LOG_F(ERROR, "texture_sampler not found in shader program"); }
  } else { LOG_F(ERROR, "MaterialComponent not found for entity with ID %d", id); }

  if (OpenGLEngine::Engine::Core::camera_ != nullptr) {
    if (transform != nullptr) {
      int model_matrix_location = glGetUniformLocation(data->shader_program, "model_matrix");
      if (model_matrix_location != -1) {
        glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(transform->GetModelMatrix()));
      }
      else { LOG_F(ERROR, "model_matrix not found in shader program"); }
    } else { LOG_F(ERROR, "TransformComponent not found for entity with ID %d", id); }

        int view_matrix_location = glGetUniformLocation(data->shader_program, "view_matrix");
        if (view_matrix_location != -1) {
          glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, glm::value_ptr(OpenGLEngine::Engine::Core::camera_->GetViewMatrix()));
        } else { LOG_F(ERROR, "view_matrix not found in shader program"); }

        int projection_matrix_location = glGetUniformLocation(data->shader_program, "projection_matrix");
        if (projection_matrix_location != -1) {
          glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, glm::value_ptr(OpenGLEngine::Engine::Core::camera_->GetProjectionMatrix()));
        } else { LOG_F(ERROR, "projection_matrix not found in shader program"); }
  } else { LOG_F(ERROR, "There isn't any camera set"); }
}

int ShaderComponent::GetShaderProgram() {
  return data->shader_program;
}

bool ShaderComponent::UseShader()
{
  return data->active;
}

#pragma endregion ShaderComponent

#pragma region CameraComponent

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

void CameraComponent::MoveCamera(){
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
//
//glm::mat4 CameraComponent::GetOrthoMatrix() { return data->ortho_matrix; }

#pragma endregion CameraComponent

#pragma region MeterialComponent

MaterialComponent::MaterialComponent(std::weak_ptr<Entity> e) {
  this->entity = e;
  this->id = entity.lock()->ID();
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
