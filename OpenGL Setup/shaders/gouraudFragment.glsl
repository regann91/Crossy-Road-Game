#version 330 core
out vec4 FragColor;

in vec4 elemColor;

void main()
{
    FragColor = elemColor;
}