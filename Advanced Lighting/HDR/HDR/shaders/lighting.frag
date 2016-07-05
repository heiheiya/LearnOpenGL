#version 330 core

out vec4 FragColor;

in VS_OUT{
    vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
}fs_in;


uniform sampler2D woodTexture;

uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];
uniform vec3 viewPos;

vec3 BlinnPhong(vec3 normal, vec3 fragPos, vec3 lightPos, vec3 lightColor)
{
    vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = 0.0;
	vec3 halfwayDir = normalize(lightDir + viewDir);
	spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0f);
	vec3 specular = spec * lightColor;

	return diffuse + specular;
}

void main()
{
    vec3 color = texture(woodTexture, fs_in.TexCoords).rgb;

	vec3 lighting = vec3(0.0);
	for(int i = 0; i < 4; ++i)
	    lighting += BlinnPhong(normalize(fs_in.Normal), fs_in.FragPos, lightPositions[i], lightColors[i]);
    color *= lighting;

	FragColor = vec4(color, 1.0f);
}