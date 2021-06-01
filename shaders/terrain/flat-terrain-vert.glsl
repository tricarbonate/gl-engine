#version 400 core 

#define NR_POINT_LIGHTS 500

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNorm;
layout(location = 2) in vec3 inColor;

out vec3 fragPos;
out vec3 fragNorm;
out vec3 fragColor;

flat out vec3 flatColor;

uniform mat4 mvp;
uniform mat4 model;

struct PointLight {
  vec3 position;

  float constant;
  float linear;
  float quadratic;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct DirLight{
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirLight dirLight;
uniform int pointLightCount;
uniform vec3 viewPos;

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main(){

  gl_Position = mvp * vec4(inPos, 1.0);
  fragPos = vec3(model * vec4(inPos, 1.0));
  fragNorm = mat3(transpose(inverse(model))) * inNorm;

  vec3 norm = normalize(fragNorm);
  vec3 viewDir = normalize(viewPos - inPos);

  fragColor = inColor * calcDirLight(dirLight, norm, viewDir);
  for(int i = 0; i < pointLightCount; i++){
    fragColor += calcPointLight(pointLights[i], norm, fragPos, viewDir);
  }

  flatColor = fragColor;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
  vec3 lightDir = normalize(light.position - fragPos);
  // diffuse shading
  float diff = max(dot(normal, lightDir), 0.0);
  // specular shading
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
  // attenuation
  float distance    = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance +
           light.quadratic * (distance * distance));
  // combine results
  vec3 ambient  = light.ambient;
  vec3 diffuse  = light.diffuse  * diff;
  vec3 specular = light.specular * spec;
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
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
  // combine results
  vec3 ambient  = light.ambient;
  vec3 diffuse  = light.diffuse  * diff;
  vec3 specular = light.specular * spec;
  return (ambient + diffuse + specular);
}

