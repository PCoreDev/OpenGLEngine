#ifndef __SHADER_H__
#define __SHADER_H__ 1

#include <memory>
#include <string>

#include "glm/glm.hpp"

struct ShaderData
{
  unsigned int shader_program;
};

class Shader
{
public:
	Shader();
  Shader(const Shader& other);
  Shader(Shader&& other) noexcept;
	~Shader();

  bool LoadShader(std::string vert, std::string frag);
  int GetProgram();

  void SetBool(const std::string& name, bool value) const;
  void SetInt(const std::string& name, int value) const;
  void SetFloat(const std::string& name, float value) const;
  void SetVec2(const std::string& name, glm::vec2 value) const;
  void SetVec3(const std::string& name, glm::vec3 value) const;
  void SetMat4(const std::string& name, glm::mat4 value) const;
  void SetTexture(const std::string& name, int value) const;

  void UseProgram();

private:
  std::unique_ptr<ShaderData> data_;
  std::string ReadFile(const std::string& path);
  unsigned int CompileShader(std::string& shader_code, int shader_type); // 0 = vertex, 1 = fragment, 2 = program
  bool LinkProgram(unsigned int &vertex, unsigned int &fragment);
};

#endif // !__SHADER_H__
