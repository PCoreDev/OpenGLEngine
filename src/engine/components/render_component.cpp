#include "engine/components/render_component.h"

#include "engine/components/mesh_component.h"
#include "engine/components/shader_component.h"
#include "engine/components/material_component.h"
#include "engine/components/transform_component.h"
#include "engine/components/skybox_component.h"
#include "engine/components/light_component.h"
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
  auto shader_component = entity_locked->GetShaderComponent();
  auto mesh = entity_locked->GetMeshComponent();
  auto shader = OpenGLEngine::Engine::Core::shader_;

  if (shader_component) {
    shader = shader_component->GetShader();
  }

  shader->UseShader();
  MatrixToShader(shader);
  RenderLights(shader);

  glPolygonMode(GL_FRONT_AND_BACK, EngineInput::IsKeyPressed(EngineInput::kKeyNames_F13) ? GL_LINE : GL_FILL);

  glDepthFunc(entity_locked->GetSkyBoxComponent() ? GL_LEQUAL : GL_LESS);
  if (mesh) {
    auto material = entity_locked->GetMaterialComponent();
    for (int i = 0; i < mesh->GetMeshCount(); ++i) {
      if (material) {
        material->BindMaterial(shader, i);
      }
      glBindVertexArray(mesh->GetVAO()[i]);
      glBindBuffer(GL_ARRAY_BUFFER, mesh->GetVBO()[i]);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->GetIBO()[i]);
      glDrawElements(GL_TRIANGLES, mesh->GetVertexCount()[i] * 3, GL_UNSIGNED_INT, nullptr);
    }
  }
}

void RenderComponent::RenderLights(std::shared_ptr<Shader> shader){
  std::weak_ptr<Entity> directional_light;
  std::vector<std::weak_ptr<Entity>> point_lights;
  std::vector<std::weak_ptr<Entity>> spot_lights;

  for (auto entity : OpenGLEngine::Engine::core->entity_manager_->GetEntitiesWithLights()) {
    if (entity.lock()->GetLightComponent()->GetLightType() == LightComponent::LightType::Directional) {
      directional_light = entity;
    }
    else if (entity.lock()->GetLightComponent()->GetLightType() == LightComponent::LightType::Point) {
      point_lights.push_back(entity);
    }
    else if (entity.lock()->GetLightComponent()->GetLightType() == LightComponent::LightType::Spot) {
      spot_lights.push_back(entity);
    }
  }

  //directional light
  shader->SetVec3("directional_light.direction", directional_light.lock()->GetLightComponent()->GetDirection());
  shader->SetVec3("directional_light.ambient", directional_light.lock()->GetLightComponent()->GetAmbient());
  shader->SetVec3("directional_light.diffuse", directional_light.lock()->GetLightComponent()->GetDiffuse());
  shader->SetVec3("directional_light.specular", directional_light.lock()->GetLightComponent()->GetSpecular());
  shader->SetVec3("directional_light.color", directional_light.lock()->GetLightComponent()->GetLightColor());


  //point light
  for (int i = 0; i < point_lights.size(); ++i) {
    std::string index = std::to_string(i);
    shader->SetVec3("point_light[" + index + ']' + ".position", point_lights[i].lock()->GetTransformComponent()->GetPosition());
    shader->SetVec3("point_light[" + index + ']' + ".ambient", point_lights[i].lock()->GetLightComponent()->GetAmbient());
    shader->SetVec3("point_light[" + index + ']' + ".diffuse", point_lights[i].lock()->GetLightComponent()->GetDiffuse());
    shader->SetVec3("point_light[" + index + ']' + ".specular", point_lights[i].lock()->GetLightComponent()->GetSpecular());
    shader->SetFloat("point_light[" + index + ']' + ".constant", point_lights[i].lock()->GetLightComponent()->GetConstant());
    shader->SetFloat("point_light[" + index + ']' + ".linear", point_lights[i].lock()->GetLightComponent()->GetLinear());
    shader->SetFloat("point_light[" + index + ']' + ".quadratic", point_lights[i].lock()->GetLightComponent()->GetQuadratic());
    shader->SetVec3("point_light[" + index + ']' + ".color", point_lights[i].lock()->GetLightComponent()->GetLightColor());
  }

  if (point_lights.size() > 0)
    shader->SetInt("point_light_count", point_lights.size());

  //spot light
  for (int i = 0; i < spot_lights.size(); ++i) {
    std::string index = std::to_string(i);
    shader->SetVec3("spot_light[" + index + ']' + ".position", spot_lights[i].lock()->GetTransformComponent()->GetPosition());
    shader->SetVec3("spot_light[" + index + ']' + ".direction", spot_lights[i].lock()->GetLightComponent()->GetDirection());
    shader->SetFloat("spot_light[" + index + ']' + ".cutOff", spot_lights[i].lock()->GetLightComponent()->GetCutOff());
    shader->SetVec3("point_light[" + index + ']' + ".ambient", spot_lights[i].lock()->GetLightComponent()->GetAmbient());
    shader->SetVec3("point_light[" + index + ']' + ".diffuse", spot_lights[i].lock()->GetLightComponent()->GetDiffuse());
    shader->SetVec3("point_light[" + index + ']' + ".specular", spot_lights[i].lock()->GetLightComponent()->GetSpecular());
    shader->SetFloat("point_light[" + index + ']' + ".constant", spot_lights[i].lock()->GetLightComponent()->GetConstant());
    shader->SetFloat("point_light[" + index + ']' + ".linear", spot_lights[i].lock()->GetLightComponent()->GetLinear());
    shader->SetFloat("point_light[" + index + ']' + ".quadratic", spot_lights[i].lock()->GetLightComponent()->GetQuadratic());
    shader->SetVec3("spot_light[" + index + ']' + ".color", spot_lights[i].lock()->GetLightComponent()->GetLightColor());
  }

  if (spot_lights.size() > 0)
    shader->SetInt("spot_light_count", spot_lights.size());
}

void RenderComponent::MatrixToShader(std::shared_ptr<Shader> shader)
{
  auto entity_locked = entity.lock();
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
  shader->SetVec3("camera_position", OpenGLEngine::Engine::Core::camera_->GetPosition());
  shader->SetVec3("camera_direction", OpenGLEngine::Engine::Core::camera_->GetDirection());
}
