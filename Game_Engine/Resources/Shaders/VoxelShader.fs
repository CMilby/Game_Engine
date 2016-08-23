#version 330

in vec3 texCoord0;

out vec4 fragColor;

uniform sampler2DArray sampler;

void main( void ) {
	fragColor = texture( sampler, vec3( texCoord0.xy, texCoord0.z ) );
	
	if ( fragColor.a < 0.5 ) {
		discard;
	}
}