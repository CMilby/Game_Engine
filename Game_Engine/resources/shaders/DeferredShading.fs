#version 330 core

in vec2 texCoords0;

out vec4 fragColor;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gSpecular;

struct Light {
    vec3 position;
    vec3 color;
    
    float linear;
    float quadratic;
};

const int NR_LIGHTS = 32;
uniform Light lights[ NR_LIGHTS ];
uniform vec3 viewPos;

void main()
{
    vec3 FragPos = texture( gPosition, texCoords0 ).rgb;
    vec3 Normal = texture( gNormal, texCoords0 ).rgb;
    vec3 Diffuse = texture( gSpecular, texCoords0 ).rgb;
    float Specular = texture( gSpecular, texCoords0 ).a;
    
    vec3 lighting = Diffuse * 0.5;
    vec3 viewDir = normalize( viewPos - FragPos );
    
    for ( int i = 0; i < NR_LIGHTS; i++ ) {
        vec3 lightDir = normalize( lights[ i ].position - FragPos );
        vec3 diffuse = max( dot( Normal, lightDir ), 0.0 ) * Diffuse * lights[ i ].color;
        
        vec3 halfDir = normalize( lightDir + viewDir );
        float spec = pow( max( dot( Normal, halfDir ), 0.0 ), 16.0 );
        vec3 specular = lights[ i ].color * spec * Specular;
        
        float distance = length( lights[ i ].position - FragPos );
        float atten = 1.0 / ( 1.0 + lights[ i ].linear * distance + lights[ i ].quadratic * distance * distance );
        diffuse *= atten;
        specular *= atten;
        lighting += diffuse + specular;
    }
    fragColor = vec4( lighting, 1.0 );
}