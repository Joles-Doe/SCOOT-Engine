#pragma once

#include <glm/glm.hpp>

struct SphereCollider
{
    float radius = 0.5f;
    glm::vec3 offset{ 0.0f };
};

struct BoxCollider
{
    glm::vec3 halfExtents{ 0.5f };
    glm::vec3 offset{ 0.0f };
};

struct CapsuleCollider
{
    float radius = 0.5f;
    float halfHeight = 0.5f;
    glm::vec3 offset{ 0.0f };
};