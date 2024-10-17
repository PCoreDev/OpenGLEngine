#version 460 core

layout (location = 0) in vec3 aPos;  // Vertex position
layout (location = 1) in vec3 aNormal;  // Vertex normal
layout (location = 2) in vec2 aTexCoords;  // Texture coordinates

// Uniforms for transformation matrices
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

out vec3 normals;  // Normal in world space
out vec2 texCoords;  // Texture coordinates
out vec4 fragPos;  // Fragment position in world space

void main() {
    // Apply transformations
    gl_Position = model_matrix * vec4(aPos, 1.0);
    normals = aNormal;
    texCoords = aTexCoords;
    fragPos = view_matrix * projection_matrix * vec4(aPos, 1.0);
}

