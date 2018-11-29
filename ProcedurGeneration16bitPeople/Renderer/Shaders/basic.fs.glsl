#version 410

in vec2 TexureCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
//    FragColor = texture(ourTexture, TexureCoord) * vec4(TexureCoord, 1.0, 1.0);
//    FragColor = mix(texture(ourTexture, TexureCoord), vec4(TexureCoord, 1.0, 1.0), 0.5);
    FragColor = texture(ourTexture, TexureCoord);
//    FragColor = vec4(TexureCoord, 1.0, 1.0);
}
