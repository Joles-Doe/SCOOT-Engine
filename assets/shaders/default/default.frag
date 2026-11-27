#version 450 core

uniform sampler2D uTexture;

in vec2 vTextureCoord;

out vec4 oFragColor;

void main()
{
	vec4 tex = texture(uTexture, vTextureCoord);
	oFragColor = tex;
}
