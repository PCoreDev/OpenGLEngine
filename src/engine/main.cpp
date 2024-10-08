//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//Main file of the engine.

#include <memory>
#include <fstream>
#include <string>

#include "engine/core.h"
#include "engine/entity_manager.h"
#include "engine/entity.h"
#include "engine/component.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "loguru/loguru.hpp"


#define PX_SCHED_IMPLEMENTATION 1
//"../../src/engine/shaders/hello_triangle.vert"
std::string LoadShader(const std::string& filename, std::string& dst) {
  //Open the file
  std::ifstream shader(filename);
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
  //Copy the code to the destination
  dst = shader_code;

  return dst;
}

int main(int argc, char** argv){
//First step initialize loguru and create the core of the engine.
//Initialize loguru
  loguru::init(argc, argv);
  loguru::add_file("../../../data/log/engine.log", loguru::Append, loguru::Verbosity_MAX);
  LOG_SCOPE_FUNCTION(INFO);

//Create the core of the engine and initialize it.
  std::unique_ptr<OpenGLEngine::Engine::Core> core = std::make_unique<OpenGLEngine::Engine::Core>();
  
  if (core->InitializeCore()) {
    LOG_F(INFO, "Core initialized correctly");
  }
  else {
    LOG_F(INFO, "Core failed to initialize");
  }
  EntityManager entity_manager;
  std::shared_ptr<Entity> entity = entity_manager.CreateEntity();
  LOG_F(INFO, "Entity created with id: %d", entity->ID());
  LOG_F(INFO, "Number of entities: %d", entity_manager.GetNumberOfEntities());

  entity->AddMeshComponent();
  entity->GetMeshComponent()->Triangle();
   unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, entity->GetMeshComponent()->GetVertexSizeb(), entity->GetMeshComponent()->GetVertexData(), GL_STATIC_DRAW);
  
  
  //***********************VERTEX SHADER***********************
  //Load shader
  std::string vertexShaderSource;
  LoadShader("../../src/engine/shaders/hello_triangle.vert", vertexShaderSource);
  //transform the string to a char*
  const char* vertexShaderSourceChar = vertexShaderSource.c_str();

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSourceChar, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    LOG_F(ERROR, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog);
  }
  else {
    LOG_F(INFO, "Vertex shader compiled correctly");
  }

  //***********************FRAGMENT SHADER***********************
  //Load shader
  std::string fragmentShaderSource;
  LoadShader("../../src/engine/shaders/hello_triangle.frag", fragmentShaderSource);
  //transform the string to a char*
  const char* fragmentShaderSourceChar = fragmentShaderSource.c_str();

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSourceChar, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    LOG_F(ERROR, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s", infoLog);
  }
  else {
    LOG_F(INFO, "Fragment shader compiled correctly");
  }


  //***********************SHADER PROGRAM***********************
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    LOG_F(ERROR, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", infoLog);
  }
  else {
    LOG_F(INFO, "Shader program linked correctly");
  }

  glUseProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

// 0. copy our vertices array in a buffer for OpenGL to use
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, entity->GetMeshComponent()->GetVertexSizeb(), entity->GetMeshComponent()->GetVertexData(), GL_STATIC_DRAW);
// 1. then set the vertex attributes pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
// 2. use with the shader program when we want to render an object
  //glUseProgram(shaderProgram);
// 3. draw the object
  //glDrawArrays(GL_TRIANGLES, 0, 3);

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, entity->GetMeshComponent()->GetVertexSizeb(), entity->GetMeshComponent()->GetVertexData(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);


  while (!core->RunningState())
  {
    //Input
    core->Input();
    //Update
    //Render
  //  glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, entity->GetMeshComponent()->GetVertexCount());


    core->EventsHandler();
    core->BufferHandler();
  }

   core->DeinitializeCore();
  return 0;
}
