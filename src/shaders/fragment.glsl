#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D texture_diffuse1;
uniform sampler2D texData;
uniform sampler2D texData2;

uniform float vbty;
void main()
{
    FragColor =  texture(texture_diffuse1, TexCoords) * vbty;
} 