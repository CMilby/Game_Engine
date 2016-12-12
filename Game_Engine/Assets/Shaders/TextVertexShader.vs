#version 330

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;

out vec2 texCoord0;

void main()
{
    vec2 vertexPos = position - vec2( 400, 300 );
    vertexPos /= vec2( 400,300 );
    gl_Position =  vec4( vertexPos, 0, 1 );
    
    texCoord0 = texCoord;
}

