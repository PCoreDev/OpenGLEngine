#version 460 core

out vec4 FragColor;

in vec3 normals;
in vec2 texCoords;

void main() {
    // Set the fragment color
    FragColor = vec4(texCoords.x, texCoords.y, 0.0f, 1.0); // Orange color
}
