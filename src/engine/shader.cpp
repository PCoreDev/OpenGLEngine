#include "engine/shader.h"

#include <fstream>
#include "loguru/loguru.hpp"
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

struct ShaderData
{
  GLuint shader_program;
};

Shader::Shader() {
  data_ = std::make_unique<ShaderData>();
}

Shader::~Shader()
{
}

bool Shader::LoadShader(){
  unsigned int vertex = CompileShader(ReadFile("../../src/engine/shaders/core/vertex_core.glsl"), 0);
  unsigned int fragment = CompileShader(ReadFile("../../src/engine/shaders/core/fragment_core.glsl"), 1);

  return LinkProgram(vertex, fragment);
}

int Shader::GetProgram(){
  return data_->shader_program;
}

void Shader::SetBool(const std::string& name, bool value) const{
  int found = glGetUniformLocation(data_->shader_program, name.c_str());
  if (found != -1) {
    glUniform1i(found, (int)value);
  }
  else { LOG_F(ERROR, "Uniform %s not found", name.c_str()); }
}

void Shader::SetInt(const std::string& name, int value) const{
  int found = glGetUniformLocation(data_->shader_program, name.c_str());
  if (found != -1) {
    glUniform1i(found, value);
  }
  else { LOG_F(ERROR, "Uniform %s not found", name.c_str()); }
}

void Shader::SetFloat(const std::string& name, float value) const{
  int found = glGetUniformLocation(data_->shader_program, name.c_str());
  if (found != -1) {
    glUniform1f(found, value);
  }
  else { LOG_F(ERROR, "Uniform %s not found", name.c_str()); }
}

void Shader::SetVec3(const std::string& name, glm::vec3 value) const{
  int found = glGetUniformLocation(data_->shader_program, name.c_str());
  if (found != -1) {
    glUniform3fv(found, 1, &value[0]);
  }
  else { LOG_F(ERROR, "Uniform %s not found", name.c_str()); }
}

void Shader::SetMat4(const std::string& name, glm::mat4 value) const{
  int found = glGetUniformLocation(data_->shader_program, name.c_str());
  if (found != -1) {
    glUniformMatrix4fv(found, 1, GL_FALSE, &value[0][0]);
  }
  else { LOG_F(ERROR, "Uniform %s not found", name.c_str()); }
}

void Shader::SetTexture(const std::string& name, int value) const {
  int found = glGetUniformLocation(data_->shader_program, name.c_str());
  if (found != -1) {
    glUniform1i(found, value);
  }
  else { LOG_F(ERROR, "Uniform %s not found", name.c_str()); }
}

void Shader::UseProgram(){
  glUseProgram(data_->shader_program);
}

std::string Shader::ReadFile(const std::string& path) {
  std::string code;
  std::ifstream file;

  file.open(path);

  if (!file.is_open()) {
    LOG_F(ERROR, "Failed to open file %s", path.c_str());
  }

  std::string loaded_code;
  std::string line;

  while (std::getline(file, line)) {
    loaded_code += line + "\n";
  }

  file.close();

  return loaded_code;
}

unsigned int Shader::CompileShader(std::string& shader_code, int shader_type){
  //Create the shader
  GLuint shader;
  switch (shader_type)
  {
  case 0:
    shader = glCreateShader(GL_VERTEX_SHADER);
    break;
  case 1:
    shader = glCreateShader(GL_FRAGMENT_SHADER);
    break;
  default:
    
    break;
  }
    
  const GLchar* code = shader_code.c_str();
  GLint success;

  glShaderSource(shader, 1, &code, NULL);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    GLchar infoLog[512];
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    switch (shader_type)
    {
    case 0:
      LOG_F(ERROR, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog);
      break;
    case 1:
      LOG_F(ERROR, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s", infoLog);
      break;
    default:
      LOG_F(ERROR, "ERROR::SHADER::UNKNOW::COMPILATION_FAILED\n%s", infoLog);
      break;
    }
  }

  return shader;
}

bool Shader::LinkProgram(unsigned int &vertex, unsigned int &fragment) {
  GLint success;
  bool correct = true;
  GLint program = glCreateProgram();
  data_->shader_program = program;

  glAttachShader(data_->shader_program, vertex);
  glAttachShader(data_->shader_program, fragment);

  glLinkProgram(data_->shader_program);

  glGetProgramiv(data_->shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    GLchar infoLog[512];
    glGetProgramInfoLog(data_->shader_program, 512, NULL, infoLog);
    LOG_F(ERROR, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", infoLog);
    correct = false;
  }

  glUseProgram(0);
  glDeleteShader(vertex);
  glDeleteShader(fragment);

  return correct;
}
