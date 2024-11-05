#include "engine/components/material_component.h"
#include <vector>


#include "loguru/loguru.hpp"
#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include "engine/entity.h"

struct Texture {
  GLuint id;
  int width, height, n_channels;
  unsigned char* data;
  void Process();
};

struct MaterialData {
  Texture texture;
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  float shininess;

  void SetAmbient(const float ambient_x, float ambient_y, float ambient_z);
  void SetAmbient(const float ambient[3]);
  void SetAmbient(const glm::vec3& ambient);

  void SetDiffuse(const float diffuse_x, float diffuse_y, float diffuse_z);
  void SetDiffuse(const float diffuse[3]);
  void SetDiffuse(const glm::vec3& diffuse);

  void SetSpecular(const float specular_x, float specular_y, float specular_z);
  void SetSpecular(const float specular[3]);
  void SetSpecular(const glm::vec3& specular);

  void SetShininess(float shininess);

  void LoadTexture(const std::string& path);
};

MaterialComponent::MaterialComponent(std::weak_ptr<class Entity> entity) {
  this->entity = entity;
  this->id = entity.lock()->ID();
  this->type = ComponentType_Material;
}

MaterialComponent::MaterialComponent(const MaterialComponent& other) {
  this->entity = other.entity;
  this->id = other.id;
  this->type = other.type;
  //Copy the vector of unique pointers
}

MaterialComponent& MaterialComponent::operator=(const MaterialComponent& other) {
  this->entity = other.entity;
  this->id = other.id;
  this->type = other.type;
  //Copy the vector of unique pointers
  return *this;
}

MaterialComponent::MaterialComponent(MaterialComponent&& other) noexcept {
  this->entity = std::move(other.entity);
  this->id = other.id;
  this->type = other.type;
  //Copy the vector of unique pointers
}

MaterialComponent& MaterialComponent::operator=(MaterialComponent&& other) noexcept
{
  if (this != &other) {
    this->entity = std::move(other.entity);
    this->id = other.id;
    this->type = other.type;
    //Copy the vector of unique pointers
  }

  return *this;
}

int MaterialComponent::LoadBPM(const std::string& path) {
  Texture texture;
  unsigned char header[54];
  unsigned int data_pos;

  FILE* file = fopen(path.c_str(), "rb");
  if (!file) {
    LOG_F(ERROR, "Image could not be opened");
    return -1;
  }

  if (fread(header, 1, 54, file) != 54) {
    LOG_F(ERROR, "Not a correct BMP file");
    return -1;
  }

  if (header[0] != 'B' || header[1] != 'M') {
    LOG_F(ERROR, "Not a correct BMP file");
    return -1;
  }

  data_pos = *(int*)&(header[0x0A]);
  texture.n_channels = *(int*)&(header[0x22]);
  texture.width = *(int*)&(header[0x12]);
  texture.height = *(int*)&(header[0x16]);

  if (texture.n_channels == 0) {
    texture.n_channels = texture.width * texture.height * 3;
  }

  if (data_pos == 0) {
    data_pos = 54; //BMP Header
  }

  fread(texture.data, 1, texture.n_channels, file);
  fclose(file);
  data_.push_back(std::make_unique<MaterialData>());
  data_.back()->texture = texture;


  if (data_.back()->texture.data) {
    LOG_F(INFO, "Texture loaded correctly");
  }
  else {
    LOG_F(ERROR, "Failed to load texture");
    return -1;
  }
}

int MaterialComponent::LoadTexture(int n, const std::string& path)
{
  if (n >= data_.size()) {
    LOG_F(ERROR, "Texture not found");
    return -1;
  }
  else {
    Texture texture;
    texture.data = stbi_load(path.c_str(), &texture.width, &texture.height, &texture.n_channels, 0);
    data_[n]->texture = texture;
    if (data_[n]->texture.data) {
      LOG_F(INFO, "Texture loaded correctly");
      data_[n]->texture.Process();
    }
    else {
      LOG_F(ERROR, "Failed to load texture");
      return -1;
    }
  }
}

void MaterialComponent::Process(MaterialData* data){
}

size_t MaterialComponent::GetNumbersOfTextures()
{
  return data_.size();
}

unsigned int MaterialComponent::GetTexture(int n)
{
  if (n < data_.size())
    return data_[n]->texture.id;
  else
    LOG_F(ERROR, "Texture not found");
  return 0;
}

void MaterialComponent::SetAmbient(int n, const float ambient_x, float ambient_y, float ambient_z){
  if (n < data_.size()){
    data_[n]->SetAmbient(ambient_x, ambient_y, ambient_z);
  }
  else {
    LOG_F(ERROR, "Texture not found");
  }
}

