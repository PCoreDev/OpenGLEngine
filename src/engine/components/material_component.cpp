#include "engine/components/material_component.h"
#include <vector>


#include "loguru/loguru.hpp"
#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include "engine/entity.h"
#include "engine/components/shader_component.h"
#include "engine/core.h"

#include <map>

struct Texture {
  bool set = false;
  GLuint id;
  int width, height, n_channels;
  unsigned int type;
  GLint texture_unit;
  unsigned char* data;
  std::map<MaterialComponent::TextureFormat, int> texture_map = {
    {MaterialComponent::TextureFormat::Texture1D, GL_TEXTURE_1D},
    {MaterialComponent::TextureFormat::Texture2D, GL_TEXTURE_2D},
    {MaterialComponent::TextureFormat::Texture3D, GL_TEXTURE_3D},
    {MaterialComponent::TextureFormat::Texture1DArray, GL_TEXTURE_1D_ARRAY},
    {MaterialComponent::TextureFormat::Texture2DArray, GL_TEXTURE_2D_ARRAY},
    {MaterialComponent::TextureFormat::TextureRectangle, GL_TEXTURE_RECTANGLE},
    {MaterialComponent::TextureFormat::TextureCubeMap, GL_TEXTURE_CUBE_MAP},
    {MaterialComponent::TextureFormat::TextureCubeMapArray, GL_TEXTURE_CUBE_MAP_ARRAY},
    {MaterialComponent::TextureFormat::TextureBuffer, GL_TEXTURE_BUFFER},
    {MaterialComponent::TextureFormat::Texture2DMultisample, GL_TEXTURE_2D_MULTISAMPLE},
    {MaterialComponent::TextureFormat::Texture2DMultisampleArray, GL_TEXTURE_2D_MULTISAMPLE_ARRAY}
  };
  void Process();
};

struct MaterialData {
  std::string name;

  Texture diffuse_texture; // map_Kd
  Texture ambient_texture; // map_Ka
  Texture specular_texture; // map_Ks
  Texture emissive_texture; // map_Ke
  Texture alpha_texture; // map_d 
  Texture bump_texture; // map_bump
  Texture normal_texture; // map_Ns
  Texture displacement_texture; // disp
  Texture specular_exponent_texture; // map_Ns
  Texture reflection_texture; // map_refl
  Texture roughness_texture; // map_Pr
  Texture metallic_texture; // map_Pm
  Texture ambient_occlusion_texture; // map_AO
  //Could be redundant
  Texture height_texture; // map_h
  Texture glossiness_texture; // map_G

  glm::vec3 ambient_color;
  glm::vec3 diffuse_color;
  glm::vec3 specular_color;
  float shininess;
  float dissolve;

  static int current_textures;
};

int MaterialData::current_textures = 0;

MaterialComponent::MaterialComponent(std::weak_ptr<class Entity> entity) {
  this->entity = entity;
  this->id = entity.lock()->ID();
  this->type = ComponentType_Material;
  this->data_ = std::make_unique<MaterialData>();
}

MaterialComponent::MaterialComponent(const MaterialComponent& other) {
  this->entity = other.entity;
  this->id = other.id;
  this->type = other.type;
  this->data_ = std::make_unique<MaterialData>(*other.data_);
  //Copy the vector of unique pointers
}

MaterialComponent& MaterialComponent::operator=(const MaterialComponent& other) {
  this->entity = other.entity;
  this->id = other.id;
  this->type = other.type;
  this->data_ = std::make_unique<MaterialData>(*other.data_);
  //Copy the vector of unique pointers
  return *this;
}

MaterialComponent::MaterialComponent(MaterialComponent&& other) noexcept {
  this->entity = std::move(other.entity);
  this->id = other.id;
  this->type = other.type;
  this->data_ = std::move(other.data_);
  //Copy the vector of unique pointers
}

MaterialComponent& MaterialComponent::operator=(MaterialComponent&& other) noexcept {
  if (this != &other) {
    this->entity = std::move(other.entity);
    this->id = other.id;
    this->type = other.type;
    this->data_ = std::move(other.data_);
    //Copy the vector of unique pointers
  }

  return *this;
}

