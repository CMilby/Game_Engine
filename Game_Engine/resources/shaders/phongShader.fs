#version 330

const int MAX_POINT_LIGHTS = 5;
const int MAX_SPOT_LIGHTS = 5;

in vec2 texCoord0;
in vec3 normal0;
in vec3 worldPos0;

out vec4 fragColor;

struct BaseLight {
    vec3 color;
    float intensity;
};

struct DirectionalLight {
    BaseLight base;
    vec3 direction;
};

struct Attenuation {
    float constant;
    float linear;
    float exponent;
};

struct PointLight {
    BaseLight base;
    Attenuation atten;
    vec3 position;
    float range;
};

struct SpotLight {
    PointLight pointLight;
    vec3 direction;
    float cutoff;
};

uniform vec3 baseColor;
uniform vec3 eyePos;
uniform vec3 ambientLight;
uniform sampler2D sampler;

uniform float specularIntensity;
uniform float specularPower;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[ MAX_POINT_LIGHTS ];
uniform SpotLight spotLights[ MAX_SPOT_LIGHTS ];

vec4 CalcLight( BaseLight base, vec3 direction, vec3 normal ) {
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

vec4 CalcDirectionalLight( DirectionalLight light, vec3 normal ) {
    return CalcLight( light.base, -light.direction, normal );
}

vec4 CalcPointLight( PointLight light, vec3 normal ) {
    vec3 lightDirection = worldPos0 - light.position;
    float distance = length( lightDirection );
    
    if ( distance > light.range ) {
        return vec4( 0.0f, 0.0f, 0.0f, 0.0f );
    }
    
    lightDirection = normalize( lightDirection );
    
    vec4 color = CalcLight( light.base, lightDirection, normal );
    float atten = light.atten.constant +
                  light.atten.linear * distance +
                  light.atten.exponent * distance *
                  distance + 0.0001f;
    return color / atten;
}

vec4 CalcSpotLight( SpotLight light, vec3 normal ) {
    vec3 lightDirection = normalize( worldPos0 - light.pointLight.position );
    float spotFactor = dot( lightDirection, light.direction );
    
    vec4 color = vec4( 0.0f, 0.0f, 0.0f, 0.0f );
    
    if ( spotFactor > light.cutoff ) {
        color = CalcPointLight( light.pointLight, normal ) *
                ( 1.0f - ( 1.0f - spotFactor ) / ( 1.0f - light.cutoff ) );
    }
    
    return color;
}

void main() {
    vec4 totalLight = vec4( ambientLight, 1.0f );
    vec4 color = vec4( baseColor, 1.0f );
    vec4 textureColor = texture( sampler, texCoord0 );
    
    if ( textureColor != vec4( 0, 0, 0, 0 ) ) {
        color *= textureColor;
    }
    
    vec3 normal = normalize( normal0 );
    
    totalLight += CalcDirectionalLight( directionalLight, normal );
    
    for ( int i = 0; i < MAX_POINT_LIGHTS; i++ ) {
        if ( pointLights[ i ].base.intensity > 0 ) {
            totalLight += CalcPointLight( pointLights[ i ], normal );
        }
    }
    
    for ( int i = 0; i < MAX_SPOT_LIGHTS; i++ ) {
        if ( spotLights[ i ].pointLight.base.intensity > 0 ) {
            totalLight += CalcSpotLight( spotLights[ i ], normal );
        }
    }
    
    fragColor = color * totalLight;
    
    /*vec4 ambientColor = vec4( directionalLight.base.color * directionalLight.base.ambientIntensity, 1.0f );
    vec3 lightDirection = directionalLight.direction;
    vec3 normal = normalize( normal0 );
    
    float diffseFactor = dot( normal, lightDirection );
    
    vec4 diffuseColor = vec4( 0, 0, 0, 0 );
    vec4 specularColor = vec4( 0, 0, 0, 0 );
    
    if ( diffseFactor > 0 ) {
        diffuseColor = vec4( directionalLight.base.color * directionalLight.base.diffuseIntensity * diffseFactor, 1.0f );
        
        vec3 vertexToEye = normalize( eyePos - worldPos0 );
        vec3 lightReflect = normalize( reflect( -directionalLight.direction, normal ) );
        float specularFactor = dot( vertexToEye, lightReflect );
        if ( specularFactor > 0 ) {
            specularFactor = pow( specularFactor, specularPower );
            specularColor = vec4( directionalLight.base.color * specularIntensity * specularFactor, 1.0f );
        }
    }
    
    fragColor = texture( sampler, texCoord0 ) *
                ( ambientColor + diffuseColor + specularColor );*/
}

    /*vec4 color = vec4( baseColor, 1.0 );
    vec4 textureColor = texture( sampler, texCoord0 );
  
    if ( textureColor != vec4( 0, 0, 0, 0 ) ) {
        color *= textureColor;
    }
    
    fragColor = color *
                vec4( directionalLight.color, 1.0f ) *
                directionalLight.intensity;
                // vec4( directionalLight.color, 1.0f ) *
                // sdirectionalLight.intensity;
}

/*const int MAX_POINT_LIGHTS = 5;
const int MAX_SPOT_LIGHTS = 5;

in vec2 texCoord0;
in vec3 normal0;
in vec3 worldPos0;

out vec4 fragColor;

struct BaseLight
{
    vec3 color;
    float intensity;
};

struct DirectionalLight
{
    BaseLight base;
    vec3 direction;
};

struct Attenuation
{
    float constant;
    float linear;
    float exponent;
};

struct PointLight
{
    BaseLight base;
    Attenuation atten;
    vec3 position;
    float range;
};

struct SpotLight
{
    PointLight pointLight;
    vec3 direction;
    float cutoff;
};

uniform vec3 baseColor;
uniform vec3 eyePos;
uniform vec3 ambientLight;
uniform sampler2D sampler;

uniform float specularIntensity;
uniform float specularPower;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

vec4 calcLight(BaseLight base, vec3 direction, vec3 normal)
{
    float diffuseFactor = dot(normal, -direction);
    
    vec4 diffuseColor = vec4(0,0,0,0);
    vec4 specularColor = vec4(0,0,0,0);
    
    if(diffuseFactor > 0)
    {
        diffuseColor = vec4(base.color, 1.0) * base.intensity * diffuseFactor;
        
        vec3 directionToEye = normalize(eyePos - worldPos0);
        vec3 reflectDirection = normalize(reflect(direction, normal));
        
        float specularFactor = dot(directionToEye, reflectDirection);
        specularFactor = pow(specularFactor, specularPower);
        
        if(specularFactor > 0)
        {
            specularColor = vec4(base.color, 1.0) * specularIntensity * specularFactor;
        }
    }
    
    return diffuseColor + specularColor;
}

vec4 calcDirectionalLight(DirectionalLight directionalLight, vec3 normal)
{
    return calcLight(directionalLight.base, -directionalLight.direction, normal);
}

vec4 calcPointLight(PointLight pointLight, vec3 normal)
{
    vec3 lightDirection = worldPos0 - pointLight.position;
    float distanceToPoint = length(lightDirection);
    
    if(distanceToPoint > pointLight.range)
        return vec4(0,0,0,0);
    
    lightDirection = normalize(lightDirection);
    
    vec4 color = calcLight(pointLight.base, lightDirection, normal);
    
    float attenuation = pointLight.atten.constant +
    pointLight.atten.linear * distanceToPoint +
    pointLight.atten.exponent * distanceToPoint * distanceToPoint +
    0.0001;
    
    return color / attenuation;
}

vec4 calcSpotLight(SpotLight spotLight, vec3 normal)
{
    vec3 lightDirection = normalize(worldPos0 - spotLight.pointLight.position);
    float spotFactor = dot(lightDirection, spotLight.direction);
    
    vec4 color = vec4(0,0,0,0);
    
    if(spotFactor > spotLight.cutoff)
    {
        color = calcPointLight(spotLight.pointLight, normal) *
        (1.0 - (1.0 - spotFactor)/(1.0 - spotLight.cutoff));
    }
    
    return color;
}

void main()
{
    vec4 totalLight = vec4(ambientLight,1);
    vec4 color = vec4(baseColor, 1);
    vec4 textureColor = texture(sampler, texCoord0.xy);
    
    if(textureColor != vec4(0,0,0,0))
        color *= textureColor;
    
    vec3 normal = normalize(normal0);
    
    totalLight += calcDirectionalLight(directionalLight, normal);
    
    for(int i = 0; i < MAX_POINT_LIGHTS; i++)
        if(pointLights[i].base.intensity > 0)
            totalLight += calcPointLight(pointLights[i], normal);
    
    for(int i = 0; i < MAX_SPOT_LIGHTS; i++)
        if(spotLights[i].pointLight.base.intensity > 0)
            totalLight += calcSpotLight(spotLights[i], normal);
    
    fragColor = color * totalLight;
}*/