void MaterialComponent::SetAmbient(int n, const float ambient[3])
{
  if (n < data_.size()) {
    data_[n]->SetAmbient(ambient);
  }
  else {
    LOG_F(ERROR, "Texture not found");
  }
}

void MaterialComponent::SetAmbient(int n, const glm::vec3& ambient)
{
  if (n < data_.size()) {
    data_[n]->SetAmbient(ambient);
  }
  else {
    LOG_F(ERROR, "Texture not found");
  }
}

void MaterialComponent::SetDiffuse(int n, const float diffuse_x, float diffuse_y, float diffuse_z){
  if (n < data_.size()) {
    data_[n]->SetDiffuse(diffuse_x, diffuse_y, diffuse_z);
  }
  else {
    LOG_F(ERROR, "Texture not found");
  }
}

void MaterialComponent::SetDiffuse(int n, const float diffuse[3]) {
  if (n < data_.size()) {
    data_[n]->SetDiffuse(diffuse);
  }
  else {
    LOG_F(ERROR, "Texture not found");
  }
}

void MaterialComponent::SetDiffuse(int n, const glm::vec3& diffuse){
  if (n < data_.size()) {
    data_[n]->SetDiffuse(diffuse);
  }
  else {
    LOG_F(ERROR, "Texture not found");
  }

}

void MaterialComponent::SetSpecular(int n, const float specular_x, float specular_y, float specular_z) {
  if (n < data_.size()) {
    data_[n]->SetSpecular(specular_x, specular_y, specular_z);
  }
  else {
    LOG_F(ERROR, "Texture not found");
  }
}

void MaterialComponent::SetSpecular(int n, const float specular[3]) {
  if (n < data_.size()) {
    data_[n]->SetSpecular(specular);
  }
  else {
    LOG_F(ERROR, "Texture not found");
  }
}

void MaterialComponent::SetSpecular(int n, const glm::vec3& specular) {
  if (n < data_.size()) {
    data_[n]->SetSpecular(specular);
  }
  else {
    LOG_F(ERROR, "Texture not found");
  }
}

void MaterialComponent::SetShininess(int n, float shininess) {
  if (n < data_.size()) {
    data_[n]->SetShininess(shininess);
  }
  else {
    LOG_F(ERROR, "Texture not found");
  }
}

void MaterialComponent::AddNewMaterial(std::string path, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shinisses) {
  data_.push_back(std::make_unique<MaterialData>());
  data_.back()->LoadTexture(path);
  data_.back()->SetAmbient(ambient);
  data_.back()->SetDiffuse(diffuse);
  data_.back()->SetSpecular(specular);
  data_.back()->SetShininess(shinisses);
}

void MaterialData::SetAmbient(const float ambient_x, float ambient_y, float ambient_z) {
  ambient = glm::vec3(ambient_x, ambient_y, ambient_z);
}

void MaterialData::SetAmbient(const float ambient[3]) {
  SetAmbient(ambient[1], ambient[1], ambient[2]);
}

void MaterialData::SetAmbient(const glm::vec3& ambient) {
  this->ambient = ambient;
}

void MaterialData::SetDiffuse(const float diffuse_x, float diffuse_y, float diffuse_z) {
  diffuse = glm::vec3(diffuse_x, diffuse_y, diffuse_z);
}

void MaterialData::SetDiffuse(const float diffuse[3]){
  SetDiffuse(diffuse[1], diffuse[1], diffuse[2]);
}

void MaterialData::SetDiffuse(const glm::vec3& diffuse) {
  this->diffuse = diffuse;
}

void MaterialData::SetSpecular(const float specular_x, float specular_y, float specular_z){
  specular = glm::vec3(specular_x, specular_y, specular_z);
}

void MaterialData::SetSpecular(const float specular[3]){
  SetSpecular(specular[1], specular[1], specular[2]);
}

void MaterialData::SetSpecular(const glm::vec3& specular) {
  this->specular = specular;
}

void MaterialData ::SetShininess(float shininess) {
  this->shininess = shininess;
}

void MaterialData::LoadTexture(const std::string& path){
  Texture texture;
  texture.data = stbi_load(path.c_str(), &texture.width, &texture.height, &texture.n_channels, 0);
  this->texture = texture;
  if (this->texture.data) {
    LOG_F(INFO, "Texture loaded correctly");
    //this->texture.Process();
  }
  else {
    LOG_F(ERROR, "Failed to load texture");
  }
}

void Texture::Process()
{
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
 
 
 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
 
 // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, tex->m_texture.border_color);
 
  glGenerateMipmap(GL_TEXTURE_2D);
 
  stbi_image_free(data);
}
