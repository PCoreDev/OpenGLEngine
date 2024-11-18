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
  //std::vector<std::shared_ptr<Texture>> textures;
  Texture base_color_texture;
  Texture metallic_texture;
  Texture specular_texture;
  Texture roughness_texture;
  Texture emissive_texture;
  Texture diffuse_texture;
  Texture normal_texture;
  Texture ambient_oclusion_texture;
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  float shininess;
  int current_textures;
};

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
    shader->SetVec3("material.ambient", data_->ambient);
    shader->SetVec3("material.diffuse", data_->diffuse);
    shader->SetVec3("material.specular", data_->specular);

    if(data_->base_color_texture.set == true) {
      shader->SetTexture("material.base_color_texture", data_->base_color_texture.id);
    }

    if(data_->metallic_texture.set == true){
      shader->SetTexture("material.metallic_texture", data_->metallic_texture.id);
    }

    if(data_->specular_texture.set == true){
      shader->SetTexture("material.specular_texture", data_->specular_texture.id);
    }

    if(data_->roughness_texture.set == true){
      shader->SetTexture("material.roughness_texture", data_->roughness_texture.id);
    }

    if(data_->emissive_texture.set == true){
      shader->SetTexture("material.emissive_texture", data_->emissive_texture.id);
    }

    if(data_->diffuse_texture.set == true){
      shader->SetTexture("material.diffuse_texture", data_->diffuse_texture.id);
    }

    if(data_->normal_texture.set == true){
      shader->SetTexture("material.normal_texture", data_->normal_texture.id);
    }

    if(data_->ambient_oclusion_texture.set == true){
      shader->SetTexture("material.ambient_oclusion_texture", data_->ambient_oclusion_texture.id);
    }
  }
  else {
    OpenGLEngine::Engine::Core::shader_->SetVec3("material.ambient", data_->ambient);
    OpenGLEngine::Engine::Core::shader_->SetVec3("material.diffuse", data_->diffuse);
    OpenGLEngine::Engine::Core::shader_->SetVec3("material.specular", data_->specular);
    if (data_->base_color_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.base_color_texture", data_->base_color_texture.id);
    }

    if (data_->metallic_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.metallic_texture", data_->metallic_texture.id);
    }

    if (data_->specular_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.specular_texture", data_->specular_texture.id);
    }

    if (data_->roughness_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.roughness_texture", data_->roughness_texture.id);
    }

    if (data_->emissive_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.emissive_texture", data_->emissive_texture.id);
    }

    if (data_->diffuse_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.diffuse_texture", data_->diffuse_texture.id);
    }

    if (data_->normal_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.normal_texture", data_->normal_texture.id);
    }

    if (data_->ambient_oclusion_texture.set == true) {
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.ambient_oclusion_texture", data_->ambient_oclusion_texture.id);
    }
  }

  BindTextures();
}

//Setters

void MaterialComponent::SetAmbient(const float ambient_x, float ambient_y, float ambient_z){
  data_->ambient = glm::vec3(ambient_x, ambient_y, ambient_z);
}

void MaterialComponent::SetAmbient(const float ambient[3]) { SetAmbient(ambient[1], ambient[1], ambient[2]); }

void MaterialComponent::SetAmbient(const glm::vec3& ambient) { SetAmbient(ambient.x, ambient.y, ambient.z); }

void MaterialComponent::SetDiffuse(const float diffuse_x, float diffuse_y, float diffuse_z) {
  data_->diffuse = glm::vec3(diffuse_x, diffuse_y, diffuse_z);
}

void MaterialComponent::SetDiffuse(const float diffuse[3]) { SetDiffuse(diffuse[1], diffuse[1], diffuse[2]); }

void MaterialComponent::SetDiffuse(const glm::vec3& diffuse) { SetDiffuse(diffuse.x, diffuse.y, diffuse.z); }

void MaterialComponent::SetSpecular(const float specular_x, float specular_y, float specular_z) {
  data_->specular = glm::vec3(specular_x, specular_y, specular_z);
}

void MaterialComponent::SetSpecular(const float specular[3]) { SetSpecular(specular[1], specular[1], specular[2]); }

void MaterialComponent::SetSpecular(const glm::vec3& specular) { SetSpecular(specular.x, specular.y, specular.z); }

void MaterialComponent::SetShininess(float shininess) {
  data_->shininess = shininess;
}

