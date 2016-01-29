#version 330 core

layout (location = 0) in vec3 position;

out vec3 position0;

uniform mat4 transformProjected;

void main()
{
    gl_Position = transformProjected * vec4( position, 1.0 );
    position0 = position;
}