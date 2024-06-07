//Author: Pablo "Pau" Core Palmero
//Date: 5-June-2024
//Email: p.core.dev@outlook.com
//This file contains the component class's implementation of the engine to add differents properties to the objects.

#include "engine/component.h"

namespace OpenGLEngine {

  enum ComponentType {
    ComponentType_Invalid = 0,
    ComponentType_Render,
    ComponentType_Transform,
    ComponentType_Physics,
    ComponentType_Node,
    ComponentType_Sound,
    ComponentType_Light,
    ComponentType_Camera,
    ComponentType_MAX,
  };


#pragma region TransformComponent
  struct TransformData{
  public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
  private:

    glm::mat4 m_translation;
    glm::mat4 m_rotation;
    glm::mat4 m_scale;
    glm::mat4 m_model;
  };

  TransformComponent::TransformComponent(int id)
  {
    this->id = id;
    this->type = ComponentType_Transform;
    data = std::make_unique<TransformData>();
  }

  void TransformComponent::operator=(const TransformComponent& other)
  {
    this->id = other.id;
    this->type = other.type;
    data = std::make_unique<TransformData>(*other.data);
  }

  //Position
  void TransformComponent::SetPosition(float x, float y, float z)
  {
    data->position = glm::vec3(x, y, z);
  }

  void TransformComponent::SetPosition(float position[3])
  {
    data->position = glm::vec3(position[0], position[1], position[2]);
  }

  void TransformComponent::SetPosition(glm::vec3 position)
  {
    data->position = position;
  }

  //Rotation
  void TransformComponent::SetRotation(float x, float y, float z)
  {
    data->rotation = glm::vec3(x, y, z);
  
  }

  void TransformComponent::SetRotation(float rotation[3])
  {
    data->rotation = glm::vec3(rotation[0], rotation[1], rotation[2]);
  }

  void TransformComponent::SetRotation(glm::vec3 rotation)
  {
    data->rotation = rotation;
  
  }

  //Scale
  void TransformComponent::SetScale(float x, float y, float z)
  {
    data->scale = glm::vec3(x, y, z);
  
  }

  void TransformComponent::SetScale(float scale[3])
  {
    data->scale = glm::vec3(scale[0], scale[1], scale[2]);
  
  }

  void TransformComponent::SetScale(glm::vec3 scale)
  {
    data->scale = scale;
  
  
  }

#pragma endregion TransformComponent

#pragma region RenderComponent
  RenderComponent::RenderComponent(int id)
  {
    this->id = id;
    this->type = ComponentType_Render;
  }

  void RenderComponent::operator=(const RenderComponent& other)
  {
    this->id = other.id;
    this->type = other.type;
  }
#pragma endregion RenderComponent

#pragma region MaterialComponent
  #pragma region MaterialParameters
  struct MaterialParameters {

    MaterialParameters();
    MaterialParameters(const MaterialParameters& other);
    void operator=(const MaterialParameters& other);

    glm::vec4 base_color;
    glm::vec3 albedo;
    float emissive;
    float roughness;
    float metallic;
    float ambient_oclussion;
    unsigned int material_id;//Program
    unsigned int texture_ID;
    bool affected_by_light;
    bool can_cast_shadows;
  };

  MaterialParameters::MaterialParameters()
  {
    base_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    albedo = glm::vec3(1.0f, 1.0f, 1.0f);
    emissive = 0.0f;
    roughness = 0.0f;
    metallic = 0.0f;
    ambient_oclussion = 0.0f;
    material_id = 0;
    texture_ID = 0;
    affected_by_light = true;
    can_cast_shadows = true;
  }

  MaterialParameters::MaterialParameters(const MaterialParameters& other)
  {
    base_color = other.base_color;
    albedo = other.albedo;
    emissive = other.emissive;
    roughness = other.roughness;
    metallic = other.metallic;
    ambient_oclussion = other.ambient_oclussion;
    material_id = other.material_id;
    texture_ID = other.texture_ID;
    affected_by_light = other.affected_by_light;
    can_cast_shadows = other.can_cast_shadows;
  }

  void MaterialParameters::operator=(const MaterialParameters& other)
  {
    base_color = other.base_color;
    albedo = other.albedo;
    emissive = other.emissive;
    roughness = other.roughness;
    metallic = other.metallic;
    ambient_oclussion = other.ambient_oclussion;
    material_id = other.material_id;
    texture_ID = other.texture_ID;
    affected_by_light = other.affected_by_light;
    can_cast_shadows = other.can_cast_shadows;
  }

  #pragma endregion MaterialParameters

  MaterialComponent::MaterialComponent(int id)
  {
    this->id = id;
    this->type = ComponentType_Render;
  }

