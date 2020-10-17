#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 4) out;
in vec4 gPos[];
in vec3 geo_color[];

out vec3 Color;

void main() {    
    Color =geo_color[2];
    gl_Position = gPos[0] + vec4(-0.75, -1.2, 0.0, 0.0); // 1:top   
    EmitVertex();
    Color =geo_color[0];
    gl_Position = gPos[0] + vec4(0.75,  -1.2, 0.0, 0.0); // 3:top-left
    EmitVertex();

    Color =geo_color[1];   
    gl_Position = gPos[1] + vec4( 0.0, 0.0, 0.0, 0.0); // 2:bottom-right
    EmitVertex();
    Color =geo_color[2];
    gl_Position = gPos[2] + vec4(0.0,  0.0, 0.0, 0.0); // 3:top-left
    EmitVertex();

    EndPrimitive();
}