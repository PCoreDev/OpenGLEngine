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
  vec3 position;  
  vec3 direction;
  float cutOff;
  
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  
  float constant;
  float linear;
  float quadratic;

  vec3 color;
}; 


out vec4 FragColor;

in vec3 position;
in vec3 normal;
in vec2 texCoords;

uniform vec3 light_position;

uniform vec3 camera_position;
uniform vec3 camera_direction;

uniform Material material;

uniform int texture_index;

uniform DirectionalLight directional_light;
uniform PointLight point_light[16];
uniform SpotLight spot_light[16];

uniform int point_light_count;
uniform int spot_light_count;


vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 view_dir) {
  vec3 light_direction = normalize(-light.direction);
  // diffuse shading
  float diff = max(dot(normal, light_direction), 0.0);
  
  // specular shading
  vec3 reflectDir = reflect(-light_direction, normal);

  vec3 ambient = vec3(0.0f);
  vec3 diffuse = vec3(0.0f);
  vec3 specular = vec3(0.0f);

  for(int i = 0; i < texture_index; i++){
    float spec = pow(max(dot(view_dir, reflectDir), 0.0), material.shininess[i]);
    
    // combine results
    ambient = light.ambient * vec3(texture(material.diffuse_texture[i], texCoords));
    diffuse = light.diffuse * diff * vec3(texture(material.diffuse_texture[i], texCoords));
    specular = light.specular * spec * vec3(texture(material.specular_texture[i], texCoords));
  }
  return (ambient + diffuse + specular) * light.color;
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_dir) {
  vec3 light_direction = normalize(light.position - frag_pos);
  // diffuse shading
  float diff = max(dot(normal, light_direction), 0.0);
  // specular shading
  vec3 reflectDir = reflect(-light_direction, normal);
  //float spec = pow(max(dot(view_dir, reflectDir), 0.0), material.shininess[0]);

  // attenuation
  float dist = length(light.position - frag_pos);
  float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

  vec3 ambient = vec3(0.0f);
  vec3 diffuse = vec3(0.0f);
  vec3 specular = vec3(0.0f);
  
  for(int i = 0; i < texture_index; i++){
    float spec = pow(max(dot(view_dir, reflectDir), 0.0), material.shininess[i]);
    
    // combine results
    ambient = light.ambient * vec3(texture(material.diffuse_texture[i], texCoords));
    diffuse = light.diffuse * diff * vec3(texture(material.diffuse_texture[i], texCoords));
    specular = light.specular * spec * vec3(texture(material.specular_texture[i], texCoords));
  }

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  return (ambient + diffuse + specular) * light.color;
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 frag_pos, vec3 view_dir){

  vec3 light_direction = normalize(light.position - frag_pos);
  float theta = dot(light_direction, normalize(-light.direction));

  

  if(theta > light.cutOff){
    vec3 result = vec3(0.0f);
    // diffuse shading
    float diff = max(dot(normal, light_direction), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-light_direction, normal);
    float spec = pow(max(dot(view_dir, reflectDir), 0.0), material.shininess[0]);

    // attenuation
    float dist = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

    vec3 ambient = vec3(0.0f);
    vec3 diffuse = vec3(0.0f);
    vec3 specular = vec3(0.0f);

    for(int i = 0; i < texture_index; i++){
      float spec = pow(max(dot(view_dir, reflectDir), 0.0), material.shininess[i]);
      
      // combine results
      ambient = light.ambient * vec3(texture(material.diffuse_texture[i], texCoords));
      diffuse = light.diffuse * diff * vec3(texture(material.diffuse_texture[i], texCoords));
      specular = light.specular * spec * vec3(texture(material.specular_texture[i], texCoords));
    }

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    result = (ambient + diffuse + specular) * light.color;
    return result;
  }else{
    vec3 result = vec3(0.0f);
    for(int i = 0; i < texture_index; i++){
      result += light.ambient * vec3(texture(material.diffuse_texture[i], texCoords));
    }
    return result;
  }
}

void main() {

  // properties
  vec3 norm = normalize(normal);
  //vec3 view_dir = normalize(camera_position - position);
  vec3 view_dir = normalize(camera_direction - position);

  vec3 result = vec3(0.0f);
  // phase 1: directional light
  //result += CalculateDirectionalLight(directional_light, norm, view_dir);

  // phase 2: point lights
  for(int i = 0; i < point_light_count; i++){
    result += CalculatePointLight(point_light[i], norm, position, view_dir);
  }

  // phase 3: spot lights
//  for(int i = 0; i < spot_light_count; i++){
//    result += CalculateSpotLight(spot_light[i], norm, position, view_dir);
//  }

  FragColor = vec4(result, 1.0);
}
