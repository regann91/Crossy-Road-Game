#version 330 core
out vec4 FragColor;

in vec3 elemColor;
in vec2 elemTexCoord;

uniform sampler2D tex;
uniform bool texturingActive;

void main()
{
    FragColor = texturingActive ? vec4(elemColor * texture(tex, elemTexCoord).xyz, 1) : vec4(elemColor, 1);
}