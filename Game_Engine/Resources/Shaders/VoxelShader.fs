#version 330

in vec4 texCoord0;

out vec4 fragColor;

uniform sampler2DArray sampler;

void main( void ) {
	fragColor = texture( sampler, vec3( texCoord0.yz, texCoord0.w ) );
}