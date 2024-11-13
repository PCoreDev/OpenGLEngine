#include "engine/components/material_component.h"
#include <vector>


#include "loguru/loguru.hpp"
#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include "engine/entity.h"

struct Texture {
  GLuint tex_id;
  int width, height, n_channels;
  unsigned char* tex_data;
  void Process();
};

struct MaterialData {
  //GLuint tex_id;
  //int width, height, n_channels;
  //unsigned char* tex_data;
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

unsigned int MaterialComponent::GetTexture(int n) {
  return data_->textures[n]->tex_id;
}

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

void MaterialComponent::ProcessAllMaterials(){

}

void MaterialComponent::LoadTexture(const std::string& path) {
  Texture texture;
  texture.tex_data = stbi_load(path.c_str(), &texture.width, &texture.height, &texture.n_channels, 0);
  data_->textures.push_back(std::make_shared<Texture>(texture));
    if (data_->textures.back()->tex_data) {
      LOG_F(INFO, "Texture loaded correctly: %s", path.c_str());
      data_->textures.back()->Process();
    }
    else {
      LOG_F(ERROR, "Failed to load texture: %s", path.c_str());
    }
}

int MaterialComponent::GetNumberOfTextures() {
  return data_->textures.size();
}

void MaterialComponent::BindTextures()
{
  for (int i = 0; i < data_->textures.size(); i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, data_->textures[i]->tex_id);
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

void Texture::Process() {
  glGenTextures(1, &tex_id);
  glBindTexture(GL_TEXTURE_2D, tex_id);

  if (n_channels == 2) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, tex_data);
  }
  else if (n_channels == 3) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_data);
  }
  else if (n_channels == 4) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data);
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

  stbi_image_free(tex_data);
}
