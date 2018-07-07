#version 300 es

layout (location=0) in lowp vec3 aPos;
layout (location=1) in lowp vec3 aNormal;
layout (location=2) in lowp vec2 aTexCoords;

out lowp vec2 TexCoords;
out lowp vec3 normal;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;  
    normal = aNormal;  
    gl_Position = projection * model * vec4(aPos, 1.0);
}
