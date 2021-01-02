#version 330 core
out vec3 FragColor;

in vec3 ourColor;

void main()
{
    FragColor = ourColor;
}