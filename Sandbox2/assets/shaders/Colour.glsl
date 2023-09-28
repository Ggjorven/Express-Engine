#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;

void main()
{
    gl_Position = vec4(a_Position, 1.0);
}

#shader fragment
#version 330 core

out vec4 FragColor;

uniform vec4 u_Colour;

void main()
{
    FragColor = u_Colour;
}
