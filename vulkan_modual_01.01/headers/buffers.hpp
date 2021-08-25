

#include "vulkan_definz.hpp"

struct shader_uniform {

    VkBuffer buffer;
    VkDeviceMemory memory;

};

const double PI = 3.14159265359f;
const double TORAD = PI/180.0f;

// perspective projection parameters:
float fov = 45.0f;
float nearZ = 0.1f;
float farZ = 1000.0f;

float aspectRatio = context.width / (float)context.height;
float t = 1.0f / tan( fov * TORAD * 0.5 );
float nf = nearZ - farZ;

float projectionMatrix[16] = { t / aspectRatio, 0, 0, 0,
                               0, t, 0, 0,
                               0, 0, (-nearZ-farZ) / nf, (2*nearZ*farZ) / nf,
                               0, 0, 1, 0 };

float viewMatrix[16] = { 1, 0, 0, 0,
                         0, 1, 0, 0,
                         0, 0, 1, 0,
                         0, 0, 0, 1 };

float modelMatrix[16] = { 1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1 };