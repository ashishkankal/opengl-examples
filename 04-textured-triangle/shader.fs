#version 330 core
out vec4 color;
uniform vec4 ourColor; 
// texture sampler
uniform sampler2D texture1;
in vec2 TexCoord;

void main(){
  color = vec4(1.0, 0.0, 0.0, 1.0);
}