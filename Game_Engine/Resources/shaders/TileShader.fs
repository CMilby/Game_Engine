
#version 330

in vec4 texCoord0;

uniform sampler2DArray sampler;

out vec4 fragColor;

void main( void ) {
	fragColor = texture( sampler, vec3( texCoord0.xy, texCoord0.w ) );
}