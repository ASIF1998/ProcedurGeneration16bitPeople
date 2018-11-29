#version 410

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

out vec2 TexureCoord;

mat3 ratate(float a)
{
    return mat3 (
        cos(a), -sin(a), 0.0,
        sin(a), -cos(a), 0.0,
        0.0, 0.0, 1.0
    );
}

uniform float a;

void main()
{
    TexureCoord = texCoord;
    gl_Position = vec4(ratate(0.0001) * pos, 1.0);
}
