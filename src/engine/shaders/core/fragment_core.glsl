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

vec3 CalculateAmbient(Material material){
  return material.ambient_color;
}

vec3 CalculateDiffuse(Material material, vec3 position, vec3 normal, vec3 lightPos){

  vec3 position_to_light_director_vector = normalize(light_position - position);

  float diffuse = clamp(dot(position_to_light_director_vector, normal), 0.0f, 1.0f);

  return material.diffuse_color * diffuse;
}

vec3 CalculateSpecular(Material material, vec3 position, vec3 normal, vec3 lightPos, vec3 cameraPos){

  vec3 light_to_position_director_vector = normalize(position - light_position);
  vec3 reflect_director_vector = normalize(reflect(light_to_position_director_vector, normalize(normal)));
  vec3 position_to_view_director_vector = normalize(camera_position - position);
  float specularConstant = pow(max(dot(position_to_view_director_vector, reflect_director_vector), 0.0f), 35.0f);
  return material.specular_color * specularConstant;
}

void main() {

  vec3 ambient = CalculateAmbient(material) * vec3(texture(material.diffuse_texture, texCoords));
  vec3 diffuse = CalculateDiffuse(material, position, normal, light_position) * vec3(texture(material.diffuse_texture, texCoords));
  vec3 specular = CalculateSpecular(material, position, normal, light_position, camera_position) * vec3(texture(material.specular_texture, texCoords));
  
  vec3 lights = ambient + diffuse + specular;
     
  FragColor = vec4(lights, 1.0); 

}
