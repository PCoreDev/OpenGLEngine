//Author: Pablo "Pau" Core Palmero
//Date: 4-June-2024
//Email: p.core.dev@outlook.com
//This header contains the shader class's implementation of the engine.
#include "engine/shader.h"

#include "loguru/loguru.hpp"


Shader::Shader(){
    LOG_F(INFO, "Constructing Shader");
}

Shader::Shader(const char* vertexPath, const char* fragmentPath){
    LOG_F(INFO, "Constructing Shader");
    LoadShader(vertexPath, vertex_data_);
    LoadShader(fragmentPath, fragment_data_);
}

void Shader::LoadShader(const char* path, std::string& shader_data){
 /*
    //Open the file
  std::ifstream shader(path);
  //Check if the file is open
  if (!shader.is_open()) {
    LOG_F(ERROR, "Failed to open file %s", filename.c_str());
    return "";
  }
  //Read the file
  std::string shader_code;
  std::string line;
  while (std::getline(shader, line)) {
    shader_code += line + "\n";
  }
  //Close the file
  shader.close();

  shader_data = shader_code;
  */
}

Shader::~Shader(){
    LOG_F(INFO, "Destructing Shader");
    //TODO clean up
}
