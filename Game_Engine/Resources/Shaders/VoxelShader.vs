#version 330

layout ( location = 0 ) in vec4 position;

out vec4 texCoord0;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main( void ) {
	texCoord0 = position;
	gl_Position = ( projection * view * model ) * vec4( position.xyz, 1.0 );
}