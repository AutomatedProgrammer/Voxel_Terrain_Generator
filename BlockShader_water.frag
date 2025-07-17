#version 330 core
out vec4 waterFragColor; 
in vec2 aWaterTexCoord;

uniform sampler2D ourWaterTexture;
  
void main()
{
   float ambientStrength = 0.5;
   vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);

   vec3 result = ambient * texture(ourWaterTexture, aWaterTexCoord).rgb;
   waterFragColor = vec4(result, 1.0);
}