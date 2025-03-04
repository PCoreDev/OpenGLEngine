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


#include "engine/components/render_component.h"

#include <Windows.h>

//ClearCommand
void ClearCommand::Execute() {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

////DrawCommand
//
//void DrawCommand::Execute() {
//  if (entity->GetRenderComponent() != nullptr) {
//    entity->GetRenderComponent()->Render();
//  }
//}


DrawRenderBufferCommand::DrawRenderBufferCommand(EntityManager& manager, Shader& s, unsigned int fbo, unsigned int fb_texture, unsigned int quad_vao, unsigned int quad_ibo) {
  entity_manager = std::make_shared<EntityManager>(manager);
  shader = std::make_shared<Shader>(s);
  framebuffer = fbo;
  framebuffer_texture = fb_texture;
  screen_quad_vao = quad_vao;
  screen_quad_ibo = quad_ibo;
}

void DrawRenderBufferCommand::BindUniforms() {
  shader->UseShader();
  int screen_texture_location = glGetUniformLocation(shader->GetProgram(), "screen_texture");
  if (screen_texture_location != -1) {
    glUniform1i(screen_texture_location, 0); // Unidad de textura 0
  }

  int depth_texture_location = glGetUniformLocation(shader->GetProgram(), "depth_texture");
  if (depth_texture_location != -1) {
    glUniform1i(depth_texture_location, 1); // Unidad de textura 1
  }

  int stencil_texture_location = glGetUniformLocation(shader->GetProgram(), "stencil_texture");
  if (stencil_texture_location != -1) {
    glUniform1i(stencil_texture_location, 2); // Unidad de textura 2
  }
}

void DrawRenderBufferCommand::Execute() {

  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
  glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  //DrawObjects
  for (const auto& weak_entity : entity_manager->GetEntities()) {
    if (auto entity = weak_entity.lock()) {
      if (entity->GetRenderComponent() != nullptr) {
        entity->GetRenderComponent()->Render();
      }
    }
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  BindUniforms();
  glBindVertexArray(screen_quad_vao);
  glDepthFunc(GL_LESS);
  glDisable(GL_DEPTH_TEST);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, screen_quad_ibo);
  glActiveTexture(GL_TEXTURE0); // Activar la unidad de textura 0
  glBindTexture(GL_TEXTURE_2D, framebuffer_texture);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
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

//void DisplayList::AddDrawCommand(Entity& entity) {
//  auto command = std::make_unique<DrawCommand>(entity);
//  commands_.push_back(std::move(command));
//}

void DisplayList::AddDrawRenderBufferCommand(EntityManager& manager, Shader& s, unsigned int fbo, unsigned int fb_texture, unsigned int quad_vao, unsigned int quad_ibo){
  auto command = std::make_unique<DrawRenderBufferCommand>(manager, s, fbo, fb_texture, quad_vao, quad_ibo);
  commands_.push_back(std::move(command));
}

void DisplayList::Execute(){
  for (auto& command : commands_) { command->Execute(); }
}

