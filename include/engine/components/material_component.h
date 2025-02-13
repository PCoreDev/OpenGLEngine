#ifndef __MATERIAL_COMPONENT_H__
#define __MATERIAL_COMPONENT_H__ 1

#include "engine/component.h"
#include <vector>
#include <memory>


class MaterialComponent : public Component {
public:

  MaterialComponent() = default;
  MaterialComponent(std::weak_ptr<class Entity> entity);
  ~MaterialComponent() = default;
  MaterialComponent(const MaterialComponent& other);
  MaterialComponent& operator=(const MaterialComponent& other);
  MaterialComponent(MaterialComponent&& other) noexcept;
  MaterialComponent& operator=(MaterialComponent&& other) noexcept;

  void AddNewMaterial(
    const std::string& name,
    const std::string& diffuse_path,
    const std::string& ambient_path,
    const std::string& specular_path,
    const std::string& alpha_path,
    const std::string& bump_path,
    const std::string& normal_path,
    const glm::vec3& ambient,
    const glm::vec3& diffuse,
    const glm::vec3& specular,
    float shininess,
    float dissolve,
    float opt_dens,
    int illum
  );

  void BindMaterial(std::shared_ptr<class Shader> shader, int index);
  void SendToShader(std::shared_ptr<class Shader> shader, int index);
  void CleanUp();

  void ShowStats() override;

private:
  std::shared_ptr<class MaterialData> data_;
};


#endif // !__MATERIAL_COMPONENT_H__