//Getters

glm::vec3 MaterialComponent::GetAmbient() const {
  return data_->ambient;
}

glm::vec3 MaterialComponent::GetDiffuse() const {
  return data_->diffuse;
}

glm::vec3 MaterialComponent::GetSpecular() const {
  return data_->specular;
}

float MaterialComponent::GetShininess() const {
  return data_->shininess;
}

unsigned int MaterialComponent::GetBaseColorTexture() {
  return data_->base_color_texture.id;
}

unsigned int MaterialComponent::GetMetallicTexture() {
  return data_->metallic_texture.id;
}

unsigned int MaterialComponent::GetSpecularColorTexture() {
  return data_->specular_texture.id;
}

unsigned int MaterialComponent::GetRoughnessTexture() {
  return data_->roughness_texture.id;
}

unsigned int MaterialComponent::GetDiffuseTexture(){
  return data_->diffuse_texture.id;
}

unsigned int MaterialComponent::GetEmissiveTexture() {
  return data_->emissive_texture.id;
}

unsigned int MaterialComponent::GetNormalTexture() {
  return data_->normal_texture.id;
}

unsigned int MaterialComponent::GetAmbientOcclusionTexture() {
  return data_->ambient_oclusion_texture.id;
}

void MaterialComponent::LoadTexture(const std::string& path, MaterialComponent::TextureFormat type, MaterialComponent::TextureTarget target){
  Texture new_texture;

  auto it = new_texture.texture_map.find(type);
  if (it != new_texture.texture_map.end()) {
    new_texture.type = it->second;
  }
  else {
    LOG_F(ERROR, "Texture type not found");
  }
  new_texture.texture_unit = data_->current_textures + 1;
  new_texture.data = stbi_load(path.c_str(), &new_texture.width, &new_texture.height, &new_texture.n_channels, 0);

  if (new_texture.data != nullptr) {
    new_texture.set = true;
    new_texture.Process();
    switch (target) {

    case TextureTarget::BaseColor:
      data_->base_color_texture = new_texture;
      break;

    case TextureTarget::Metallic:
      data_->metallic_texture = new_texture;
      break;

    case TextureTarget::Specular:
      data_->specular_texture = new_texture;
      break;

    case TextureTarget::Diffuse:
      data_->diffuse_texture = new_texture;
      break;

    case TextureTarget::Roughness:
      data_->roughness_texture = new_texture;
      break;

    case TextureTarget::Emissive:
      data_->emissive_texture = new_texture;
      break;

    case TextureTarget::Normal:
      data_->normal_texture = new_texture;
      break;

    case TextureTarget::AmbientOcclusion:
      data_->ambient_oclusion_texture = new_texture;
      break;

    default:
      break;
    }

    data_->current_textures++;

    LOG_F(INFO, "Texture loaded correctly: %s", path.c_str());
  }
  else {
    LOG_F(ERROR, "Failed to load texture: %s", path.c_str());
  }

}

void MaterialComponent::BindTextures() {
  //BaseColor
  if (data_->base_color_texture.set == true) {
    glActiveTexture(GL_TEXTURE0 + data_->base_color_texture.texture_unit);
    glBindTexture(GL_TEXTURE_2D, data_->base_color_texture.id);
  }

  //Metallic
  if (data_->metallic_texture.set == true) {
    glActiveTexture(GL_TEXTURE0 + data_->metallic_texture.texture_unit);
    glBindTexture(GL_TEXTURE_2D, data_->metallic_texture.id);
  }

  //Specular
  if (data_->specular_texture.set == true) {
    glActiveTexture(GL_TEXTURE0 + data_->specular_texture.texture_unit);
    glBindTexture(GL_TEXTURE_2D, data_->specular_texture.id);
  }

  //Roughness
  if (data_->roughness_texture.set == true) {
    glActiveTexture(GL_TEXTURE0 + data_->roughness_texture.texture_unit);
    glBindTexture(GL_TEXTURE_2D, data_->roughness_texture.id);
  }

  //Emissive
  if (data_->emissive_texture.set == true) {
    glActiveTexture(GL_TEXTURE0 + data_->emissive_texture.texture_unit);
    glBindTexture(GL_TEXTURE_2D, data_->emissive_texture.id);
  }

  //Diffuse
  if (data_->diffuse_texture.set == true) {
    glActiveTexture(GL_TEXTURE0 + data_->diffuse_texture.texture_unit);
    glBindTexture(GL_TEXTURE_2D, data_->diffuse_texture.id);
  }

  //Normal
  if (data_->normal_texture.set == true) {
    glActiveTexture(GL_TEXTURE0 + data_->normal_texture.texture_unit);
    glBindTexture(GL_TEXTURE_2D, data_->normal_texture.id);
  }

  //AmbientOcclusion
  if (data_->ambient_oclusion_texture.set == true) {
    glActiveTexture(GL_TEXTURE0 + data_->ambient_oclusion_texture.texture_unit);
    glBindTexture(GL_TEXTURE_2D, data_->ambient_oclusion_texture.id);
  }
}

