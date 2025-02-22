#include "engine/components/skybox_component.h"

#include <glad/glad.h>

#include "stb/stb_image.h"
#include "loguru/loguru.hpp"


struct SkyBoxData {
  unsigned int skybox_id;
};


SkyBoxComponent::SkyBoxComponent(std::weak_ptr<Entity> entity) {
  this->entity = entity;
  this->type = ComponentType_SkyBox;
  data_ = std::make_unique<SkyBoxData>();
}

SkyBoxComponent::SkyBoxComponent(const SkyBoxComponent& other) {
  this->entity = other.entity;
  this->type = other.type;
  data_ = std::make_unique<SkyBoxData>();
  data_->skybox_id = other.data_->skybox_id;
}

SkyBoxComponent::SkyBoxComponent(SkyBoxComponent&& other) noexcept {
  this->entity = other.entity;
  this->type = other.type;
  data_ = std::move(other.data_);
}

void SkyBoxComponent::operator=(const SkyBoxComponent& other) {
  this->entity = other.entity;
  this->type = other.type;
  data_ = std::make_unique<SkyBoxData>();
  data_->skybox_id = other.data_->skybox_id;
}

SkyBoxComponent& SkyBoxComponent::operator=(SkyBoxComponent&& other) noexcept {
  this->entity = other.entity;
  this->type = other.type;
  data_ = std::move(other.data_);
  return *this;
}

SkyBoxComponent::~SkyBoxComponent() {
  glDeleteTextures(1, &data_->skybox_id);
  data_.reset();
}

unsigned int SkyBoxComponent::GetSkyBoxID() const {
  return data_->skybox_id;
}

void SkyBoxComponent::LoadSkyBox(std::vector<std::string> faces_path) {
  glGenTextures(1, &data_->skybox_id);
  glBindTexture(GL_TEXTURE_CUBE_MAP, data_->skybox_id);
  int width, height, n_channels;
  for (unsigned int i = 0; i < faces_path.size(); i++) {
    unsigned char* data;
    data = stbi_load(faces_path[i].c_str(), &width, &height, &n_channels, 0);
    if (data) {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    } else {
      LOG_F(ERROR, "Failed to load texture: %s", faces_path[i].c_str());
    }
    stbi_image_free(data);
  }

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void SkyBoxComponent::ShowStats(){
}
