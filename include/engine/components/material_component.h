#ifndef __MATERIAL_COMPONENT_H__
#define __MATERIAL_COMPONENT_H__ 1

#include "engine/component.h"
#include <vector>
#include <memory>


//class MaterialComponent : public Component {
//public:
//  MaterialComponent() = default;
//  MaterialComponent(std::weak_ptr<class Entity> entity);
//  ~MaterialComponent() = default;
//  MaterialComponent(const MaterialComponent&);
//  MaterialComponent& operator=(const MaterialComponent& other);
//  MaterialComponent(MaterialComponent&& other) noexcept;
//  MaterialComponent& operator=(MaterialComponent&&) noexcept;
//  void LoadTexture(const std::string& path);
//  void LoadBMP_custom(const std::string& imagepath);
//  unsigned int GetTexture(int n);
//  unsigned int GetTextureLength();
//  void Process(class MaterialData* data);
//
//private:
//  std::vector<std::unique_ptr<class MaterialData>> textures;
//};
//
//

class MaterialComponent : public Component {
public:
  MaterialComponent() = default;
  MaterialComponent(std::weak_ptr<class Entity> entity);
  ~MaterialComponent() = default;
  MaterialComponent(const MaterialComponent& other);
  MaterialComponent& operator=(const MaterialComponent& other);
  MaterialComponent(MaterialComponent&& other) noexcept;
  MaterialComponent& operator=(MaterialComponent&& other) noexcept;

  int LoadBPM(const std::string& path);
  int LoadTexture(int n, const std::string& path);
  void Process(class MaterialData* data);

  size_t GetNumbersOfTextures();
  unsigned int GetTexture(int n);

  void SetAmbient(int n, const float ambient_x, float ambient_y, float ambient_z);
  void SetAmbient(int n, const float ambient[3]);
  void SetAmbient(int n, const glm::vec3& ambient);

  void SetDiffuse(int n, const float diffuse_x, float diffuse_y, float diffuse_z);
  void SetDiffuse(int n, const float diffuse[3]);
  void SetDiffuse(int n, const glm::vec3& diffuse);

  void SetSpecular(int n, const float specular_x, float specular_y, float specular_z);
  void SetSpecular(int n, const float specular[3]);
  void SetSpecular(int n, const glm::vec3& specular);

  void SetShininess(int n, float shininess);

  void AddNewMaterial(std::string path, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shinisses);

private:
  std::vector<std::unique_ptr<class MaterialData>> data_;

};


#endif // !__MATERIAL_COMPONENT_H__
