#version 330 core

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gSpecular;

in vec3 position0;
in vec2 texCoord0;
in vec3 normal0;

uniform sampler2D textureDiffuse;
uniform sampler2D textureSpecular;

void main()
{
    gPosition = position0;
    gNormal = normalize( normal0 );
    gSpecular.rgb = texture( textureDiffuse, texCoord0 ).rgb;
    gSpecular.a = texture( textureSpecular, texCoord0 ).r;
}