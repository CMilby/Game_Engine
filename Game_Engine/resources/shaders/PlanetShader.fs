#version 330

in vec3 worldPos0;
in vec3 color0;
in vec3 normal0;

out vec4 fragColor;

struct BaseLight {
    vec3 color;
    float intensity;
};

struct DirectionalLight {
    BaseLight base;
    vec3 direction;
};

uniform vec3 baseColor;
uniform vec3 eyePos;
uniform vec3 ambientLight;

uniform float specularIntensity;
uniform float specularPower;

uniform DirectionalLight directionalLight;

vec4 CalcLight( BaseLight base, vec3 direction, vec3 normal )
{
    float diffuseFactor = dot( normal, -direction );
    
    vec4 diffuseColor = vec4( 0.0f, 0.0f, 0.0f, 0.0f );
    vec4 specularColor = vec4( 0.0f, 0.0f, 0.0f, 0.0f );
    
    if ( diffuseFactor > 0 ) {
        diffuseColor = vec4( base.color, 1.0f ) * base.intensity * diffuseFactor;
        
        vec3 directionToEye = normalize( eyePos - worldPos0 );
        vec3 reflectDirection = normalize( reflect(  direction, normal ) );
        
        float specularFactor = dot( directionToEye, reflectDirection );
        specularFactor = pow( specularFactor, specularPower );
        
        if ( specularFactor > 0 ) {
            specularColor = vec4( base.color, 1.0f ) * specularIntensity * specularFactor;
        }
    }
    return diffuseColor + specularColor;
}

vec4 CalcDirectionalLight( DirectionalLight light, vec3 normal )
{
    return CalcLight( light.base, -light.direction, normal );
}

void main()
{
    vec4 totalLight = vec4( ambientLight, 1.0f );
    vec4 color = vec4( baseColor, 1.0f );
    vec4 textureColor = vec4( color0, 1.0f );
    
    if ( textureColor != vec4( 0, 0, 0, 0 ) ) {
        color *= textureColor;
    }
    
    vec3 normal = normalize( normal0 );
    
    totalLight += CalcDirectionalLight( directionalLight, normal );
    
    fragColor = color * totalLight;
}

