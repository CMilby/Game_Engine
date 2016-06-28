#version 330 core

in vec2 texCoord0;

uniform sampler2D sampler;

out vec4 fragColor;

void main( void ) {
	fragColor = texture( sampler, texCoord0 );
}