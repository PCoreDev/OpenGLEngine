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

struct DirectionalLight {
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  vec3 color;
};

struct PointLight {
  vec3 position;  
  
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  
  float constant;
  float linear;
  float quadratic;
  vec3 color;
};

struct SpotLight {
  vec3  position;
  vec3  direction;
  float cutOff;
  vec3 color;
}; 


out vec4 FragColor;

in vec3 position;
in vec3 normal;
in vec2 texCoords;

uniform vec3 light_position;

uniform vec3 camera_position;

uniform Material material;

uniform int texture_index;

uniform DirectionalLight directional_light;
uniform PointLight point_light[16];
uniform SpotLight spot_light[16];

uniform int point_light_count;
uniform int spot_light_count;


vec3 CalculateDirectionalLight(int i) {
//ambient
vec3 ambient = directional_light.ambient * (texture(material.ambient_texture[i], texCoords).rgb);

//diffuse
vec3 normal = normalize(normal);
vec3 lightDir = normalize(-directional_light.direction);
float diff = max(dot(normal, lightDir), 0.0);
vec3 diffuse = directional_light.diffuse * diff * (texture(material.diffuse_texture[i], texCoords).rgb);

//specular
vec3 viewDir = normalize(camera_position - position);
vec3 reflectDir = reflect(-lightDir, normal);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess[i]);
vec3 specular = directional_light.specular * spec * (texture(material.specular_texture[i], texCoords).rgb);

return ((ambient * material.ambient_color[i]) + (diffuse * material.diffuse_color[i]) + (specular * material.specular_color[i]));
}

vec3 CalculatePointLight(int i) {
//ambient
vec3 ambient = point_light[i].ambient * (texture(material.ambient_texture[i], texCoords).rgb);

//diffuse
vec3 normal = normalize(normal);
vec3 lightDir = normalize(point_light[i].position - position);
float diff = max(dot(normal, lightDir), 0.0);
vec3 diffuse = point_light[i].diffuse * diff * (texture(material.diffuse_texture[i], texCoords).rgb);

//specular
vec3 viewDir = normalize(camera_position - position);
vec3 reflectDir = reflect(-lightDir, normal);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess[i]);
vec3 specular = point_light[i].specular * spec * (texture(material.specular_texture[i], texCoords).rgb);

// attenuation
float distance = length(point_light[i].position - position);
float attenuation = 1.0 / (point_light[i].constant + point_light[i].linear * distance + point_light[i].quadratic * (distance * distance));
  
//return ((ambient * material.ambient_color[i]) + (diffuse * material.diffuse_color[i]) + (specular * material.specular_color[i])) * attenuation;
return (ambient + diffuse+ specular) * attenuation;
}

void main() {

  vec3 lights = vec3(0.0f);

  for(int i = 0; i < texture_index; i++){
    //lights += CalculateDirectionalLight(i);
    for(int j = 0; j < point_light_count; j++){
      lights += CalculatePointLight(j);
    }
  }

  FragColor = vec4(lights, 1.0); 

}
