#version 300 es

out lowp vec4 FragColor;

in lowp vec2 TexCoords;
in lowp vec3 normal;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;

void main()
{   
    FragColor = texture(texture_diffuse1, TexCoords) + texture(texture_diffuse2, TexCoords);
}
