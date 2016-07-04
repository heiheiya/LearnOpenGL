#version 330 core

out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
	vec2 TexCoords;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
}fs_in;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D depthMap;

uniform bool parallax;
uniform float height_scale;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{
    const float minLayers = 10;
	const float maxLayers = 20;
	float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));
	float layerDepth = 1.0/numLayers;
	float currentLayerDepth = 1.0;

	vec2 P = viewDir.xy/viewDir.z * height_scale;
	vec2 deltaTexCoords = P/numLayers;

	vec2 currentTexCoords = texCoords;
	float currentDepthMapValue = texture(depthMap, currentTexCoords).r;

	while(currentLayerDepth < currentDepthMapValue)
	{
	    currentTexCoords -= deltaTexCoords;
		currentDepthMapValue = texture(depthMap, currentTexCoords).r;
		currentLayerDepth += layerDepth;
	}
	return currentTexCoords;
}

void main()
{     
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
	vec2 texCoords = fs_in.TexCoords;
	if(parallax)
	    texCoords = ParallaxMapping(fs_in.TexCoords, viewDir);
		         
	vec3 normal = texture(normalMap, texCoords).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	vec3 color = texture(diffuseMap, texCoords).rgb;

	vec3 ambient = 0.1 * color;

	vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
	float diff = max(dot(lightDir, normal), 0.0f);
	vec3 diffuse = diff * color;

	vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
	vec3 specular = spec * vec3(0.2) ;

	FragColor = vec4(ambient + diffuse + specular, 1.0f);
}