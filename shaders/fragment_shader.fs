#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D frameTex;

void main()
{
	FragColor = texture(frameTex, TexCoord);
	FragColor = FragColor.zyxw;
	//FragColor *= vec4(TexCoord, 1.0, 1.0);
}