//void MaterialComponent::AddTexture(const std::string& path) {
//  if (!path.empty()) {
//
//    int tex_width, tex_height, tex_n_channels;
//    unsigned char* new_tex_data = stbi_load(path.c_str(), &tex_width, &tex_height, &tex_n_channels, 0);
//
//    if (new_tex_data) {
//      LOG_F(INFO, "Texture loaded correctly: %s", path.c_str());
//
//      //Concat the new texture to the old one
//      unsigned char* new_data = new unsigned char[data_->width * data_->height * data_->n_channels + tex_width * tex_height * tex_n_channels];
//      memcpy(new_data, data_->tex_data, data_->width * data_->height * data_->n_channels);
//      memcpy(new_data + data_->width * data_->height * data_->n_channels, new_tex_data, tex_width * tex_height * tex_n_channels);
//
//      if (data_->tex_data) stbi_image_free(data_->tex_data);
//
//      data_->tex_data = new_data;
//
//    } else { LOG_F(ERROR, "Failed to load texture: %s", path.c_str()); }
//  } else { LOG_F(WARNING, "Path is empty"); }
//}

//void MaterialData::SetAmbient(const float ambient_x, float ambient_y, float ambient_z) {
//  ambient = glm::vec3(ambient_x, ambient_y, ambient_z);
//}
//
//void MaterialData::SetAmbient(const float ambient[3]) {
//  SetAmbient(ambient[1], ambient[1], ambient[2]);
//}
//
//void MaterialData::SetAmbient(const glm::vec3& ambient) {
//  this->ambient = ambient;
//}
//
//void MaterialData::SetDiffuse(const float diffuse_x, float diffuse_y, float diffuse_z) {
//  diffuse = glm::vec3(diffuse_x, diffuse_y, diffuse_z);
//}
//
//void MaterialData::SetDiffuse(const float diffuse[3]){
//  SetDiffuse(diffuse[1], diffuse[1], diffuse[2]);
//}
//
//void MaterialData::SetDiffuse(const glm::vec3& diffuse) {
//  this->diffuse = diffuse;
//}
//
//void MaterialData::SetSpecular(const float specular_x, float specular_y, float specular_z){
//  specular = glm::vec3(specular_x, specular_y, specular_z);
//}
//
//void MaterialData::SetSpecular(const float specular[3]){
//  SetSpecular(specular[1], specular[1], specular[2]);
//}
//
//void MaterialData::SetSpecular(const glm::vec3& specular) {
//  this->specular = specular;
//}
//
//void MaterialData ::SetShininess(float shininess) {
//  this->shininess = shininess;
//}
//
//void MaterialData::LoadTexture(const std::string& path){
//  Texture texture;
//  texture.data = stbi_load(path.c_str(), &texture.width, &texture.height, &texture.n_channels, 0);
//  this->texture = texture;
//  if (this->texture.data) {
//    LOG_F(INFO, "Texture loaded correctly");
//    this->texture.Process();
//  }
//  else {
//    LOG_F(ERROR, "Failed to load texture");
//  }
//}

//void Texture::Process() {
//  glGenTextures(1, &tex_id);
//  glBindTexture(GL_TEXTURE_2D, tex_id);
//
//  if (n_channels == 2) {
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, tex_data);
//  }
//  else if (n_channels == 3) {
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_data);
//  }
//  else if (n_channels == 4) {
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data);
//  }
//  glGenerateMipmap(GL_TEXTURE_2D);
//
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 
// 
// 
//  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 
// 
//  glActiveTexture(0);
//  glBindTexture(GL_TEXTURE_2D, 0);
//
//  stbi_image_free(tex_data);
//}

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