void MaterialComponent::SendToShader()
{
  std::shared_ptr<ShaderComponent> shader = entity.lock()->GetShaderComponent();
  if (shader != nullptr) {
    //Textures

    //diffuse
    if (data_->diffuse_texture.set == true) {
      shader->SetTexture("material.diffuse_texture", data_->diffuse_texture.id);
    }

    //ambient
    if (data_->ambient_texture.set == true) {
      shader->SetTexture("material.ambient_texture", data_->ambient_texture.id);
    }

    //specular
    if (data_->specular_texture.set == true) {
      shader->SetTexture("material.specular_texture", data_->specular_texture.id);
    }

    //emissive
    if (data_->emissive_texture.set == true) {
      shader->SetTexture("material.emissive_texture", data_->emissive_texture.id);
    }

    //alpha
    if (data_->alpha_texture.set == true) {
      shader->SetTexture("material.alpha_texture", data_->alpha_texture.id);
    }

    //bump
    if (data_->bump_texture.set == true) {
      shader->SetTexture("material.bump_texture", data_->bump_texture.id);
    }

    //normal
    if (data_->normal_texture.set == true) {
      shader->SetTexture("material.normal_texture", data_->normal_texture.id);
    }

    //displacement
    if (data_->displacement_texture.set == true) {
      shader->SetTexture("material.displacement_texture", data_->displacement_texture.id);
    }

    //specular_exponent
    if (data_->specular_exponent_texture.set == true) {
      shader->SetTexture("material.specular_exponent_texture", data_->specular_exponent_texture.id);
    }

    //reflection
    if (data_->reflection_texture.set == true) {
      shader->SetTexture("material.reflection_texture", data_->reflection_texture.id);
    }

    //roughness
    if (data_->roughness_texture.set == true) {
      shader->SetTexture("material.roughness_texture", data_->roughness_texture.id);
    }

    //metallic
    if (data_->metallic_texture.set == true) {
      shader->SetTexture("material.metallic_texture", data_->metallic_texture.id);
    }

    //ambient_occlusion
    if (data_->ambient_occlusion_texture.set == true) {
      shader->SetTexture("material.ambient_occlusion_texture", data_->ambient_occlusion_texture.id);
    }

    //height
    if (data_->height_texture.set == true) {
      shader->SetTexture("material.height_texture", data_->height_texture.id);
    }

    //glossiness
    if (data_->glossiness_texture.set == true) {
      shader->SetTexture("material.glossiness_texture", data_->glossiness_texture.id);
    }

    //Colors
    shader->SetVec3("material.ambient_color", data_->ambient_color);
    shader->SetVec3("material.diffuse_color", data_->diffuse_color);
    shader->SetVec3("material.specular_color", data_->specular_color);
    //shader->SetFloat("material.shininess", data_->shininess);
    //shader->SetFloat("material.dissolve", data_->dissolve);

  }
  else {
    //Textures

//diffuse
    if (data_->diffuse_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.diffuse_texture", data_->diffuse_texture.id);
    }

    //ambient
    if (data_->ambient_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.ambient_texture", data_->ambient_texture.id);
    }

    //specular
    if (data_->specular_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.specular_texture", data_->specular_texture.id);
    }

    //emissive
    if (data_->emissive_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.emissive_texture", data_->emissive_texture.id);
    }

    //alpha
    if (data_->alpha_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.alpha_texture", data_->alpha_texture.id);
    }

    //bump
    if (data_->bump_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.bump_texture", data_->bump_texture.id);
    }

    //normal
    if (data_->normal_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.normal_texture", data_->normal_texture.id);
    }

    //displacement
    if (data_->displacement_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.displacement_texture", data_->displacement_texture.id);
    }

    //specular_exponent
    if (data_->specular_exponent_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.specular_exponent_texture", data_->specular_exponent_texture.id);
    }

    //reflection
    if (data_->reflection_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.reflection_texture", data_->reflection_texture.id);
    }

    //roughness
    if (data_->roughness_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.roughness_texture", data_->roughness_texture.id);
    }

    //metallic
    if (data_->metallic_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.metallic_texture", data_->metallic_texture.id);
    }

    //ambient_occlusion
    if (data_->ambient_occlusion_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.ambient_occlusion_texture", data_->ambient_occlusion_texture.id);
    }

    //height
    if (data_->height_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.height_texture", data_->height_texture.id);
    }

    //glossiness
    if (data_->glossiness_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.glossiness_texture", data_->glossiness_texture.id);
    }

    //Colors
    OpenGLEngine::Engine::Core::shader_->SetVec3("material.ambient_color", data_->ambient_color);
    OpenGLEngine::Engine::Core::shader_->SetVec3("material.diffuse_color", data_->diffuse_color);
    OpenGLEngine::Engine::Core::shader_->SetVec3("material.specular_color", data_->specular_color);
    //OpenGLEngine::Engine::Core::shader_->SetFloat("material.shininess", data_->shininess);
    //OpenGLEngine::Engine::Core::shader_->SetFloat("material.dissolve", data_->dissolve);
  }

  //BindTextures();
}

//Setters

void MaterialComponent::SetAmbient(const float ambient_x, float ambient_y, float ambient_z){
  data_->ambient_color = glm::vec3(ambient_x, ambient_y, ambient_z);
}

