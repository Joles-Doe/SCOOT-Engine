#version 450 core

#define MAX_LIGHTS 16

struct PointLight
{
    vec3 position;
    vec3 color;
    float intensity;
    float range;
};

uniform PointLight uLights[MAX_LIGHTS];
uniform int uLightCount;
uniform sampler2D uTexture;
uniform vec3 uCameraPosition;
uniform vec3 uBaseColor;
uniform vec3 uSpecularColor;
uniform float uSpecularStrength;
uniform float uShininess;

in vec2 vTexCoord;
in vec3 vWorldPosition;
in vec3 vWorldNormal;

out vec4 oFragColor;

void main()
{
    vec3 albedo = texture(uTexture, vTexCoord).rgb * uBaseColor;
    vec3 normal = normalize(vWorldNormal);
    vec3 diffuseLighting = vec3(0.05);
    vec3 specularLighting = vec3(0.0);
    vec3 viewDirection = normalize(uCameraPosition - vWorldPosition);

    for (int i = 0; i < uLightCount; ++i)
    {
        vec3 toLight = uLights[i].position - vWorldPosition;
        float distanceToLight = length(toLight);

        if (distanceToLight >= uLights[i].range) continue;
        if (distanceToLight < 0.001) continue;

        vec3 lightDirection = normalize(toLight);
        float diffuse = max(dot(normal, lightDirection), 0.0);

        float attenuation = 1.0 / (1.0 + 0.09 * distanceToLight + 0.032 * distanceToLight * distanceToLight);

		vec3 radiance = uLights[i].color * uLights[i].intensity * attenuation;
		diffuseLighting += radiance * diffuse;

		if (diffuse > 0.0)
		{
			vec3 halfwayDirection = normalize(lightDirection + viewDirection);
			float specular = pow(
				max(dot(normal, halfwayDirection), 0.0),
				uShininess);
			specularLighting += radiance * uSpecularColor * (uSpecularStrength * specular);
		}
    }

    oFragColor = vec4(albedo * diffuseLighting + specularLighting, 1.0);
}
