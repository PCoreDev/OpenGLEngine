#version 460 core

layout (location = 0) in vec3 aPos;  // Vertex position
//layout (location = 1) in vec3 aNormal;  // Vertex normal
//layout (location = 2) in vec2 aTexCoords;  // Texture coordinates

//out vec3 position;
//out vec3 normal;
out vec3 texCoords;
//out vec4 color;

// Uniforms for transformation matrices
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main(){
  //position = vec4(model_matrix * vec4(aPos, 1.0)).xyz;
  //normal = mat3(model_matrix) * aNormal;
  texCoords = aPos;
  vec4 pos = projection_matrix * view_matrix * vec4(aPos, 1.0);
  gl_Position = pos.xyww;
}