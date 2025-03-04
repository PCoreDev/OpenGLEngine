#version 460 core

struct Material {
    sampler2D diffuse_texture;  // map_Kd
    sampler2D ambient_texture;  // map_Ka
    sampler2D specular_texture; // map_Ks
    sampler2D alpha_texture;    // map_d
    sampler2D bump_texture;     // map_bump
    sampler2D normal_texture;   // map_Ns

    vec3 ambient_color;
    vec3 diffuse_color;
    vec3 specular_color;
    float shininess;
    float dissolve;
    float optical_density;
    int illumination;
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
    float outerCutOff;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
    vec3 color;
};

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 camera_position;

uniform Material material;

uniform DirectionalLight directional_light;
uniform PointLight point_light[16];
uniform SpotLight spot_light[16];

uniform int point_light_count;
uniform int spot_light_count;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 view_dir) {
    vec3 light_direction = normalize(-light.direction);
    float diff = max(dot(normal, light_direction), 0.0);
    vec3 reflectDir = reflect(-light_direction, normal);
    float spec = pow(max(dot(view_dir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse_texture, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse_texture, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular_texture, TexCoords));

    return (ambient + diffuse + specular) * light.color;
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_dir) {
    vec3 light_direction = normalize(light.position - frag_pos);
    float diff = max(dot(normal, light_direction), 0.0);
    vec3 reflectDir = reflect(-light_direction, normal);
    float spec = pow(max(dot(view_dir, reflectDir), 0.0), material.shininess);

    float dist = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

    vec3 ambient = light.ambient * vec3(texture(material.diffuse_texture, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse_texture, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular_texture, TexCoords));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular) * light.color;
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 frag_pos, vec3 view_dir) {
    vec3 light_direction = normalize(light.position - frag_pos);
    float theta = dot(light_direction, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    if (theta > light.outerCutOff) {
        float diff = max(dot(normal, light_direction), 0.0);
        vec3 reflectDir = reflect(-light_direction, normal);
        float spec = pow(max(dot(view_dir, reflectDir), 0.0), material.shininess);

        float dist = length(light.position - frag_pos);
        float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

        vec3 ambient = light.ambient * vec3(texture(material.diffuse_texture, TexCoords));
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse_texture, TexCoords));
        vec3 specular = light.specular * spec * vec3(texture(material.specular_texture, TexCoords));

        ambient *= attenuation;
        diffuse *= attenuation * intensity;
        specular *= attenuation * intensity;

        return (ambient + diffuse + specular) * light.color;
    } else {
        return light.ambient * vec3(texture(material.diffuse_texture, TexCoords));
    }
}

void main() {
    vec3 norm = normalize(Normal);

    vec3 view_dir = normalize(camera_position - FragPos);

    vec3 result = vec3(0.0f);

    // directional light
    result += CalculateDirectionalLight(directional_light, norm, view_dir);

    // point lights
    for (int i = 0; i < point_light_count; i++) {
        result += CalculatePointLight(point_light[i], norm, FragPos, view_dir);
    }

    // spot lights
    for (int i = 0; i < spot_light_count; i++) {
        result += CalculateSpotLight(spot_light[i], norm, FragPos, view_dir);
    }

    FragColor = vec4(result, 1.0);
}