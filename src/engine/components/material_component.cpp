#include "engine/components/material_component.h"
#include <vector>


#include "loguru/loguru.hpp"
#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include "engine/entity.h"

//struct Texture {
//  unsigned int texture;
//  int width, height, n_channels;
//  unsigned char* data;
//  float border_color[4];
//};
//
//struct MaterialData {
//  glm::vec3 ambient;
//  glm::vec3 diffuse;
//  glm::vec3 specular;
//  float shininess;
//  std::string diffuse_texname;
//  Texture m_texture;
//};
//
//MaterialComponent::MaterialComponent(std::weak_ptr<Entity> e) {
//  this->entity = e;
//  this->id = entity.lock()->ID();
//  this->type = ComponentType_Material;
//}
//
//MaterialComponent::MaterialComponent(const MaterialComponent& other) {
//  this->id = other.id;
//  this->type = other.type;
//  textures = std::move(other.textures);
//}
//
//MaterialComponent& MaterialComponent::operator=(const MaterialComponent& other) {
//  this->id = other.id;
//  this->type = other.type;
//  textures = std::move(other.textures);
//  return *this;
//}
//
//MaterialComponent::MaterialComponent(MaterialComponent&& other) noexcept {
//  this->textures = std::move(other.textures);
//}
//
//MaterialComponent& MaterialComponent::operator=(MaterialComponent&& other) noexcept
//{
//  if (this != &other) {
//    this->textures = std::move(other.textures);
//  }
//  return *this;
//}
//
//void MaterialComponent::LoadTexture(const std::string& path) {
//  MaterialData mdata;
//  mdata.m_texture.data = stbi_load(path.c_str(), &mdata.m_texture.width, &mdata.m_texture.height, &mdata.m_texture.n_channels, 0);
//  textures.push_back(std::make_unique<MaterialData>(mdata));
//
//  if (textures.back()->m_texture.data) {
//    LOG_F(INFO, "Texture loaded correctly");
//    Process(textures.back().get());
//  }
//  else {
//    LOG_F(ERROR, "Failed to load texture");
//  }
//}
//
//void MaterialComponent::LoadBMP_custom(const std::string& imagepath)
//{
//  unsigned char header[54]; // Each BMP file begins by a 54-bytes header
//  unsigned int dataPos;     // Position in the file where the actual data begins
//  unsigned int width, height;
//  unsigned int imageSize;   // = width*height*3
//  // Actual RGB data
//  unsigned char* data;
//
//  //Open the file
//  FILE* file = fopen(imagepath.c_str(), "rb");
//  if (!file) {
//    LOG_F(ERROR, "Image could not be opened");
//    return;
//  }
//
//  if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
//    LOG_F(ERROR, "Not a correct BMP file");
//    return;
//  }
//
//  if (header[0] != 'B' || header[1] != 'M') {
//    LOG_F(ERROR, "Not a correct BMP file");
//    return;
//  }
//
//  // Read ints from the byte array
//  dataPos = *(int*)&(header[0x0A]);
//  imageSize = *(int*)&(header[0x22]);
//  width = *(int*)&(header[0x12]);
//  height = *(int*)&(header[0x16]);
//
//  if (imageSize == 0) {
//    imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
//  }
//
//  if (dataPos == 0) {
//    dataPos = 54; // The BMP header is done that way
//  }
//
//  // Create a buffer
//  data = new unsigned char[imageSize];
//
//  // Read the actual data from the file into the buffer
//  fread(data, 1, imageSize, file);
//
//  //Everything is in memory now, the file can be closed
//  fclose(file);
//
//  return;
//}
//
//unsigned int MaterialComponent::GetTexture(int n) {
//  if (n >= textures.size()) return 0;
//  else if (textures[n] == nullptr)
//    return 0;
//
//  return textures[n]->m_texture.texture;
//}
//
//unsigned int MaterialComponent::GetTextureLength() {
//  return textures.size();
//}
//
//void MaterialComponent::Process(MaterialData* tex) {
//  glGenTextures(1, &tex->m_texture.texture);
//
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
//
//  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, tex->m_texture.border_color);
//
//
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//
//  glBindTexture(GL_TEXTURE_2D, tex->m_texture.texture);
//
//  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->m_texture.width, tex->m_texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->m_texture.data);
//  glGenerateMipmap(GL_TEXTURE_2D);
//
//  stbi_image_free(tex->m_texture.data);
//}

struct Texture {
  GLuint id;
  int width, height, n_channels;
  unsigned char* data;
  void Process();
};

struct MaterialData {
  std::vector<Texture> textures;
};

MaterialComponent::MaterialComponent(std::weak_ptr<class Entity> entity) {
  this->entity = entity;
  this->id = entity.lock()->ID();
  this->type = ComponentType_Material;
  data = std::make_unique<MaterialData>();
}

MaterialComponent::MaterialComponent(const MaterialComponent& other) {
  this->entity = other.entity;
  this->id = other.id;
  this->type = other.type;
  data = std::make_unique<MaterialData>(*other.data);
}

MaterialComponent& MaterialComponent::operator=(const MaterialComponent& other) {
  this->entity = other.entity;
  this->id = other.id;
  this->type = other.type;
  data = std::make_unique<MaterialData>(*other.data);
  return *this;
}

MaterialComponent::MaterialComponent(MaterialComponent&& other) noexcept {
  this->entity = std::move(other.entity);
  this->id = other.id;
  this->type = other.type;
  this->data = std::move(other.data);
}

MaterialComponent& MaterialComponent::operator=(MaterialComponent&& other) noexcept
{
  if (this != &other) {
    this->entity = std::move(other.entity);
    this->id = other.id;
    this->type = other.type;
    this->data = std::move(other.data);
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

  if (data->textures.back().data) {
    LOG_F(INFO, "Texture loaded correctly");
    data->textures.back().Process();
  }
  else {
    LOG_F(ERROR, "Failed to load texture");
    return -1;
  }
}

int MaterialComponent::LoadTexture(const std::string& path)
{
  Texture texture;
  texture.data = stbi_load(path.c_str(), &texture.width, &texture.height, &texture.n_channels, 0);
  data->textures.push_back(texture);

  if (data->textures.back().data) {
    LOG_F(INFO, "Texture loaded correctly");
    data->textures.back().Process();
  }
  else {
    LOG_F(ERROR, "Failed to load texture");
    return -1;
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
