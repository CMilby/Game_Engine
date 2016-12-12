#version 330 core

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

uniform vec3 ambientLight;
uniform DirectionalLight directionalLight;

vec4 CalcLight( BaseLight p_base, vec3 p_direction, vec3 p_normal ) {
    float diffuseFactor = dot( p_normal, -p_direction );
    
    vec4 diffuseColor = vec4( 0.0f, 0.0f, 0.0f, 0.0f );
    vec4 specularColor = vec4( 0.0f, 0.0f, 0.0f, 0.0f );
    
    if ( diffuseFactor > 0 ) {
        diffuseColor = vec4( p_base.color, 1.0f ) * p_base.intensity * diffuseFactor;
        
        // vec3 directionToEye = normalize( eyePos - worldPos0 );
        // vec3 reflectDirection = normalize( reflect(  direction, normal ) );
        
        // float specularFactor = dot( directionToEye, reflectDirection );
        // specularFactor = pow( specularFactor, specularPower );
        
        // if ( specularFactor > 0 ) {
        //    specularColor = vec4( base.color, 1.0f ) * specularIntensity * specularFactor;
        // }
    }
    
    return diffuseColor + specularColor;
}

vec4 CalcDirectionalLight( DirectionalLight p_light, vec3 p_normal ) {
    return CalcLight( p_light.base, -p_light.direction, p_normal );
}

void main( void ) {
    vec4 totalLight = vec4( ambientLight, 1.0f );
    vec4 color = vec4( color0, 1.0f );
    
    vec3 normal = normalize( normal0 );
    totalLight += CalcDirectionalLight( directionalLight, normal );
    
    fragColor = color; // * totalLight;
}
