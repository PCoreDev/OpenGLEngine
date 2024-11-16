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
  GLuint id;
  int width, height, n_channels;
  unsigned int type;
  GLint texture_unit;
  unsigned char* data;
  std::map<MaterialComponent::TextureType, int> texture_map = {
    {MaterialComponent::TextureType::Texture1D, GL_TEXTURE_1D},
    {MaterialComponent::TextureType::Texture2D, GL_TEXTURE_2D},
    {MaterialComponent::TextureType::Texture3D, GL_TEXTURE_3D},
    {MaterialComponent::TextureType::Texture1DArray, GL_TEXTURE_1D_ARRAY},
    {MaterialComponent::TextureType::Texture2DArray, GL_TEXTURE_2D_ARRAY},
    {MaterialComponent::TextureType::TextureRectangle, GL_TEXTURE_RECTANGLE},
    {MaterialComponent::TextureType::TextureCubeMap, GL_TEXTURE_CUBE_MAP},
    {MaterialComponent::TextureType::TextureCubeMapArray, GL_TEXTURE_CUBE_MAP_ARRAY},
    {MaterialComponent::TextureType::TextureBuffer, GL_TEXTURE_BUFFER},
    {MaterialComponent::TextureType::Texture2DMultisample, GL_TEXTURE_2D_MULTISAMPLE},
    {MaterialComponent::TextureType::Texture2DMultisampleArray, GL_TEXTURE_2D_MULTISAMPLE_ARRAY}
  };
  void Process();
};

struct MaterialData {
  std::vector<std::shared_ptr<Texture>> textures;
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  float shininess;
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
    //shader->SetFloat("material.shininess", data_->shininess);
    if (data_->textures.size() > 0 && data_->textures[0] != nullptr)
    shader->SetTexture("material.tex_diffuse", GetTextureID(0));
    if (data_->textures.size() > 1 && data_->textures[1] != nullptr)
      shader->SetTexture("material.tex_specular", GetTextureID(1));
  }
  else {
    OpenGLEngine::Engine::Core::shader_->SetVec3("material.ambient", data_->ambient);
    OpenGLEngine::Engine::Core::shader_->SetVec3("material.diffuse", data_->diffuse);
    OpenGLEngine::Engine::Core::shader_->SetVec3("material.specular", data_->specular);
    //OpenGLEngine::Engine::Core::shader_->SetFloat("material.shininess", data_->shininess);
    if (data_->textures.size() > 0 && data_->textures[0] != nullptr)
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.tex_diffuse", GetTextureID(0));
    if (data_->textures.size() > 1 && data_->textures[1] != nullptr)
      OpenGLEngine::Engine::Core::shader_->SetTexture("material.tex_specular", GetTextureID(1));
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

//Texture

unsigned int MaterialComponent::GetTextureID(int n)
{
  return data_->textures[n]->id;
}

void MaterialComponent::LoadTexture(const std::string& path, TextureType type) {
  Texture texture;
  texture.texture_unit = data_->textures.size() + 1;

  auto it = texture.texture_map.find(type);
  if (it != texture.texture_map.end()) {
    texture.type = it->second;
  }
  else {
    LOG_F(ERROR, "Texture type not found");
  }

  texture.data = stbi_load(path.c_str(), &texture.width, &texture.height, &texture.n_channels, 0);

  if (texture.data != nullptr) {
    texture.Process();
    data_->textures.push_back(std::make_shared<Texture>(texture));
    
    LOG_F(INFO, "Texture loaded correctly: %s", path.c_str());
  }
  else {
    LOG_F(ERROR, "Failed to load texture: %s", path.c_str());
  }
}

int MaterialComponent::GetNumberOfTextures() {
  return data_->textures.size();
}

void MaterialComponent::BindTextures() {
  for each (std::shared_ptr<Texture> tex in data_->textures){
    glActiveTexture(GL_TEXTURE0 + tex->texture_unit);
    glBindTexture(GL_TEXTURE_2D, tex->id);
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
