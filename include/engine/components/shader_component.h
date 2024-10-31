#ifndef __SHADER_COMPONENT_H__
#define __SHADER_COMPONENT_H__ 1

#include "engine/component.h"


struct ShaderComponent : public Component {
  //ShaderComponent() = default;
  ShaderComponent(std::weak_ptr<Entity> entity);
  //ShaderComponent(const ShaderComponent&);
  //void operator=(const ShaderComponent& other);
  void SetVertexShaderPath(const std::string& path);
  void SetFragmentShaderPath(const std::string& path);
  void SetGeometryShaderPath(const std::string& path);
  std::string LoadShader(const std::string& path, std::string& shader_code);
  int ProcessShader();
  void SetUniforms();
  int GetShaderProgram();
  bool UseShader();

  std::unique_ptr<class ShaderData> data;
};




#endif // !__SHADER_COMPONENT_H__
