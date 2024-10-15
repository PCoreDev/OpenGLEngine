#version 460 core

layout (location = 0) in vec3 aPos;  // Vertex position

// Uniforms for transformation matrices
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main() {
    // Apply transformations
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(aPos, 1.0);
}

