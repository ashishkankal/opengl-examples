#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
out vec3 fragmentColor;

uniform mat4 MVP;

void main(){
  gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
  if(gl_Position.x<=-0.2){
  fragmentColor = vec3(1.0,0.64,0.0);
  }
  
  if (gl_Position.x>-0.2 && gl_Position.x<0.0){
    fragmentColor = vec3(1.0,1.0,1.0);
  }
  if (gl_Position.x==0.0){
    fragmentColor = vec3(0.0,0.0,1.0);
  }
    if (gl_Position.x>0.0 && gl_Position.x<=0.2){
    fragmentColor = vec3(1.0,1.0,1.0);
  }
  if(gl_Position.x>0.2){
    fragmentColor = vec3(0.0,1.0,0.0);
  }


}