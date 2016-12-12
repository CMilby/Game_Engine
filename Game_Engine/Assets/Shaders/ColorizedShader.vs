#version 330 core

layout ( location = 0 ) in vec3 position;
layout ( location = 2 ) in vec3 normal;
layout ( location = 3 ) in vec3 color;

out vec3 color0;
out vec3 normal0;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main( void ) {
    color0 = color;
    normal0 = normal;
    gl_Position =  ( projection * view * model ) * vec4( position, 1.0 );
}

