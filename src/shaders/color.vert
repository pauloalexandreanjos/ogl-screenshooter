#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform vec2 myPosition;
uniform mat4 transform;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0) + vec4(myPosition, 0.0f, 0.0f) + transform[gl_VertexID];
    ourColor = aColor;
}