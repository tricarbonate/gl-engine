#version 330 core

#define NR_POINT_LIGHTS 10 

in vec3 fragNorm;
in vec3 fragPos;
in vec2 fragTex;

out vec4 colour;

struct Material{
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

struct DirLight{
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct PointLight {
  vec3 position;

  float constant;
  float linear;
  float quadratic;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};


uniform int pointLightCount;
uniform DirLight dirLight;
uniform vec3 viewPos;

uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform Material material;

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main(){
  vec3 norm = normalize(fragNorm);
  vec3 viewDir = normalize(viewPos - fragPos);

  vec3 result = vec3(0.0, 0.0, 0.0);
  result = calcDirLight(dirLight, norm, viewDir);

  if(pointLightCount != 0 ){
    for(int j = 0; j < pointLightCount; j++){
      result += calcPointLight(pointLights[j], norm, fragPos, viewDir);
    }
  }
  

  colour = vec4(result, 1.0); 
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
  vec3 lightDir = normalize(light.position - fragPos);
  // diffuse shading
  float diff = max(dot(normal, lightDir), 0.0);
  // specular shading
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  // attenuation
  float distance    = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance +
           light.quadratic * (distance * distance));
  // combine results
  vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, fragTex));
  vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, fragTex));
  vec3 specular = light.specular * spec * vec3(texture(material.specular, fragTex));
  ambient  *= attenuation;
  diffuse  *= attenuation;
  specular *= attenuation;
  return (ambient + diffuse + specular);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir){
  vec3 lightDir = normalize(-light.direction);
  // diffuse shading
  float diff = max(dot(normal, lightDir), 0.0);
  // specular shading
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  // combine results
  vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, fragTex));
  vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, fragTex));
  vec3 specular = light.specular * spec * vec3(texture(material.specular, fragTex));
  return (ambient + diffuse + specular);
}

