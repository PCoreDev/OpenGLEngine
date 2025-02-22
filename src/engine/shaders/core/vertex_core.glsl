#version 460 core

// Vertex attributes
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;


out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;


uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main() {
    FragPos = vec3(model_matrix * vec4(aPos, 1.0));

    Normal = mat3(transpose(inverse(model_matrix))) * aNormal;

    TexCoords = aTexCoords;

    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(aPos, 1.0);
}