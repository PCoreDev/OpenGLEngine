#version 460 core


struct Material {
  sampler2D diffuse_texture[32]; // map_Kd
  sampler2D ambient_texture[32]; // map_Ka
  sampler2D specular_texture[32]; // map_Ks
  sampler2D emissive_texture[32]; // map_Ke
  sampler2D alpha_texture[32]; // map_d 
  sampler2D bump_texture[32]; // map_bump
  sampler2D normal_texture[32]; // map_Ns
  sampler2D displacement_texture[32]; // disp
  sampler2D specular_exponent_texture[32]; // map_Ns
  sampler2D reflection_texture[32]; // map_refl
  sampler2D roughness_texture[32]; // map_Pr
  sampler2D metallic_texture[32]; // map_Pm
  sampler2D ambient_occlusion_texture[32]; // map_AO
  //Could be redundant
  sampler2D height_texture[32]; // map_h
  sampler2D glossiness_texture[32]; // map_G
  
  vec3 ambient_color[32];
  vec3 diffuse_color[32];
  vec3 specular_color[32];
  float shininess[32];
  float dissolve[32];
};

out vec4 FragColor;

in vec3 position;
in vec3 normal;
in vec2 texCoords;
in vec4 color;

uniform vec3 light_position;
uniform vec3 camera_position;

uniform Material material;

uniform int texture_index;

vec3 CalculateAmbient(Material material, int index){
  return material.ambient_color[index];
}

vec3 CalculateDiffuse(Material material, vec3 position, vec3 normal, vec3 lightPos, int index){

  vec3 position_to_light_director_vector = normalize(light_position - position);

  float diffuse = clamp(dot(position_to_light_director_vector, normal), 0.0f, 1.0f);

  return material.diffuse_color[index] * diffuse;
}

vec3 CalculateSpecular(Material material, vec3 position, vec3 normal, vec3 lightPos, vec3 cameraPos, int index){

  vec3 light_to_position_director_vector = normalize(position - light_position);
  vec3 reflect_director_vector = normalize(reflect(light_to_position_director_vector, normalize(normal)));
  vec3 position_to_view_director_vector = normalize(camera_position - position);
  float specularConstant = pow(max(dot(position_to_view_director_vector, reflect_director_vector), 0.0f), 35.0f);
  return material.specular_color[index] * specularConstant;
}

void main() {

vec3 ambient = vec3(0.0f);
vec3 diffuse = vec3(0.0f);
vec3 specular = vec3(0.0f);

for(int i = 0; i < texture_index; i++){
  ambient += CalculateAmbient(material, i) * vec3(texture(material.diffuse_texture[i], texCoords));
  diffuse += CalculateDiffuse(material, position, normal, light_position, i) * vec3(texture(material.diffuse_texture[i], texCoords));
  specular += CalculateSpecular(material, position, normal, light_position, camera_position, i) * vec3(texture(material.specular_texture[i], texCoords));
}


  vec3 lights = ambient + diffuse + specular;
     
  FragColor = vec4(lights, 1.0); 

}
