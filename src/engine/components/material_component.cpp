#include "engine/components/material_component.h"
#include <vector>

#include "loguru/loguru.hpp"
#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "engine/entity.h"
#include "engine/components/shader_component.h"
#include "engine/core.h"

#include <map>

struct Texture {
  GLuint id = -1;
  int width = 0;
  int height = 0;
  int n_channels = 0;
};

struct Material {
  std::string name;

  Texture diffuse_texture; // map_Kd
  Texture ambient_texture; // map_Ka
  Texture specular_texture; // map_Ks
  Texture alpha_texture; // map_d 
  Texture bump_texture; // map_bump
  Texture normal_texture; // map_Ns

  glm::vec3 ambient_color = glm::vec3(0.0f);
  glm::vec3 diffuse_color = glm::vec3(0.0f);
  glm::vec3 specular_color = glm::vec3(0.0f);

  float shininess = 0.0f;
  float dissolve = 0.0f;
  int illumination = 0;
  float optical_density = 0.0f;

  void LoadTexture(const std::string& path, Texture& texture) {
    unsigned char* data = stbi_load(path.c_str(), &texture.width, &texture.height, &texture.n_channels, 0);
    if (data) {
      GLenum format = GL_RGB; // Default format
      glGenTextures(1, &texture.id);
      glBindTexture(GL_TEXTURE_2D, texture.id);
      if (texture.n_channels == 1)
        format = GL_RED;
      else if (texture.n_channels == 3)
        format = GL_RGB;
      else if (texture.n_channels == 4)
        format = GL_RGBA;
      glTexImage2D(GL_TEXTURE_2D, 0, format, texture.width, texture.height, 0, format, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {
      LOG_F(ERROR, "Failed to load texture: %s", path.c_str());
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
  }
};

struct MaterialData {
  std::vector<Material> materials;
};

MaterialComponent::MaterialComponent(std::weak_ptr<class Entity> entity) {
  this->entity = entity;
  this->id = entity.lock()->ID();
  this->type = ComponentType_Material;
  this->data_ = std::make_shared<MaterialData>();
}

MaterialComponent::MaterialComponent(const MaterialComponent& other) {
  this->entity = other.entity;
  this->id = other.id;
  this->type = other.type;
  this->data_ = std::make_shared<MaterialData>(*other.data_);
  //Copy the vector of unique pointers
}

MaterialComponent& MaterialComponent::operator=(const MaterialComponent& other) {
  this->entity = other.entity;
  this->id = other.id;
  this->type = other.type;
  this->data_ = std::make_shared<MaterialData>(*other.data_);
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

void MaterialComponent::AddNewMaterial(const std::string& name, const std::string& diffuse_path, const std::string& ambient_path, const std::string& specular_path, const std::string& alpha_path, const std::string& bump_path, const std::string& normal_path, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess, float dissolve, float opt_dens, int illum) {
  Material material;
  material.name = name;

  //Split the path to get the file name
  std::string diffuse_name = diffuse_path.substr(diffuse_path.find_last_of("/\\") + 1);
  std::string ambient_name = ambient_path.substr(ambient_path.find_last_of("/\\") + 1);
  std::string specular_name = specular_path.substr(specular_path.find_last_of("/\\") + 1);
  std::string alpha_name = alpha_path.substr(alpha_path.find_last_of("/\\") + 1);
  std::string bump_name = bump_path.substr(bump_path.find_last_of("/\\") + 1);
  std::string normal_name = normal_path.substr(normal_path.find_last_of("/\\") + 1);

  if (diffuse_name != "") {
    material.LoadTexture(diffuse_path, material.diffuse_texture);
  }
  if (ambient_name != "") {
    material.LoadTexture(ambient_path, material.ambient_texture);
  }
  if (specular_name != "") {
    material.LoadTexture(specular_path, material.specular_texture);
  }
  if (alpha_name != "") {
    material.LoadTexture(alpha_path, material.alpha_texture);
  }
  if (bump_name != "") {
    material.LoadTexture(bump_path, material.bump_texture);
  }
  if (normal_name != "") {
    material.LoadTexture(normal_path, material.normal_texture);
  }
  material.ambient_color = ambient;
  material.diffuse_color = diffuse;
  material.specular_color = specular;
  material.shininess = shininess;
  material.dissolve = dissolve;
  material.optical_density = opt_dens;
  material.illumination = illum;
  data_->materials.push_back(material);
}

void MaterialComponent::BindMaterial(std::shared_ptr<class Shader> shader, int index)
{
  if (index < data_->materials.size()) {
    Material material = data_->materials[index];

    if (material.diffuse_texture.id != -1) {
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, material.diffuse_texture.id);
      shader->SetTexture("material.diffuse_texture", 1);
    }
    else {
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, 0);
    }

    if (material.ambient_texture.id != -1) {
      glActiveTexture(GL_TEXTURE2);
      glBindTexture(GL_TEXTURE_2D, material.ambient_texture.id);
      shader->SetTexture("material.ambient_texture", 2);
    }
    else{
      glActiveTexture(GL_TEXTURE2);
      glBindTexture(GL_TEXTURE_2D, 0);
    }

    if (material.specular_texture.id != -1) {
      glActiveTexture(GL_TEXTURE3);
      glBindTexture(GL_TEXTURE_2D, material.specular_texture.id);
      shader->SetTexture("material.specular_texture", 3);
    }
    else {
      glActiveTexture(GL_TEXTURE3);
      glBindTexture(GL_TEXTURE_2D, 0);
    }

    if (material.alpha_texture.id != -1) {
      glActiveTexture(GL_TEXTURE4);
      glBindTexture(GL_TEXTURE_2D, material.alpha_texture.id);
      shader->SetTexture("material.alpha_texture", 4);
    }
    else {
      glActiveTexture(GL_TEXTURE4);
      glBindTexture(GL_TEXTURE_2D, 0);
    }

    if (material.bump_texture.id != -1) {
      glActiveTexture(GL_TEXTURE5);
      glBindTexture(GL_TEXTURE_2D, material.bump_texture.id);
      shader->SetTexture("material.bump_texture", 5);
    }
    else {
      glActiveTexture(GL_TEXTURE5);
      glBindTexture(GL_TEXTURE_2D, 0);
    }

    if (material.normal_texture.id != -1) {
      glActiveTexture(GL_TEXTURE6);
      glBindTexture(GL_TEXTURE_2D, material.normal_texture.id);
      shader->SetTexture("material.normal_texture", 6);
    }
    else {
      glActiveTexture(GL_TEXTURE6);
      glBindTexture(GL_TEXTURE_2D, 0);
    }

  }
  else {
    LOG_F(ERROR, "Material index out of range");
  }
}

void MaterialComponent::SendToShader(std::shared_ptr<class Shader> shader, int index)
{
  if (index < data_->materials.size()) {
    Material material = data_->materials[index];
    shader->SetTexture("material.diffuse_texture", 1);
    shader->SetTexture("material.ambient_texture", 2);
    shader->SetTexture("material.specular_texture", 3);
    shader->SetTexture("material.alpha_texture", 4);
    shader->SetTexture("material.bump_texture", 5);
    shader->SetTexture("material.normal_texture", 6);

    shader->SetVec3("material.ambient_color", material.ambient_color);
    shader->SetVec3("material.diffuse_color", material.diffuse_color);
    shader->SetVec3("material.specular_color", material.specular_color);
    shader->SetFloat("material.shininess", material.shininess);
    shader->SetFloat("material.dissolve", material.dissolve);
    shader->SetFloat("material.optical_density", material.optical_density);
    shader->SetInt("material.illumination", material.illumination);
  }
  else {
    LOG_F(ERROR, "Material index out of range");
  }
}

void MaterialComponent::CleanUp() {
  for (auto& material : data_->materials) {
    glDeleteTextures(1, &material.diffuse_texture.id);
    glDeleteTextures(1, &material.ambient_texture.id);
    glDeleteTextures(1, &material.specular_texture.id);
    glDeleteTextures(1, &material.alpha_texture.id);
    glDeleteTextures(1, &material.bump_texture.id);
    glDeleteTextures(1, &material.normal_texture.id);
  }
  data_->materials.clear();
}
