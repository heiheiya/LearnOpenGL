#version 330 core
layout(location = 0) in vec3 position;
layout (location = 1) in vec3 color;
uniform float yoffset;
out vec4 vertexColor;
void main()
{
gl_Position = vec4(position.x, position.y+yoffset,position.z,1.0);
vertexColor = gl_Position;
}