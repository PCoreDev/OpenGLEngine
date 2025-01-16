#include "engine/components/shader_component.h"

#include <fstream>


#include "glad/glad.h"
#include "loguru/loguru.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "engine/core.h"

#include "engine/components/camera_component.h"
#include "engine/components/transform_component.h"
#include "engine/components/material_component.h"

#include "engine/entity.h"






ShaderComponent::ShaderComponent(std::weak_ptr<Entity> e) {
  this->entity = e;
  this->id = entity.lock()->ID();
  this->type = ComponentType_Shader;
  data = std::make_unique<ShaderComponentData>();
  data->enable = true;
}

ShaderComponent::ShaderComponent(const ShaderComponent& other){
  this->id = other.id;
  this->type = other.type;
  this->data = std::make_unique<ShaderComponentData>();
  this->data->vertex = other.data->vertex;
  this->data->fragment = other.data->fragment;
  this->data->geometry = other.data->geometry;
  this->data->program = other.data->program;
  this->data->enable = other.data->enable;
}

ShaderComponent::ShaderComponent(ShaderComponent&& other) noexcept
{
  this->data = std::move(other.data);
  this->id = other.id;
  this->type = other.type;
}

void ShaderComponent::operator=(const ShaderComponent& other){
  this->id = other.id;
  this->type = other.type;
  this->data = std::make_unique<ShaderComponentData>();
  this->data->vertex = other.data->vertex;
  this->data->fragment = other.data->fragment;
  this->data->geometry = other.data->geometry;
  this->data->program = other.data->program;
  this->data->enable = other.data->enable;
}

ShaderComponent& ShaderComponent::operator=(ShaderComponent&& other) noexcept {
  if (this != &other) {
    this->data = std::move(other.data);
    this->id = other.id;
    this->type = other.type;
  }
  return *this;
}

void ShaderComponent::SetEnable(bool enable){
  data->enable = enable;
}

void ShaderComponent::SetBool(const std::string& name, bool value) const {
  int found = glGetUniformLocation(data->program, name.c_str());
  if (found != -1) {
    glUniform1i(found, (int)value);
  }
  else { LOG_F(ERROR, "Uniform %s not found", name.c_str()); }
}

void ShaderComponent::SetInt(const std::string& name, int value) const {
  int found = glGetUniformLocation(data->program, name.c_str());
  if (found != -1) {
    glUniform1i(found, value);
  }
  else { LOG_F(ERROR, "Uniform %s not found", name.c_str()); }
}

void ShaderComponent::SetFloat(const std::string& name, float value) const {
  int found = glGetUniformLocation(data->program, name.c_str());
  if (found != -1) {
    glUniform1f(found, value);
  }
  else { LOG_F(ERROR, "Uniform %s not found", name.c_str()); }
}

void ShaderComponent::SetVec3(const std::string& name, glm::vec3 value) const {
  int found = glGetUniformLocation(data->program, name.c_str());
  if (found != -1) {
    glUniform3fv(found, 1, &value[0]);
  }
  else { LOG_F(ERROR, "Uniform %s not found", name.c_str()); }
}

void ShaderComponent::SetMat4(const std::string& name, glm::mat4 value) const {
  int found = glGetUniformLocation(data->program, name.c_str());
  if (found != -1) {
    glUniformMatrix4fv(found, 1, GL_FALSE, &value[0][0]);
  }
  else { LOG_F(ERROR, "Uniform %s not found", name.c_str()); }
}

void ShaderComponent::SetTexture(const std::string& name, int value) const {
  int found = glGetUniformLocation(data->program, name.c_str());
  if (found != -1) {
    glUniform1i(found, value);
  }
  else { LOG_F(ERROR, "Uniform %s not found", name.c_str()); }
}

int ShaderComponent::GetProgram() {
  return data->program;
}

bool ShaderComponent::Enable()
{
  return data->enable;
}

void ShaderComponent::UseProgram(){
  glUseProgram(data->program);
}

bool ShaderComponent::LoadShader(std::string path, ShaderType type) {
  std::string shaderCode = ReadFile(path);
  switch (type)
  {
  case Vertex:
    data->vertex = CompileShader(shaderCode, type);
    break;
  case Fragment:
    data->fragment = CompileShader(shaderCode, type);
    break;
  case Geometry:
    data->geometry = CompileShader(shaderCode, type);
    break;
  default:
    break;
  }

  return LinkProgram();
}

bool ShaderComponent::LoadShaderAndAttach(std::string path, ShaderType type)
{
  std::string shaderCode = ReadFile(path);
  switch (type)
  {
  case Vertex:
    data->vertex = CompileShader(shaderCode, type);
    break;
  case Fragment:
    data->fragment = CompileShader(shaderCode, type);
    break;
  case Geometry:
    data->geometry = CompileShader(shaderCode, type);
    break;
  default:
    break;
  }

  return LinkProgram(true);
}

std::string ShaderComponent::ReadFile(const std::string& path) {
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

unsigned int ShaderComponent::CompileShader(std::string& shader_code, ShaderType type)
{
  GLuint shader = 0;
    switch (type)
    {
    case Vertex:
      shader = glCreateShader(GL_VERTEX_SHADER);
      break;
    case Fragment:
      shader = glCreateShader(GL_FRAGMENT_SHADER);
      break;
    case Geometry:
      shader = glCreateShader(GL_GEOMETRY_SHADER);
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
    switch (type)
    {
    case Vertex:
      LOG_F(ERROR, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog);
      break;
    case Fragment:
      LOG_F(ERROR, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s", infoLog);
      break;
    case Geometry:
      LOG_F(ERROR, "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n%s", infoLog);
      break;
    default:
      LOG_F(ERROR, "ERROR::SHADER::UNKNOW::COMPILATION_FAILED\n%s", infoLog);
      break;
    }
  }

  return shader;
}

bool ShaderComponent::LinkProgram(bool core) {
  GLint success;
  bool correct = true;
  GLuint program;
  if (!core) {
    data->program = glCreateProgram();
    program = data->program;
  }
  else {
    LinkProgram();
    program = OpenGLEngine::Engine::Core::shader_->GetProgram();
  }

  glAttachShader(program, data->vertex);
  glAttachShader(program, data->fragment);
  //glAttachShader(data->program, data->geometry);

  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    GLchar infoLog[512];
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    LOG_F(ERROR, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", infoLog);
    correct = false;
  }

  glUseProgram(0);
  glDeleteShader(data->vertex);
  glDeleteShader(data->fragment);
  glDeleteShader(data->geometry);

  return correct;
}