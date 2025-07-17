#version 330 core
out vec4 FragColor; 
in vec2 TexCoord;

uniform sampler2D ourTexture;
  
void main()
{
   float ambientStrength = 0.5;
   vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);

   vec3 result = ambient * texture(ourTexture, TexCoord).rgb;
   FragColor = vec4(result, 1.0);
}