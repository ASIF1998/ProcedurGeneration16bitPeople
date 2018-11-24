#version 410

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

out vec3 Color;
out vec2 TexureCoord;

void main()
{
    Color = vec3(texCoord, 1.0);
    TexureCoord = texCoord;
    gl_Position = vec4(pos, 1.0);
}
