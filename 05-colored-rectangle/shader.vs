#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;

out vec3 Color;

uniform mat4 MVP;

void main(){
  gl_Position =  MVP*vec4(position,0.0, 1.0);
  Color = color;
}

