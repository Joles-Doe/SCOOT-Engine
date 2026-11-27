#version 450 core

in vec3 aPosition;
in vec2 aTexCoord;

out vec2 vTextureCoord;

uniform mat4 uPerspectiveProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
	gl_Position = uPerspectiveProjection * uView * uModel * vec4(aPosition, 1.0);
	vTextureCoord = aTexCoord;
}
