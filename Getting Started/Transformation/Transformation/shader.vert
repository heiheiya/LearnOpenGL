#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
uniform float yoffset;
uniform mat4 transform;
out vec4 vertexColor;
out vec2 TexCoord;
void main()
{
gl_Position = transform * vec4(position.x, position.y+yoffset,position.z,1.0);
vertexColor = vec4(color, 1.0f);
TexCoord = texCoord;
}