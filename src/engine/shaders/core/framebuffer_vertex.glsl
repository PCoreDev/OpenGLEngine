#version 460 core

layout (location = 0) in vec3 aPos;  // Vertex position
layout (location = 1) in vec2 aTexCoords;  // Texture coordinates

out vec2 texCoords;

void main()
{
    gl_Position = vec4(aPos, 1.0); 
    texCoords = vec2(aTexCoords.x, 1.0 - aTexCoords.y);
}  