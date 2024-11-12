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


struct ShaderData {
  int vertex;
  int fragment;
  int geometry;
  int program;
  bool enable;
};



ShaderComponent::ShaderComponent(std::weak_ptr<Entity> e) {
  this->entity = e;
  this->id = entity.lock()->ID();
  this->type = ComponentType_Shader;
  data = std::make_unique<ShaderData>();
  data->enable = true;
}

ShaderComponent::ShaderComponent(const ShaderComponent& other){
  this->id = other.id;
  this->type = other.type;
  this->data = std::make_unique<ShaderData>();
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
  this->data = std::make_unique<ShaderData>();
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
    glActiveTexture(GL_TEXTURE0 + value);
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
  switch (type)
  {
  case Vertex:
    data->vertex = CompileShader(ReadFile(path), type);
    break;
  case Fragment:
    data->fragment = CompileShader(ReadFile(path), type);
    break;
  case Geometry:
    data->geometry = CompileShader(ReadFile(path), type);
    break;
  default:
    break;
  }

  return LinkProgram();
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
  GLuint shader;
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
    program = glCreateProgram();
    data->program = program;
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
  //glDeleteShader(data->vertex);
  //glDeleteShader(data->fragment);
  //glDeleteShader(data->geometry);

  return correct;
}

//void ShaderComponent::operator=(const ShaderComponent& other) {
//  this->id = other.id;
//  this->type = other.type;
//}


//void ShaderComponent::SetVertexShaderPath(const std::string& path) {
//  data->vertex_shader_path = path;
//}
//
//void ShaderComponent::SetFragmentShaderPath(const std::string& path) {
//  data->fragment_shader_path = path;
//}
//
//void ShaderComponent::SetGeometryShaderPath(const std::string& path) {
//  data->geometry_shader_path = path;
//}
//
//std::string ShaderComponent::LoadShader(const std::string& path, std::string& shader_code)
//{
//  //Open the file
//  std::ifstream shader(path);
//  //Check if the file is open
//  if (!shader.is_open()) {
//    LOG_F(ERROR, "Failed to open file %s", path.c_str());
//    return "";
//  }
//  //Read the file
//  std::string loaded_code;
//  std::string line;
//  while (std::getline(shader, line)) {
//    loaded_code += line + "\n";
//  }
//  //Close the file
//  shader.close();
//  //Copy the code to the destination
//  shader_code = loaded_code;
//  return shader_code;
//}
//
//int ShaderComponent::ProcessShader() {
//  //Vertex shader
//  LoadShader(data->vertex_shader_path, data->vertex_shader_code);
//  data->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
//  const char* vertex_shader_code_char = data->vertex_shader_code.c_str();
//  glShaderSource(data->vertex_shader, 1, &vertex_shader_code_char, nullptr);
//  glCompileShader(data->vertex_shader);
//  int success;
//  char infoLog[512];
//  glGetShaderiv(data->vertex_shader, GL_COMPILE_STATUS, &success);
//  if (!success) {
//    glGetShaderInfoLog(data->vertex_shader, 512, nullptr, infoLog);
//    LOG_F(ERROR, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog);
//    return success;
//  }
//  else {
//    LOG_F(INFO, "Vertex shader compiled correctly");
//  }
//
//  //Fragment shader
//  LoadShader(data->fragment_shader_path, data->fragment_shader_code);
//  data->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
//  const char* fragment_shader_code_char = data->fragment_shader_code.c_str();
//  glShaderSource(data->fragment_shader, 1, &fragment_shader_code_char, nullptr);
//  glCompileShader(data->fragment_shader);
//  glGetShaderiv(data->fragment_shader, GL_COMPILE_STATUS, &success);
//  if (!success) {
//    glGetShaderInfoLog(data->fragment_shader, 512, nullptr, infoLog);
//    LOG_F(ERROR, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s", infoLog);
//    return success;
//  }
//  else {
//    LOG_F(INFO, "Fragment shader compiled correctly");
//  }
//
//  //Shader program
//  data->shader_program = glCreateProgram();
//  glAttachShader(data->shader_program, data->vertex_shader);
//  glAttachShader(data->shader_program, data->fragment_shader);
//  glLinkProgram(data->shader_program);
//  glGetProgramiv(data->shader_program, GL_LINK_STATUS, &success);
//  if (!success) {
//    glGetProgramInfoLog(data->shader_program, 512, nullptr, infoLog);
//    LOG_F(ERROR, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", infoLog);
//    return success;
//  }
//  else {
//    LOG_F(INFO, "Shader program linked correctly");
//  }
//
//  glUseProgram(data->shader_program);
//  glDeleteShader(data->vertex_shader);
//  glDeleteShader(data->fragment_shader);
//
//
//  return 0;
//}
//
//void ShaderComponent::SetUniforms() {
//  std::shared_ptr<TransformComponent> transform = entity.lock()->GetTransformComponent();
//  std::shared_ptr<MaterialComponent> material = entity.lock()->GetMaterialComponent();
//
//  if (material != nullptr) {
//    //bind texture
//    int texture_location = glGetUniformLocation(data->shader_program, "texture_sampler");
//    if (texture_location != -1) {
//      glActiveTexture(GL_TEXTURE0);
//      glUniform1i(texture_location, 0);
//    }
//    else { LOG_F(ERROR, "texture_sampler not found in shader program"); }
//  }
//  else { LOG_F(ERROR, "MaterialComponent not found for entity with ID %d", id); }
//
//  if (OpenGLEngine::Engine::Core::camera_ != nullptr) {
//    if (transform != nullptr) {
//      int model_matrix_location = glGetUniformLocation(data->shader_program, "model_matrix");
//      if (model_matrix_location != -1) {
//        glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(transform->GetModelMatrix()));
//      }
//      else { LOG_F(ERROR, "model_matrix not found in shader program"); }
//    }
//    else { LOG_F(ERROR, "TransformComponent not found for entity with ID %d", id); }
//
//    int view_matrix_location = glGetUniformLocation(data->shader_program, "view_matrix");
//    if (view_matrix_location != -1) {
//      glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, glm::value_ptr(OpenGLEngine::Engine::Core::camera_->GetViewMatrix()));
//    }
//    else { LOG_F(ERROR, "view_matrix not found in shader program"); }
//
//    int projection_matrix_location = glGetUniformLocation(data->shader_program, "projection_matrix");
//    if (projection_matrix_location != -1) {
//      glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, glm::value_ptr(OpenGLEngine::Engine::Core::camera_->GetProjectionMatrix()));
//    }
//    else { LOG_F(ERROR, "projection_matrix not found in shader program"); }
//  }
//  else { LOG_F(ERROR, "There isn't any camera set"); }
//}
//
//int ShaderComponent::GetShaderProgram() {
//  return data->shader_program;
//}
//
//bool ShaderComponent::UseShader()
//{
//  return data->active;
//}
