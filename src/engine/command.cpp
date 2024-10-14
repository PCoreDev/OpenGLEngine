//Author: Pablo "Pau" Core Palmero
//Date: 4-June-2024
//Email: p.core.dev@outlook.com
//This header contains the primitive class of the engine to render objectes.

#include "engine/command.h"
#include "engine/component.h"
#include "glad/glad.h"

//ClearCommand
void ClearCommand::Execute() {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

//DrawCommand

DrawCommand::DrawCommand(Entity& entity) {
  //What I need to draw is.
  //Vertex buffer id
  vao = entity.GetMeshComponent()->GetVAO();
  vbo = entity.GetMeshComponent()->GetVBO();
  n_index = entity.GetMeshComponent()->GetVertexCount();
  shader_program = entity.GetShaderComponent()->GetShaderProgram();
  //Index buffer id
  //n_index
  //vao
  
  //model matrix
  //view matrix
  //projection matrix
  //view projection matrix
  //camera position
  //entity position

}

void DrawCommand::BindUniforms() {
    //view matrix
    //projection matrix
    //view projection matrix
    //model matrix
    //Rest of the uniforms for the shaders, color, material,lights, etc...
}

void DrawCommand::Execute() {
  glUseProgram(shader_program);

  BindUniforms();

  glEnable(GL_CULL_FACE);
  glBindVertexArray(vao); //0 = vao
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer); //0 = buffer data
  glDrawElements(GL_TRIANGLES, n_index, GL_UNSIGNED_INT, nullptr); //0 = number of vertex
}

DrawRenderBufferCommand::DrawRenderBufferCommand() {
}

//DrawRenderBuffer
void DrawRenderBufferCommand::BindUniforms() {
  int screen_texture_location = glGetUniformLocation(0, "screen_texture");
  if(screen_texture_location != -1) {
    glUniform1i(screen_texture_location, 0); //0 = screen_tex
  }

  int depth_texture_location = glGetUniformLocation(0, "depth_texture");
  if (depth_texture_location != -1) {
    glUniform1i(depth_texture_location, 0); //0 = depth_tex
  }

  int stencil_texture_location = glGetUniformLocation(0, "stencil_texture");
  if (stencil_texture_location != -1) {
    glUniform1i(stencil_texture_location, 0); //0 = stencil_tex
  }
}

void DrawRenderBufferCommand::Execute() {
  glUseProgram(0);

  BindUniforms();

  glBindVertexArray(0); //0 = vao
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
  entity.GetShaderComponent()->ProcessShader();
  auto command = std::make_unique<DrawCommand>(entity);
  commands_.push_back(std::move(command));
}

void DisplayList::AddDrawRenderBufferCommand() {
}

void DisplayList::Execute(){
  for (auto& command : commands_) { command->Execute(); }
}

