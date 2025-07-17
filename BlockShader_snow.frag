#version 330 core
out vec4 SnowFragColor; 
in vec2 aSnowTexCoord;

uniform sampler2D ourSnowTexture;
  
void main()
{
   float ambientStrength = 0.5;
   vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);

   vec3 result = ambient * texture(ourSnowTexture, aSnowTexCoord).rgb;
   SnowFragColor = vec4(result, 1.0);
}