#ifndef __SHADER_COMPONENT_H__
#define __SHADER_COMPONENT_H__ 1

#include "engine/component.h"


class ShaderComponent : public Component {
public:
  enum ShaderType {
    Vertex,
    Fragment,
    Geometry,
    MAX
  };

  ShaderComponent() = default;
  ShaderComponent(std::weak_ptr<Entity> entity);
  ShaderComponent(const ShaderComponent& other);
  ShaderComponent(ShaderComponent&& other) noexcept;
  void operator=(const ShaderComponent& other);
  ShaderComponent& operator=(ShaderComponent&& other) noexcept;

  void SetEnable(bool enable);
  void SetBool(const std::string& name, bool value) const;
  void SetInt(const std::string& name, int value) const;
  void SetFloat(const std::string& name, float value) const;
  void SetVec3(const std::string& name, glm::vec3 value) const;
  void SetMat4(const std::string& name, glm::mat4 value) const;
  void SetTexture(const std::string& name, int value) const;

  int GetProgram();

  bool Enable();

  void UseProgram();


  bool LoadShader(std::string path, ShaderType type);
private:
  std::string ReadFile(const std::string& path);
  unsigned int CompileShader(std::string& shader_code, ShaderType type); 
  bool LinkProgram(bool core = false);

  std::unique_ptr<class ShaderData> data;
};




#endif // !__SHADER_COMPONENT_H__
