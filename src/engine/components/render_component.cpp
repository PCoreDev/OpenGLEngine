#include "engine/components/render_component.h"

#include "engine/components/mesh_component.h"
#include "engine/components/shader_component.h"
#include "engine/components/material_component.h"
#include "engine/components/transform_component.h"
#include "engine/components/skybox_component.h"
#include "glad/glad.h"

#include "engine/entity.h"
#include "engine/core.h"

#include "engine/shader.h"



RenderComponent::RenderComponent(std::weak_ptr<Entity> e, bool enable) {
  this->entity = e;
  this->id = entity.lock()->ID();
  this->type = ComponentType_Render;
  data = std::make_unique<RenderData>();
  data->enabled = enable;
}

RenderComponent::RenderComponent(const RenderComponent& other){
  this->id = other.id;
  this->type = other.type;
  data = std::make_unique<RenderData>();
  data->enabled = other.data->enabled;
}

RenderComponent::RenderComponent(RenderComponent&& other) noexcept {
  this->id = other.id;
  this->type = other.type;
  data = std::move(other.data);
}

RenderComponent& RenderComponent::operator=(RenderComponent&& other) noexcept {
  if (this == &other) {
    return *this;
  }

  this->id = other.id;
  this->type = other.type;
  data = std::move(other.data);
  return *this;
}

void RenderComponent::operator=(const RenderComponent& other) {
  this->id = other.id;
  this->type = other.type;
  data = std::make_unique<RenderData>();
  data->enabled = other.data->enabled;
}

bool RenderComponent::IsEnabled() { return data->enabled; }

void RenderComponent::SetEnabled(bool enabled) { data->enabled = enabled; }

void RenderComponent::Render() {
  if (!data->enabled) return;

  auto entity_locked = entity.lock();
  auto shader = entity_locked->GetShaderComponent();
  auto mesh = entity_locked->GetMeshComponent();

  if (shader) {
    shader->UseShader();

    auto transform = entity_locked->GetTransformComponent();
    if (transform) {
      shader->SetMat4("model_matrix", transform->GetModelMatrix());
    }

    glm::mat4 view = OpenGLEngine::Engine::Core::camera_->GetViewMatrix();
    auto skybox = entity_locked->GetSkyBoxComponent();
    if (skybox) {
      shader->SetInt("skybox", 0);
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->GetSkyBoxID());
      view = glm::mat4(glm::mat3(view));
    }

    shader->SetMat4("view_matrix", view);
    shader->SetMat4("projection_matrix", OpenGLEngine::Engine::Core::camera_->GetProjectionMatrix());

    auto material = entity_locked->GetMaterialComponent();
    if (material) {
      material->SendToShader();
      material->BindTextures();
    }

    shader->SetVec3("directional_light.direction", glm::vec3(0.0f, -1.0f, 0.0f));
    shader->SetVec3("directional_light.ambient", glm::vec3(0.2f));
    shader->SetVec3("directional_light.diffuse", glm::vec3(0.5f));
    shader->SetVec3("directional_light.specular", glm::vec3(1.0f));

    shader->SetVec3("point_light[0].position", OpenGLEngine::Engine::Core::camera_->GetPosition());
    shader->SetVec3("point_light[0].ambient", glm::vec3(0.2f));
    shader->SetVec3("point_light[0].diffuse", glm::vec3(0.5f));
    shader->SetVec3("point_light[0].specular", glm::vec3(1.0f));
    shader->SetFloat("point_light[0].constant", 1.0f);
    shader->SetFloat("point_light[0].linear", 0.09f);
    shader->SetFloat("point_light[0].quadratic", 0.032f);
    shader->SetVec3("point_light[0].color", glm::vec3(1.0f, 1.0f, 1.0f));

    shader->SetInt("point_light_count", 1);

    shader->SetVec3("camera_position", OpenGLEngine::Engine::Core::camera_->GetPosition());
  }
  else {
    auto core_shader = OpenGLEngine::Engine::Core::shader_;
    core_shader->UseShader();

    auto transform = entity_locked->GetTransformComponent();
    core_shader->SetMat4("model_matrix", transform->GetModelMatrix());
    core_shader->SetMat4("view_matrix", OpenGLEngine::Engine::Core::camera_->GetViewMatrix());
    core_shader->SetMat4("projection_matrix", OpenGLEngine::Engine::Core::camera_->GetProjectionMatrix());


    core_shader->SetVec3("directional_light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
    core_shader->SetVec3("directional_light.ambient", glm::vec3(0.2f));
    core_shader->SetVec3("directional_light.diffuse", glm::vec3(0.5f));
    core_shader->SetVec3("directional_light.specular", glm::vec3(1.0f));


    core_shader->SetVec3("point_light[0].position", OpenGLEngine::Engine::Core::camera_->GetPosition());
    core_shader->SetVec3("point_light[0].ambient", glm::vec3(0.2f));
    core_shader->SetVec3("point_light[0].diffuse", glm::vec3(0.5f));
    core_shader->SetVec3("point_light[0].specular", glm::vec3(1.0f));
    core_shader->SetFloat("point_light[0].constant", 1.0f);
    core_shader->SetFloat("point_light[0].linear", 0.09f);
    core_shader->SetFloat("point_light[0].quadratic", 0.032f);
    //core_shader->SetVec3("point_light[0].color", glm::vec3(1.0f, 1.0f, 1.0f));

    core_shader->SetInt("point_light_count", 1);


    core_shader->SetVec3("camera_position", OpenGLEngine::Engine::Core::camera_->GetPosition());

    auto material = entity_locked->GetMaterialComponent();
    if (material) {
      material->BindTextures();
      material->SendToShader();
    }
  }

  glPolygonMode(GL_FRONT_AND_BACK, EngineInput::IsKeyPressed(EngineInput::kKeyNames_F13) ? GL_LINE : GL_FILL);

  if (mesh) {
    glDepthFunc(entity_locked->GetSkyBoxComponent() ? GL_LEQUAL : GL_LESS);
    glBindVertexArray(mesh->GetVAO());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->GetIBO());
    glDrawElements(GL_TRIANGLES, mesh->GetVertexCount() * 3, GL_UNSIGNED_INT, nullptr);
  }
}

void RenderComponent::RenderFrameBuffer(){

}

void RenderComponent::RenderLights()
{
  //TODO ...
}
