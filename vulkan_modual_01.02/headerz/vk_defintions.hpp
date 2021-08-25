#ifndef VULKANI_DEFINZ_002_HPP
#define VULKANI_DEFINZ_002_HPP

/***********************
FILE CONTAINS::
some presets for the vulkan inialzation, (layers, extentions, defult defines and macos)
********************/

#define DEBUG_01
#define ASSERT_ON

//glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#ifdef USEZ_GLFW
    #define GLFW_INCLUDE_VULKAN
    #include <GLFW/glfw3.h>
#endif

#if defined(VK_USE_PLATFORM_XLIB_KHR) || defined(VK_USE_PLATFORM_XCB_KHR)
#include <X11/Xutil.h>
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
#include <linux/input.h>
#endif

#ifdef _WIN32
#ifdef _MSC_VER
#pragma comment(linker, "/subsystem:windows")
#endif  // MSVC
#define APP_NAME_STR_LEN 80
#endif  // _WIN32


#ifdef DEBUG_01
    //#include "vk_debug.hpp"
    const bool enableValidationLayers = true;
#else
    const bool enableValidationLayers = false;
#endif // DEBUG DEBUG_01

/*********************************************
/*************application pre-sets
*************************************************/

const uint32_t PRESET_VULK_WIDTH  =1000;
const uint32_t PRESET_VULK_HEIGHT =1000;

constexpr float DEFAULT_1_PRIORITY = 1.0f;
constexpr float GRAPHYIC_QUE_PRIORITY = 0.8f;
constexpr float COMPUTRE_QUE_PRIORIRY = 1.0f;
constexpr float PRESENTA_QUE_PRIORIRY = 0.9f;

constexpr char* APPLICATION_NAME = "vk_instance_02";

/*****************************
VULKAN VALDATION LAYERS, DEVICE EXTENTIONS PLATFORM DEPENDENT and instance Extentitions
************************************/

const std::vector<const char*> validation_layerz =
 {
    "VK_LAYER_KHRONOS_validation",
    "VK_LAYER_LUNARG_monitor",
    "VK_LAYER_LUNARG_api_dump"
 };
 const uint32_t layer_count = validation_layerz.size();


#if defined(_WIN32)
//VK_USE_PLATFORM_WIN32_KHR
 std::array<const char*,2> DEF_Device_Extensions =
    {
        VK_USE_PLATFORM_WIN32_KHR,
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    }
#elif defined(__ANDROID__)
//VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
#elif defined(__linux__)

const std::vector<const char*> DEF_Instance_extentions=
{
   "VK_EXT_debug_report" ,
    VK_KHR_SURFACE_EXTENSION_NAME,
    VK_KHR_XCB_SURFACE_EXTENSION_NAME,
    VK_KHR_SURFACE_EXTENSION_NAME

};

const uint32_t INSTA_extention_count = DEF_Instance_extentions.size();

const std::vector<const char*> DEF_Device_Extensions =
{
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};
const uint32_t DEVICE_extention_count = DEF_Device_Extensions.size();

#endif

/***************************
::::::::::::MACROS::
*****************************/

#define BUFFER_OFFSET(i) ((char *)NULL + (i))




#endif
