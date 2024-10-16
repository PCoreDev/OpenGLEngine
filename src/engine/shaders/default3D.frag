#version 460 core

out vec4 FragColor;

in vec3 normals;
in vec2 texCoords;
in vec4 fragPos;

void main() {
    // Set the fragment color
    FragColor = vec4(normals.x, normals.y, normals.z , 1.0); // Orange color
}
