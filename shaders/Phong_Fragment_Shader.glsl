#version 330 core

#define MAX_LIGHTS 8

struct LightData {
    vec3 pos;     
    vec3 color;    
};

uniform int numLights;           
uniform LightData lights[MAX_LIGHTS];

uniform vec3 uViewPos;           
uniform vec3 objectColor;         
uniform float ambientStrength;    
uniform float specularStrength;   
uniform float shininess;          

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

void main()
{
    vec3 norm    = normalize(Normal);
    vec3 viewDir = normalize(uViewPos - FragPos);

    vec3 ambient = ambientStrength * objectColor;

    vec3 totalDiffuse  = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);


    for(int i = 0; i < numLights; i++)
    {
        vec3 lightDir = normalize(lights[i].pos - FragPos);

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse  = diff * lights[i].color;

        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        vec3 specular   = specularStrength * spec * lights[i].color;

        totalDiffuse  += diffuse;
        totalSpecular += specular;
    }

    vec3 result = (ambient + totalDiffuse + totalSpecular) * objectColor;
    FragColor = vec4(result, 1.0);
}
