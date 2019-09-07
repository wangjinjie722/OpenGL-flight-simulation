//片元着色器代码
#version 330 core
struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform Material material;
uniform Light light;

void main()
{
    //环境光
    vec3 ambient = lightColor * material.ambient * light.ambient;

    //漫反射光
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);  

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * (diff * material.diffuse) * light.diffuse;

    //镜面高光
    vec3 viewDir = normalize( - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lightColor * (spec * material.specular) * light.specular;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0f);
}