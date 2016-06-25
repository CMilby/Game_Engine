
#version 330

in vec4 texCoord0;

uniform sampler2DArray sampler;
// uniform sampler2D sampler;

out vec4 fragColor;

void main( void ) {
	// fragColor = texture( sampler, vec2( ( fract( texCoord0.x ) + mod( texCoord0.w, 16 ) ) / 16.0, ( int( texCoord0.w ) / 16 ) / 16.0 ) );
	fragColor = texture( sampler, vec3( texCoord0.xy, texCoord0.w ) );
}