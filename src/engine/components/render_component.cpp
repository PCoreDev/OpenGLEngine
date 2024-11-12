#include "engine/components/render_component.h"

#include "engine/components/mesh_component.h"
#include "engine/components/shader_component.h"
#include "engine/components/material_component.h"
#include "engine/components/transform_component.h"
#include "glad/glad.h"

#include "engine/entity.h"
#include "engine/core.h"

#include "engine/shader.h"

struct RenderData {
  bool enabled;
};


RenderComponent::RenderComponent(std::weak_ptr<Entity> e) {
  this->entity = e;
  this->id = entity.lock()->ID();
  this->type = ComponentType_Render;
  data = std::make_unique<RenderData>();
  data->enabled = true;
}

RenderComponent::RenderComponent(RenderComponent&& other)
{
  this->id = other.id;
  this->type = other.type;
  data = std::move(other.data);
}

RenderComponent& RenderComponent::operator=(RenderComponent&& other)
{
  this->id = other.id;
  this->type = other.type;
  data = std::move(other.data);
  return *this;
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
    //std::shared_ptr<MaterialComponent> material = entity.lock()->GetMaterialComponent();
    std::shared_ptr<MeshComponent> mesh = entity.lock()->GetMeshComponent();

    //if (entity.lock()->GetMeshComponent()->RenderMode()) {
    //  glCullFace(GL_BACK);
    //}
    //else {
    //  glCullFace(GL_FRONT);
    //}

    if (shader != nullptr && shader->Enable()) {
      shader->UseProgram();
    }
    else {
      OpenGLEngine::Engine::Core::shader_->UseProgram();
    }

    OpenGLEngine::Engine::Core::shader_->SetTexture("texture_sampler", 0);
    OpenGLEngine::Engine::Core::shader_->SetMat4("model_matrix", entity.lock()->GetTransformComponent()->GetModelMatrix());
    OpenGLEngine::Engine::Core::shader_->SetMat4("view_matrix", OpenGLEngine::Engine::Core::camera_->GetViewMatrix());
    OpenGLEngine::Engine::Core::shader_->SetMat4("projection_matrix", OpenGLEngine::Engine::Core::camera_->GetProjectionMatrix());


    /*if (material != nullptr) {
      glBindTexture(GL_TEXTURE_2D, material->GetTexture(material->GetTextureLength()));
    }*/

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Set to wireframe
    // Render your model here
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Reset to normal fill

    if (mesh != nullptr) {
      glBindVertexArray(mesh->GetVAO());
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->GetIBO());
      glDrawElements(GL_TRIANGLES, mesh->GetVertexCount() * 3, GL_UNSIGNED_INT, nullptr);
    }
  }

  /*
  *   if (data->enabled == true) {

    glUseProgram(Shader::GetProgram());


    std::shared_ptr<ShaderComponent> shader = entity.lock()->GetShaderComponent();
    ////std::shared_ptr<MaterialComponent> material = entity.lock()->GetMaterialComponent();
    std::shared_ptr<MeshComponent> mesh = entity.lock()->GetMeshComponent();

    //TODO Add shaders from shader component to shader class' program

    //if (shader != nullptr) {
    //  if (shader->UseShader()) {
    //    glUseProgram(shader->GetShaderProgram());
        shader->SetUniforms();
    //  }
    //}

    /*if (material != nullptr) {
      glBindTexture(GL_TEXTURE_2D, material->GetTexture(material->GetTextureLength()));
    }

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Set to wireframe
    // Render your model here
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Reset to normal fill

  if (mesh != nullptr) {
    glBindVertexArray(mesh->GetVAO());
    //glDrawArrays(GL_TRIANGLES, 0, mesh->GetVertexCount());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->GetIBO());
    glDrawElements(GL_TRIANGLES, mesh->GetVertexCount() * 3, GL_UNSIGNED_INT, nullptr);
  }
  */


}