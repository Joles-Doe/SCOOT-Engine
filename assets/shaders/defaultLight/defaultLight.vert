#version 450 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

out vec2 vTexCoord;
out vec3 vWorldPosition;
out vec3 vWorldNormal;

uniform mat4 uPerspectiveProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
    vec4 worldPosition = uModel * vec4(aPosition, 1.0);

    vWorldPosition = worldPosition.xyz;
    vWorldNormal = mat3(transpose(inverse(uModel))) * aNormal;
    vTexCoord = aTexCoord;

    gl_Position = uPerspectiveProjection * uView * worldPosition;
}