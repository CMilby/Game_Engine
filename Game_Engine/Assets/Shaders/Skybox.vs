#version 330

layout (location = 0) in vec3 position;

uniform mat4 projected;

out vec3 texCoord;

void main()
{
    vec4 worldPos = projected * vec4( position, 1.0f );
    gl_Position = worldPos.xyww;
    texCoord = position;
}