/*****************************************************************//**
 * \file   shader_component.h
 * \brief  
 * 
 * \author pablo
 * \date   January 2025
 *********************************************************************/
#ifndef __SHADER_COMPONENT_H__
#define __SHADER_COMPONENT_H__ 1

#include "engine/component.h"
#include "engine/shader.h"


class ShaderComponent : public Component {
public:

  ShaderComponent();
  ShaderComponent(std::weak_ptr<Entity> e);
  ShaderComponent(const ShaderComponent& other);
  ShaderComponent(ShaderComponent&& other) noexcept;
  ~ShaderComponent();

  void operator=(const ShaderComponent& other);
  ShaderComponent& operator=(ShaderComponent&& other) noexcept;

  bool LoadShader(std::string vert, std::string frag);

  int GetProgram();

  std::shared_ptr<Shader> GetShader();

  void SetBool(const std::string& name, bool value) const;
  void SetInt(const std::string& name, int value) const;
  void SetFloat(const std::string& name, float value) const;
  void SetVec2(const std::string& name, glm::vec2 value) const;
  void SetVec3(const std::string& name, glm::vec3 value) const;
  void SetMat4(const std::string& name, glm::mat4 value) const;
  void SetTexture(const std::string& name, int value) const;

  void UseShader();

private:
  std::unique_ptr<class ShaderComponentdata> data_;
};
#endif // !__SHADER_COMPONENT_H__
