
#ifndef VULKANI_DEFINZ_001_HPP
#define VULKANI_DEFINZ_001_HPP

#include <fstream>
#define DEBUG_01

#include <optional>
#include <string>
#include <vector>
#include <stdarg.h>

#include "exrtn_vulkan.hpp"
#include "flag_templatez.hpp"

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

#ifdef ANDROID
#include "vulkan_wrapper.h"
#else
//#include <vulkan/vulkan.h>
#endif



#ifdef USEZ_GLFW
    #define GLFW_INCLUDE_VULKAN
    #include <GLFW/glfw3.h>
#endif 

//constz   

#ifdef DEBUG_01
    #include "vk_debug.hpp"
    const bool enableValidationLayers = false;
#else 
    const bool enableValidationLayers = false;
#endif // DEBUG DEBUG_01


const uint32_t PRESET_VULK_WIDTH  =1000;
const uint32_t PRESET_VULK_HEIGHT =1000; 

constexpr float DEFAULT_1_PRIORITY = 1.0f;
constexpr float GRAPHYIC_QUE_PRIORITY = 0.8f;
constexpr float COMPUTRE_QUE_PRIORIRY = 1.0f; 
constexpr float PRESENTA_QUE_PRIORIRY = 0.9f;

constexpr char* APPLICATION_NAME = "vk_instance";

/*
/*********<STREAM_opratorsz
*/
std::ostream& operator<<(std::ostream& os, const VkPhysicalDeviceLimits& vkpdl);
std::ostream& operator<<(std::ostream& os, const VkPhysicalDeviceFeatures& vkpdf);
std::ostream& operator<<(std::ostream& os, const VkPhysicalDeviceType& vkpdf);

// these should be moved to a data file and loeaded by a setup parcer. as layers and such may want to be reoginzed. or i suppose
// switches later on could derb whav. 

/* 
const functionzx
TODO::move it. lol. and dalso make all constexper. 
*/

const std::vector<const char*> validation_layerz = 
 {
    "VK_LAYER_KHRONOS_validation",
    "VK_LAYER_LUNARG_monitor"
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

   /*
   //VK_KHR_XCB_SURFACE_EXTENSION_NAME
    std::array<const char*,2> DEF_Device_Extensions = 
    {  
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };*/
#endif




static  std::vector<char> read_file(const std::string& filename)
{   
    std::ifstream file(filename,std::ios::ate|std::ios::binary);
    if(!file.is_open())
    {
        std::cerr << "#######ERRRO::fileread__static function error***failed to open.. ...\n\n";
        throw std::runtime_error(  "THROW ERROR:FILE>FAILD TO OPEN>");
    }

    size_t file_size = (size_t)file.tellg();
    std::vector<char> buffer(file_size);
    file.seekg(0);
    file.read(buffer.data(),file_size);
    file.close();

    return buffer;


}



enum class Shader_Stagez : uint32_t {
     SHADER_NULL         = 0x00,
     COMPUTE_SHADER      = 0x02,
     VERTEX_SHADER       = 0x04,
     FRAGMENT_SHADER     = 0x08,
     TESS_CONTROL_SHADER = 0x10,
     TESS_EVAL_SHADER    = 0x20,
     GEOMETRY_SHADER     = 0x40,
     ALL_PIPE            = 0x80
};
template<>
struct EnableBitMaskOperators<Shader_Stagez>
{
    static const bool enable = true;
};


#endif