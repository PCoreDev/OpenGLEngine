//Author: Pablo "Pau" Core Palmero
//Date: 4-June-2024
//Email: p.core.dev@outlook.com
//This header contains the primitive class of the engine to render objectes.

#include "engine/command.h"
#include "engine/component.h"
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "engine/core.h"

//ClearCommand
void ClearCommand::Execute() {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

//DrawCommand

DrawCommand::DrawCommand(Entity& entity) {
  
  id = entity.ID();



  ////What I need to draw is.
  ////Vertex buffer id
  //vao = entity.GetMeshComponent()->GetVAO();
  //vbo = entity.GetMeshComponent()->GetVBO();
  //ibo = entity.GetMeshComponent()->GetIBO();
  //n_index = entity.GetMeshComponent()->GetVertexCount();
  //shader_program = entity.GetShaderComponent()->GetShaderProgram();
  ////Index buffer id
  ////n_index
  ////vao
  //
  ////model matrix
  ////view matrix
  ////projection matrix
  ////view projection matrix
  ////camera position
  ////entity position

  //  // Define position, scale, and rotation
  //if (entity.GetTransformComponent() != nullptr) {
  //  position = entity.GetTransformComponent()->GetPosition();
  //  scale = entity.GetTransformComponent()->GetScale();
  //  rotation = entity.GetTransformComponent()->GetRotation();
  //  worldMatrix = entity.GetTransformComponent()->GetModelMatrix();
  //}
}

void DrawCommand::BindUniforms() {
  
  //Check if transform is null

  glm::vec3 position;
  glm::vec3 scale;
  glm::vec3 rotation;
  glm::mat4 worldMatrix;
  int shader_program;
  for (auto& entity : OpenGLEngine::Engine::Core::entity_manager_->GetEntities()) {
    if (entity.lock()->ID() == id) {
      if (entity.lock()->GetTransformComponent() != nullptr) {
        position = entity.lock()->GetTransformComponent()->GetPosition();
        scale = entity.lock()->GetTransformComponent()->GetScale();
        rotation = entity.lock()->GetTransformComponent()->GetRotation();
        worldMatrix = entity.lock()->GetTransformComponent()->GetModelMatrix();
        shader_program = entity.lock()->GetShaderComponent()->GetShaderProgram();
      }
    }
  }


  // Create translation matrix
  glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);

  // Create rotation matrices for each axis
  glm::mat4 rotationMatrix = glm::mat4(1.0f);
  rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
  rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
  rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

  // Create scale matrix
  glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

  // Combine all to create the world matrix
  

  // Define camera parameters
  glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -5.0f); // Camera position
  glm::vec3 cameraTarget = position; // Target position
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // Up direction

  // Calculate the view matrix
  glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraTarget, up);

  // Field of view, aspect ratio, near and far planes
  float fov = 45.0f;
  float aspectRatio = 800.0f / 600.0f; // Example aspect ratio (width/height)
  float nearPlane = 0.1f;
  float farPlane = 100.0f;

  glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

  int model_matrix_location = glGetUniformLocation(shader_program, "model_matrix");
  if (model_matrix_location != -1) {
    glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(worldMatrix));
  }

  int view_matrix_location = glGetUniformLocation(shader_program, "view_matrix");
  if (view_matrix_location != -1) {
    glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, glm::value_ptr(viewMatrix));
  }

  int projection_matrix_location = glGetUniformLocation(shader_program, "projection_matrix");
  if (projection_matrix_location != -1) {
    glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
  }

  //int camera_position_location = glGetUniformLocation(shader_program, "camera_position");
  //if (camera_position_location != -1) {
  //  glUniform3fv(camera_position_location, 1, glm::value_ptr(camera_position));
  //}

  //int entity_position_location = glGetUniformLocation(shader_program, "entity_position");
  //if (entity_position_location != -1) {
  //  glUniform3fv(entity_position_location, 1, glm::value_ptr(position));
  //}




    //view matrix
    //projection matrix
    //view projection matrix
    //model matrix
    //Rest of the uniforms for the shaders, color, material,lights, etc...
}

void DrawCommand::Execute() {
  for (auto& entity : OpenGLEngine::Engine::Core::entity_manager_->GetEntities()) {
    if (entity.lock()->ID() == id) {
      glUseProgram(entity.lock()->GetShaderComponent()->GetShaderProgram());

      BindUniforms();
      if (entity.lock()->GetMeshComponent() != nullptr) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glBindVertexArray(entity.lock()->GetMeshComponent()->GetVAO());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity.lock()->GetMeshComponent()->GetIBO());
        glDrawElements(GL_TRIANGLES, entity.lock()->GetMeshComponent()->GetVertexCount() * 9, GL_UNSIGNED_INT, nullptr);
      }
    }
  }
  //glUseProgram(shader_program);

  //BindUniforms();

  //glEnable(GL_CULL_FACE);
  //glBindVertexArray(vao);
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  //glDrawElements(GL_TRIANGLES, n_index, GL_UNSIGNED_INT, nullptr);
}

DrawRenderBufferCommand::DrawRenderBufferCommand() {
}

//DrawRenderBuffer
void DrawRenderBufferCommand::BindUniforms() {
  int screen_texture_location = glGetUniformLocation(0, "screen_texture");
  if(screen_texture_location != -1) {
    glUniform1i(screen_texture_location, 0);
  }

  int depth_texture_location = glGetUniformLocation(0, "depth_texture");
  if (depth_texture_location != -1) {
    glUniform1i(depth_texture_location, 0);
  }

  int stencil_texture_location = glGetUniformLocation(0, "stencil_texture");
  if (stencil_texture_location != -1) {
    glUniform1i(stencil_texture_location, 0);
  }
}

void DrawRenderBufferCommand::Execute() {
  glUseProgram(0);

  BindUniforms();

  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //0 = buffer data
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


//DisplayList

DisplayList::DisplayList(DisplayList&& other) noexcept {
  commands_ = std::move(other.commands_);
}

DisplayList& DisplayList::operator=(DisplayList&& other) noexcept {
  if (this != &other) {
    commands_ = std::move(other.commands_);
  }
  return *this;
}

DisplayList::~DisplayList() {
  Clear();
}

bool DisplayList::IsEmpty() const {
  return commands_.empty();
}

void DisplayList::Clear() {
  commands_.clear();
}

void DisplayList::Swap(DisplayList& other) {
  commands_.swap(other.commands_);
}

void DisplayList::AddClearCommand(float r, float g, float b, float a) {
  auto command = std::make_unique<ClearCommand>(r, g, b, a);
  commands_.push_back(std::move(command));
}

void DisplayList::AddDrawCommand(Entity& entity) {
  auto command = std::make_unique<DrawCommand>(entity);
  commands_.push_back(std::move(command));
}

void DisplayList::AddDrawRenderBufferCommand() {
}

void DisplayList::Execute(){
  for (auto& command : commands_) { command->Execute(); }
}

