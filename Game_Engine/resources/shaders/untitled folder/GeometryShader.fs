#version 330

layout (location = 0) out vec3 WorldPosOut;
layout (location = 1) out vec3 DiffuseOut;
layout (location = 2) out vec3 NormalOut;
layout (location = 3) out vec3 TexCoordOut;

in vec3 WorldPos0;
in vec2 TexCoord0;
in vec3 Normal0;

uniform sampler2D gColorMap;

void main()
{
    WorldPosOut = WorldPos0;
    DiffuseOut = texture( gColorMap, TexCoord0 ).xyz;
    NormalOut = normalize( Normal0 );
    TexCoordOut = vec3( TexCoord0, 0.0 );
}