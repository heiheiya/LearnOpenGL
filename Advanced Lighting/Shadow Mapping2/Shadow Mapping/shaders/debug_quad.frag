#version 330 core

in vec2 TexCoords;

out vec4 color;

uniform sampler2D depthMap;
uniform float near_plane;
uniform float far_plane;

void main()
{            
    float depthValue = texture(depthMap, TexCoords).r;
	//if(depthValue > near_plane && depthValue < far_plane)
	    color = vec4(vec3(depthValue), 1.0f);
}