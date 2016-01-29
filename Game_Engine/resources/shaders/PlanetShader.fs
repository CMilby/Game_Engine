#version 330 core

out vec4 fragColor;

in vec3 position0;

void main()
{
    fragColor = vec4( position0, 1.0 );
}