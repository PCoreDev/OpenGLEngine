#version 460 core
out vec4 FragColor;
  
in vec2 texCoords;

uniform sampler2D screen_texture;

void main()
{ 
    FragColor =  texture(screen_texture, texCoords);
}