  void MaterialComponent::operator=(const MaterialComponent& other)
  {
    this->id = other.id;
    this->type = other.type;
    data = std::make_unique<MaterialParameters>(*other.data);
  }
  //Setters******************************************************
  
  //TEXTURE
  void MaterialComponent::SetTexture(unsigned int texture_ID)
  {
    data->texture_ID = texture_ID;
  }
  //BASE COLOR
  void MaterialComponent::SetBaseColor(float R, float G, float B, float A)
  {
    data->base_color = glm::vec4(R, G, B, A);
  }
  void MaterialComponent::SetBaseColor(glm::vec4 color)
  {
    MaterialComponent::SetBaseColor(color.r, color.g, color.b, color.a);
  }
  void MaterialComponent::SetBaseColor(float color[4])
  {
    MaterialComponent::SetBaseColor(color[0], color[1], color[2], color[3]);
  }
  //ALBEDO
  void MaterialComponent::SetAlbedo(float R, float G, float B)
  {
    data->albedo = glm::vec3(R, G, B);
  }
  void MaterialComponent::SetAlbedo(glm::vec3 emissive)
  {
    MaterialComponent::SetAlbedo(emissive.r, emissive.g, emissive.b);
  }
  void MaterialComponent::SetAlbedo(float emissive[3])
  {
    MaterialComponent::SetAlbedo(emissive[0], emissive[1], emissive[2]);
  }
  //EMISSIVE
  void MaterialComponent::SetEmissive(float emissive)
  {
    data->emissive = emissive;
  }
  //ROUGHNESS
  void MaterialComponent::SetRoughness(float roughness)
  {
    data->roughness = roughness;
  }
  //METALLICNESS
  void MaterialComponent::SetMetallic(float metallic)
  {
    data->metallic = metallic;
  }
  //AMBIENT OCLUSION
  void MaterialComponent::SetAmbientOclussion(float ambientOcclusion)
  {
    data->ambient_oclussion = ambientOcclusion;
  }
  //LIGHT
  void MaterialComponent::SetAffectedByLight(bool affected)
  {
    data->affected_by_light = affected;
  }
  // SHADOWS
  void MaterialComponent::SetCanCastShadows(bool can_cast_shadow)
  {
    data->can_cast_shadows = can_cast_shadow;
  }
  //MATERIAL PARAMETERS
  void MaterialComponent::SetMaterialParameters(std::shared_ptr<class MaterialParameters> material_parameters)
  {
    data = std::make_unique<MaterialParameters>(*material_parameters);
  }
  //*************************************************************


  //Getters******************************************************

  //TEXTURE
  unsigned int MaterialComponent::GetTextureID()
  {
    return data->texture_ID;
  }
  //BASE COLOR
  std::unique_ptr<float[]> MaterialComponent::GetBaseColorfptr() const
  {
    std::unique_ptr<float[]> ptr = std::make_unique<float[]>(4);
    ptr[0] = data->base_color[0];
    ptr[1] = data->base_color[1];
    ptr[2] = data->base_color[2];
    ptr[3] = data->base_color[3];
    return ptr;
  }
  glm::vec4 MaterialComponent::GetBaseColorAsVector4() const
  {
    return data->base_color;
  }
  //ALBEDO
  std::unique_ptr<float[]> MaterialComponent::GetAlbedoAfloatPointer() const
  {
    std::unique_ptr<float[]> ptr = std::make_unique<float[]>(3);
    ptr[0] = data->albedo[0];
    ptr[1] = data->albedo[1];
    ptr[2] = data->albedo[2];
    return ptr;
  }
  glm::vec3 MaterialComponent::GetAlbedoAsVector3() const
  {
    return data->albedo;
  }
  //EMISSIVE
  float MaterialComponent::GetEmissive() const
  {
    return data->emissive;
  }
  //ROUGHNESS
  float MaterialComponent::GetRoughness() const
  {
    return data->roughness;
  }
  //METALLICNESS
  float MaterialComponent::GetMetallic() const
  {
    return data->metallic;
  }
  //AMBIENT OCLUSION
  float MaterialComponent::GetAmbientOclussion() const
  {
    return data->ambient_oclussion;
  }
  //LIGHT
  bool MaterialComponent::GetAffectedByLight() const
  {
    return data->affected_by_light;
  }
  //SHADOWS
  bool MaterialComponent::GetCanCastShadows() const
  {
    return data->can_cast_shadows;
  }
  //MATERIAL PARAMETERS
  std::shared_ptr<MaterialParameters> MaterialComponent::GetMaterialParameters() const
  {
    return std::make_shared<MaterialParameters>(*data);
  }
  //*************************************************************
#pragma endregion MaterialComponent

} // namespace OpenGLEngine