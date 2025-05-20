#vertex shader
#version 330 core

layout(location = 0)in vec4 a_Pos;

void main()
{
    gl_Position = a_Pos;
}

#fragment shader
#version 330 core

uniform vec4 u_color;
out vec4 Color;
void main()
{
    Color = u_color;
}