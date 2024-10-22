#version 460 core

out vec4 FragColor;

in vec3 normals;
in vec2 texCoords;
in vec4 fragPos;

uniform sampler2D texture_sampler;

void main() {
    // Set the fragment color
    FragColor = texture(texture_sampler, texCoords) * vec4(1.0, 1.0, 1.0, 1.0);  
}
