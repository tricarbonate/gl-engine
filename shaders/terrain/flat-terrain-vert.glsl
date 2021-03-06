#version 330

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNorm;
layout(location = 2) in vec3 inColor;

out vec3 fragPos;
out vec3 fragNorm;
out vec3 fragColor;

uniform mat4 mvp;
uniform mat4 model;

void main(){

  gl_Position = mvp * vec4(inPos, 1.0);
  fragPos = vec3(model * vec4(inPos, 1.0));
  fragNorm = mat3(transpose(inverse(model))) * inNorm;
  fragColor = inColor;
}

