#version 400 core

in vec3 fragColor;
flat in vec3 flatColor;

out vec4 colour;

uniform bool isFlat;

void main(){
  if(isFlat){
    colour = vec4(flatColor, 1.0);
  }
  else{
    colour = vec4(fragColor, 1.0);
  }
}