void MaterialComponent::SetAmbient(const float ambient[3]) { SetAmbient(ambient[1], ambient[1], ambient[2]); }

void MaterialComponent::SetAmbient(const glm::vec3& ambient) { SetAmbient(ambient.x, ambient.y, ambient.z); }

void MaterialComponent::SetDiffuse(const float diffuse_x, float diffuse_y, float diffuse_z) {
  data_->diffuse_color = glm::vec3(diffuse_x, diffuse_y, diffuse_z);
}

void MaterialComponent::SetDiffuse(const float diffuse[3]) { SetDiffuse(diffuse[1], diffuse[1], diffuse[2]); }

void MaterialComponent::SetDiffuse(const glm::vec3& diffuse) { SetDiffuse(diffuse.x, diffuse.y, diffuse.z); }

void MaterialComponent::SetSpecular(const float specular_x, float specular_y, float specular_z) {
  data_->specular_color = glm::vec3(specular_x, specular_y, specular_z);
}

void MaterialComponent::SetSpecular(const float specular[3]) { SetSpecular(specular[1], specular[1], specular[2]); }

void MaterialComponent::SetSpecular(const glm::vec3& specular) { SetSpecular(specular.x, specular.y, specular.z); }

void MaterialComponent::SetShininess(float shininess) {
  data_->shininess = shininess;
}

//Getters

//glm::vec3 MaterialComponent::GetAmbient() const {
//  return data_->ambient;
//}
//
//glm::vec3 MaterialComponent::GetDiffuse() const {
//  return data_->diffuse;
//}
//
//glm::vec3 MaterialComponent::GetSpecular() const {
//  return data_->specular;
//}
//
//float MaterialComponent::GetShininess() const {
//  return data_->shininess;
//}
//
//unsigned int MaterialComponent::GetBaseColorTexture() {
//  return data_->base_color_texture.id;
//}
//
//unsigned int MaterialComponent::GetMetallicTexture() {
//  return data_->metallic_texture.id;
//}
//
//unsigned int MaterialComponent::GetSpecularColorTexture() {
//  return data_->specular_texture.id;
//}
//
//unsigned int MaterialComponent::GetRoughnessTexture() {
//  return data_->roughness_texture.id;
//}
//
//unsigned int MaterialComponent::GetDiffuseTexture(){
//  return data_->diffuse_texture.id;
//}
//
//unsigned int MaterialComponent::GetEmissiveTexture() {
//  return data_->emissive_texture.id;
//}
//
//unsigned int MaterialComponent::GetNormalTexture() {
//  return data_->normal_texture.id;
//}
//
//unsigned int MaterialComponent::GetAmbientOcclusionTexture() {
//  return data_->ambient_oclusion_texture.id;
//}

void MaterialComponent::LoadTexture(const std::string& path, MaterialComponent::TextureFormat type, MaterialComponent::TextureTarget target){
  Texture new_texture;

  auto it = new_texture.texture_map.find(type);
  if (it != new_texture.texture_map.end()) {
    new_texture.type = it->second;
  }
  else {
    LOG_F(ERROR, "Texture type not found");
  }
  new_texture.texture_unit = MaterialData::current_textures + 1;
  new_texture.data = stbi_load(path.c_str(), &new_texture.width, &new_texture.height, &new_texture.n_channels, 0);

  if (new_texture.data != nullptr) {
    new_texture.set = true;
    new_texture.Process();
    switch (target) {

    case MaterialComponent::TextureTarget::Diffuse:
      data_->diffuse_texture = new_texture;
      break;

    case MaterialComponent::TextureTarget::Ambient:
      data_->ambient_texture = new_texture;
      break;

    case MaterialComponent::TextureTarget::Specular:
      data_->specular_texture = new_texture;
      break;

    case MaterialComponent::TextureTarget::Emissive:
      data_->emissive_texture = new_texture;
      break;

    case MaterialComponent::TextureTarget::Alpha:
      data_->alpha_texture = new_texture;
      break;

    case MaterialComponent::TextureTarget::Bump:
      data_->bump_texture = new_texture;
      break;

    case MaterialComponent::TextureTarget::Normal:
      data_->normal_texture = new_texture;
      break;

    case MaterialComponent::TextureTarget::Displacement:
      data_->displacement_texture = new_texture;
      break;

    case MaterialComponent::TextureTarget::SpecularExponent:
      data_->specular_exponent_texture = new_texture;
      break;

    case MaterialComponent::TextureTarget::Reflection:
      data_->reflection_texture = new_texture;
      break;

    case MaterialComponent::TextureTarget::Roughness:
      data_->roughness_texture = new_texture;
      break;

    case MaterialComponent::TextureTarget::Metallic:
      data_->metallic_texture = new_texture;
      break;

    case MaterialComponent::TextureTarget::AmbientOcclusion:
      data_->ambient_occlusion_texture = new_texture;
      break;

    case MaterialComponent::TextureTarget::Height:
      data_->height_texture = new_texture;
      break;

    case MaterialComponent::TextureTarget::Glossiness:
      data_->glossiness_texture = new_texture;
      break;

    default:
      break;
    }

    MaterialData::current_textures++;

    //LOG_F(INFO, "Texture loaded correctly: %s", path.c_str());
  }
  else {
    LOG_F(ERROR, "Failed to load texture: %s", path.c_str());
  }

}

