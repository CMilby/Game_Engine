#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec3 position0;
out vec2 texCoord0;
out vec3 normal0;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 worldPos = model * vec4( position, 1.0f );
    position0 = worldPos.xyz;
    gl_Position = projection * view * worldPos;
    texCoord0 = texCoord;
    
    mat3 normalMat = transpose( inverse( mat3( model ) ) );
    normal0 = normalMat * normal;
}