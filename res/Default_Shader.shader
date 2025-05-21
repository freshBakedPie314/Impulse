#vertex shader
#version 330 core

layout(location = 0)in vec4 a_Pos;
uniform mat4 u_model;
uniform mat4 u_view;
void main()
{
    gl_Position = u_view * u_model*a_Pos;
}

#fragment shader
#version 330 core

uniform vec4 u_color;
out vec4 Color;
void main()
{
    Color = u_color;
}