#version 330 core
layout (location = 3) in vec3 aSnowPos;
layout (location = 4) in vec2 aSnowTexCoord;
layout (location = 5) in mat4 aSnowInstanceMatrix;


out vec2 TexCoordSnow;

uniform mat4 view;
uniform mat4 projection;
uniform int type;

void main()
{
    gl_Position = projection * view * aSnowInstanceMatrix * vec4(aSnowPos, 1.0);
    TexCoordSnow = aSnowTexCoord;
}  