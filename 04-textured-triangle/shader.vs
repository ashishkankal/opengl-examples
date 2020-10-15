#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
uniform mat4 MVP;

out vec3 ourColor;
out vec2 TexCoord;

void main(){
  gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
}