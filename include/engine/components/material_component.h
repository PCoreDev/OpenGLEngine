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
  int LoadTexture(const std::string& path);

private:
  std::unique_ptr<class MaterialData> data;

};


#endif // !__MATERIAL_COMPONENT_H__
