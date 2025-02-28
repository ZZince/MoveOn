#define MAX_LIGHTS 8

struct LightData {
    vec3 pos;      
    vec3 color;    
};

uniform int numLights;
uniform LightData lights[MAX_LIGHTS];

in vec3 Normal;
in vec3 FragPos;

uniform vec3  uViewPos;        
uniform vec3  objectColor;     
uniform float ambientStrength; 
uniform float specularStrength;
uniform float shininess;

uniform float edgeThreshold;

out vec4 FragColor;

void main()
{
    vec3 norm    = normalize(Normal);
    vec3 viewDir = normalize(uViewPos - FragPos);

    float ndotv = dot(norm, viewDir);
    if(ndotv < edgeThreshold)
    {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
        return;
    }

    vec3 ambient = ambientStrength * objectColor;

    vec3 totalDiffuse  = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    for(int i = 0; i < numLights; i++)
    {
        vec3 lightDir = normalize(lights[i].pos - FragPos);

        float diff = max(dot(norm, lightDir), 0.0);

        float diffuseLevel = 0.0;
        if      (diff > 0.75) diffuseLevel = 1.0;
        else if (diff > 0.50) diffuseLevel = 0.6;
        else if (diff > 0.25) diffuseLevel = 0.3;

        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

        if(spec > 0.5) spec = 1.0;
        else           spec = 0.0;

        vec3 diffuse  = lights[i].color * diffuseLevel;
        vec3 specular = lights[i].color * specularStrength * spec;

        totalDiffuse  += diffuse;
        totalSpecular += specular;
    }

    vec3 finalColor = (ambient + totalDiffuse + totalSpecular) * objectColor;

    FragColor = vec4(finalColor, 1.0);
}
