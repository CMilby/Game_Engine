#version 330

layout ( location = 0 ) in vec4 position;
layout ( location = 1 ) in vec2 texCoord;

out vec3 texCoord0;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main( void ) {
	texCoord0 = vec3( texCoord, position.w );
	gl_Position = ( projection * view * model ) * vec4( position.xyz, 1.0 );
}