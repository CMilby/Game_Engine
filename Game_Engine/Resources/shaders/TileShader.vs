#version 330

layout ( location = 0 ) in vec4 position;

out vec4 texCoord0;

uniform mat4 mvp;

void main( void ) {
	texCoord0 = position;
	gl_Position = mvp * vec4( position.xyz, 1.0 );
}