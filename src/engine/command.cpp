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

DrawCommand::DrawCommand(Entity& e) {
  entity = std::make_shared<Entity>(e);
}

void DrawCommand::BindUniforms() {

  //Check if transform is null
  std::shared_ptr<TransformComponent> transform = entity->GetTransformComponent();
  std::shared_ptr<ShaderComponent> shader = entity->GetShaderComponent();

  glm::vec3 position, scale, rotation;
  glm::mat4 traslationMatrix, rotationMatrix, scaleMatrix, worldMatrix;

  int shader_program;
  if (transform != nullptr) {

    //Parse data
    position = entity->GetTransformComponent()->GetPosition();
    scale = entity->GetTransformComponent()->GetScale();
    rotation = entity->GetTransformComponent()->GetRotation();
    worldMatrix = entity->GetTransformComponent()->GetModelMatrix();

    traslationMatrix = entity->GetTransformComponent()->GetTraslationMatrix();;
    rotationMatrix = entity->GetTransformComponent()->GetRotationMatrix();
    scaleMatrix = entity->GetTransformComponent()->GetScaleMatrix();
  }

  if (shader != nullptr) {
    shader_program = shader->GetShaderProgram();
  }

  std::weak_ptr<CameraComponent> camera = OpenGLEngine::Engine::Core::camera_;
  if (camera.lock() != nullptr) {
    glm::mat4 viewMatrix = camera.lock()->GetViewMatrix();
    glm::mat4 projectionMatrix = camera.lock()->GetProjectionMatrix();

    if (shader != nullptr) {
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
    }
  }
}

void DrawCommand::Execute() {
  if (entity->GetShaderComponent() != nullptr) {
    glUseProgram(entity->GetShaderComponent()->GetShaderProgram());
  }

  BindUniforms();
  if (entity->GetMeshComponent() != nullptr) {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glBindVertexArray(entity->GetMeshComponent()->GetVAO());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity->GetMeshComponent()->GetIBO());
    glDrawElements(GL_TRIANGLES, entity->GetMeshComponent()->GetVertexCount() * 3, GL_UNSIGNED_INT, nullptr);
  }
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

