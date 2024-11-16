#ifndef __MATERIAL_COMPONENT_H__
#define __MATERIAL_COMPONENT_H__ 1

#include "engine/component.h"
#include <vector>
#include <memory>

class MaterialComponent : public Component {
public:

  enum TextureType {
    Texture1D = 0,
    Texture2D,
    Texture3D,
    Texture1DArray,
    Texture2DArray,
    TextureRectangle,
    TextureCubeMap,
    TextureCubeMapArray,
    TextureBuffer,
    Texture2DMultisample,
    Texture2DMultisampleArray
  };

  MaterialComponent() = default;
  MaterialComponent(std::weak_ptr<class Entity> entity);
  ~MaterialComponent() = default;
  MaterialComponent(const MaterialComponent& other);
  MaterialComponent& operator=(const MaterialComponent& other);
  MaterialComponent(MaterialComponent&& other) noexcept;
  MaterialComponent& operator=(MaterialComponent&& other) noexcept;


  void SendToShader();


  //Setters
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

  //Getters
  glm::vec3 GetAmbient() const;
  glm::vec3 GetDiffuse() const;
  glm::vec3 GetSpecular() const;
  float GetShininess() const;


  //Texture
  unsigned int GetTextureID(int n);
  void LoadTexture(const std::string& path, TextureType type);
  int GetNumberOfTextures();
  void BindTextures();

private:
  std::unique_ptr<class MaterialData> data_;
};


#endif // !__MATERIAL_COMPONENT_H__
