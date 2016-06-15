#version 330 core
in vec3 Normal;
in vec3 Position;

out vec4 color;

uniform vec3 cameraPos;
uniform samplerCube texture_diffuse1;

void main()
{   
    vec3 I = normalize(Position - cameraPos);
	vec3 R = reflect(I, normalize(Normal));           
    color = texture(texture_diffuse1, R);
}