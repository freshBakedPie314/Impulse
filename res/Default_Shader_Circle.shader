#vertex shader
#version 330 core

layout(location = 0)in vec4 a_Pos;
out vec2 localPos;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
void main()
{
    gl_Position = u_projection * u_view * u_model * a_Pos;
    localPos = a_Pos.xy;
}

#fragment shader
#version 330 core

out vec4 Color;
in vec2 localPos;
uniform vec4 u_color;
void main()
{
    float dist = length(localPos * 2.0);
    float alpha = 1.0 - smoothstep(0.99, 1.0, dist);
    Color = vec4(u_color.xyz , alpha); // Ignores u_color.a
}