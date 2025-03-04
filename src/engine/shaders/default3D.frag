#version 460 core


struct Material {
  sampler2D diffuse_texture; // map_Kd
  sampler2D ambient_texture; // map_Ka
  sampler2D specular_texture; // map_Ks
  sampler2D emissive_texture; // map_Ke
  sampler2D alpha_texture; // map_d 
  sampler2D bump_texture; // map_bump
  sampler2D normal_texture; // map_Ns
  sampler2D displacement_texture; // disp
  sampler2D specular_exponent_texture; // map_Ns
  sampler2D reflection_texture; // map_refl
  sampler2D roughness_texture; // map_Pr
  sampler2D metallic_texture; // map_Pm
  sampler2D ambient_occlusion_texture; // map_AO
  //Could be redundant
  sampler2D height_texture; // map_h
  sampler2D glossiness_texture; // map_G
  
  vec3 ambient_color;
  vec3 diffuse_color;
  vec3 specular_color;
  float shininess;
  float dissolve;
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
  vec3 ambient = material.ambient_color;

  //Diffuse light
  vec3 position_to_light_director_vector = normalize(position - light_position);
  float diff = clamp(dot(position_to_light_director_vector, normal), 0.0f, 1.0f);
  vec3 diffuse = material.diffuse_color * diff;

  //Specular light
  vec3 light_to_position_director_vector = normalize(light_position - position);
  vec3 reflect_director_vector = normalize(reflect(light_to_position_director_vector, normalize(normal)));
  vec3 position_to_view_director_vector = normalize(position - camera_position);
  float specularConstant = pow(max(dot(position_to_view_director_vector, reflect_director_vector), 0.0f), 30.0f);
  vec3 specular = material.specular_color * specularConstant;

  //vec4 lights = vec4(ambient, 1.0f) + vec4(diffuse, 1.0f) + vec4(specular, 1.0f);
  vec3 lights = (ambient * vec3(texture(material.diffuse_texture, texCoords))) + 
  (diffuse * vec3(texture(material.diffuse_texture, texCoords))) + 
  (specular * vec3(texture(material.specular_texture, texCoords)));
   
  //FragColor = vec4(ambient + diffuse + specular, 1.0); 
  FragColor = vec4(lights, 1.0); 

    //FragColor = (texture(material.diffuse_texture, texCoords) + texture(material.specular_texture, texCoords)) * color;
}
