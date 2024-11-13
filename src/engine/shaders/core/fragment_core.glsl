#version 460 core

out vec4 FragColor;

in vec3 normals;
in vec2 texCoords;
in vec4 fragPos;

uniform sampler2D texture_sampler_0;
//uniform sampler2D texture_sampler_1;
//uniform sampler2D texture_sampler_2;
//uniform sampler2D texture_sampler_3;


void main() {
    // Set the fragment color
    FragColor = texture(texture_sampler_0, texCoords); // + texture(texture_sampler_1, texCoords) + texture(texture_sampler_2, texCoords) + texture(texture_sampler_3, texCoords);
   //FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
