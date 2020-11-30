#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;
layout (location = 2) in vec2 aOffset;

out vec3 Color;

uniform mat4 MVP;

void main(){
  gl_Position =  MVP*vec4(position+aOffset,0.0, 1.0);
  Color = color;
}

