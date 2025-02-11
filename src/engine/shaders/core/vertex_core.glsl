#version 460 core

layout (location = 0) in vec3 aPos;  // Vertex position
layout (location = 1) in vec3 aNormal;  // Vertex normal
layout (location = 2) in vec2 aTexCoords;  // Texture coordinates

out vec3 position;
out vec3 normal;
out vec2 texCoords;

// Uniforms for transformation matrices
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main() {
    // Transform vertex position to world space
    position = vec3(model_matrix * vec4(aPos, 1.0));

    // Transform normal using the inverse transpose of the model matrix
    normal = mat3(transpose(inverse(model_matrix))) * aNormal;

    // Pass texture coordinates to the fragment shader
    texCoords = aTexCoords;

    // Transform vertex position to clip space
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(aPos, 1.0);
}