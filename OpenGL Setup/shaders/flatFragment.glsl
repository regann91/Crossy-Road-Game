#version 330 core
out vec4 FragColor;
  
uniform vec4 colorVertex;

void main()
{
    FragColor = colorVertex;
} 