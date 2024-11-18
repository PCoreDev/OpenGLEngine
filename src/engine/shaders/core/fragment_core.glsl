#version 460 core


struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
  sampler2D base_color_texture;
  sampler2D metallic_texture;
  sampler2D specular_texture;
  sampler2D roughness_texture;
  sampler2D emissive_texture;
  sampler2D diffuse_texture;
  sampler2D normal_texture;
  sampler2D ambient_oclusion_texture;
};

out vec4 FragColor;

in vec3 position;
in vec3 normal;
in vec2 texCoords;
in vec4 color;

uniform vec3 light_position;
uniform vec3 camera_position;

uniform Material material;


void main() {
    // Set the fragment color

    //Ambient light
    vec3 ambient = material.ambient;

    //Diffuse light
    vec3 position_to_light_director_vector = normalize(position - light_position);
    vec3 diffuse_color = vec3(1.0f, 1.0f, 1.0f);
    float diff = clamp(dot(position_to_light_director_vector, normal), 0.0f, 1.0f);
    vec3 diffuse = material.diffuse * diff;

    //Specular light
    vec3 light_to_position_director_vector = normalize(light_position - position);
    vec3 reflect_director_vector = normalize(reflect(light_to_position_director_vector, normalize(normal)));
    vec3 position_to_view_director_vector = normalize(position - camera_position);
    float specularConstant = pow(max(dot(position_to_view_director_vector, reflect_director_vector), 0.0f), 30.0f);
    vec3 specular = material.specular * specularConstant;

    //vec4 lights = vec4(ambient, 1.0f) + vec4(diffuse, 1.0f) + vec4(specular, 1.0f);
    vec3 lights = (ambient * vec3(texture(material.diffuse_texture, texCoords))) + 
    (diffuse * vec3(texture(material.diffuse_texture, texCoords))) + 
    (specular * vec3(texture(material.specular_texture, texCoords)));
   
    //FragColor = vec4(ambient + diffuse + specular, 1.0); 
    FragColor = vec4(lights, 1.0); 


    //FragColor = (texture(material.diffuse_texture, texCoords) + texture(material.specular_texture, texCoords)) * color;
}