void MaterialComponent::BindTextures() {
    //Diffuse
    if (data_->diffuse_texture.set == true) {
      glActiveTexture(GL_TEXTURE0 + data_->diffuse_texture.texture_unit);
      glBindTexture(data_->diffuse_texture.type, data_->diffuse_texture.id);
    }

    //Ambient
    if (data_->ambient_texture.set == true) {
      glActiveTexture(GL_TEXTURE0 + data_->ambient_texture.texture_unit);
      glBindTexture(data_->ambient_texture.type, data_->ambient_texture.id);
    }

    //Specular
    if (data_->specular_texture.set == true) {
      glActiveTexture(GL_TEXTURE0 + data_->specular_texture.texture_unit);
      glBindTexture(data_->specular_texture.type, data_->specular_texture.id);
    }

    //Emissive
    if (data_->emissive_texture.set == true) {
      glActiveTexture(GL_TEXTURE0 + data_->emissive_texture.texture_unit);
      glBindTexture(data_->emissive_texture.type, data_->emissive_texture.id);
    }

    //Alpha
    if (data_->alpha_texture.set == true) {
      glActiveTexture(GL_TEXTURE0 + data_->alpha_texture.texture_unit);
      glBindTexture(data_->alpha_texture.type, data_->alpha_texture.id);
    }

    //Bump
    if (data_->bump_texture.set == true) {
      glActiveTexture(GL_TEXTURE0 + data_->bump_texture.texture_unit);
      glBindTexture(data_->bump_texture.type, data_->bump_texture.id);
    }

    //Normal
    if (data_->normal_texture.set == true) {
      glActiveTexture(GL_TEXTURE0 + data_->normal_texture.texture_unit);
      glBindTexture(data_->normal_texture.type, data_->normal_texture.id);
    }

    //Displacement
    if (data_->displacement_texture.set == true) {
      glActiveTexture(GL_TEXTURE0 + data_->displacement_texture.texture_unit);
      glBindTexture(data_->displacement_texture.type, data_->displacement_texture.id);
    }

    //Specular Exponent
    if (data_->specular_exponent_texture.set == true) {
      glActiveTexture(GL_TEXTURE0 + data_->specular_exponent_texture.texture_unit);
      glBindTexture(data_->specular_exponent_texture.type, data_->specular_exponent_texture.id);
    }

    //Reflection
    if (data_->reflection_texture.set == true) {
      glActiveTexture(GL_TEXTURE0 + data_->reflection_texture.texture_unit);
      glBindTexture(data_->reflection_texture.type, data_->reflection_texture.id);
    }

    //Roughness
    if (data_->roughness_texture.set == true) {
      glActiveTexture(GL_TEXTURE0 + data_->roughness_texture.texture_unit);
      glBindTexture(data_->roughness_texture.type, data_->roughness_texture.id);
    }

    //Metallic
    if (data_->metallic_texture.set == true) {
      glActiveTexture(GL_TEXTURE0 + data_->metallic_texture.texture_unit);
      glBindTexture(data_->metallic_texture.type, data_->metallic_texture.id);
    }

    //Ambient Occlusion
    if (data_->ambient_occlusion_texture.set == true) {
      glActiveTexture(GL_TEXTURE0 + data_->ambient_occlusion_texture.texture_unit);
      glBindTexture(data_->ambient_occlusion_texture.type, data_->ambient_occlusion_texture.id);
    }

    //Height
    if (data_->height_texture.set == true) {
      glActiveTexture(GL_TEXTURE0 + data_->height_texture.texture_unit);
      glBindTexture(data_->height_texture.type, data_->height_texture.id);
    }

    //Glossiness
    if (data_->glossiness_texture.set == true) {
      glActiveTexture(GL_TEXTURE0 + data_->glossiness_texture.texture_unit);
      glBindTexture(data_->glossiness_texture.type, data_->glossiness_texture.id);
    }
}


void Texture::Process()
{
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  if (n_channels == 2) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, data);
  }
  else if (n_channels == 3) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  }
  else if (n_channels == 4) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  }
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);



  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


  glActiveTexture(0);
  glBindTexture(GL_TEXTURE_2D, 0);

  stbi_image_free(data);
}
