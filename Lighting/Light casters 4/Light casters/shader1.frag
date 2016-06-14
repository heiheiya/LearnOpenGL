#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
	//sampler2D emission;
    float shininess;
};

struct Light {
    vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constant;
	float linear;
	float quadratic;
	float cutOff;
	float outerCutOff;
};

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
out vec4 color;

uniform vec3 viewPos;

uniform Material material;
uniform Light light;

void main()
{
   vec3 lightDir = normalize(light.position - FragPos);
   float theta = dot(lightDir, normalize(-light.direction));
   float epsilon = light.cutOff - light.outerCutOff;
   float intensity = clamp((theta - light.outerCutOff)/epsilon, 0.0, 1.0);
   vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords));
   vec3 norm = normalize(Normal);

   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
       
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);  
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); 
   vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

   float distance = length(light.position - FragPos);
   float attenuation = 1.0f/(light.constant + light.linear * distance + light.quadratic * distance * distance);

   diffuse *= intensity;
   specular *= intensity;

   ambient  *= attenuation;
   diffuse *= attenuation;
   specular *= attenuation;

   color = vec4(ambient + diffuse + specular, 1.0f); 
}