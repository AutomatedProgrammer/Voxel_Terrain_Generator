#version 330 core
layout (location = 6) in vec3 aWaterPos;
layout (location = 7) in vec2 aWaterTexCoord;
layout (location = 8) in mat4 aWaterInstanceMatrix;


out vec2 TexCoordwater;

uniform mat4 view;
uniform mat4 projection;
uniform int type;

void main()
{
    gl_Position = projection * view * aWaterInstanceMatrix * vec4(aWaterPos, 1.0);
    TexCoordwater = aWaterTexCoord;
}  