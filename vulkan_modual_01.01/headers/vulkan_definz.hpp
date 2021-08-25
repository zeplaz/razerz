
#ifndef VULKANI_DEFINZ_001_HPP
#define VULKANI_DEFINZ_001_HPP

#include <fstream>
#define DEBUG_01

#include <optional>
#include <string>
#include <vector>
#include <stdarg.h>

//glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>



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
    const bool enableValidationLayers = true;
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
constexpr const char* SHADER_INFO_PATHNAME = "shader_build_info.info";



#define VERTEX_BUFFER_BIND_ID 0

constexpr int VERTEX_ARRAY_POS = 0;
constexpr int TESS_CTL_ARRAY_POS = 1;
constexpr int TESS_EVAL_ARRAY_POS = 2;
constexpr int GEO_ARRAY_POS = 3;
constexpr int COMPUTE_ARRAY_POS = 4;
constexpr int FRAG_ARRAY_POS = 5;

constexpr int MAX_FRAMES_IN_FLIGHT = 4;
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
     COMPUTE_SHADER      = 0x01,
     VERTEX_SHADER       = 0x02,
     FRAGMENT_SHADER     = 0x04,
     TESS_CONTROL_SHADER = 0x08,
     TESS_EVAL_SHADER    = 0x16,
     GEOMETRY_SHADER     = 0x40,
     ALL_PIPE            = 0x71
};
template<>
struct EnableBitMaskOperators<Shader_Stagez>
{
    static const bool enable = true;
};


template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

template<typename type>
class hasher: public std::hash<type>{


    static size_t last_hash;

    std::string output_debug()
    {
        //  std::string temp = "LAST_hahs::" + std::to_string(last_hash);
        return std::string("LAST_hash::" + std::to_string(last_hash));

    }
};


struct glyph_vertex{
   glm::vec4  vertex_pos_texcord;

   bool operator ==(const glyph_vertex& other) const noexcept
   {
    return vertex_pos_texcord == other.vertex_pos_texcord;
   }
};

template<> struct hasher<glyph_vertex>
    {
    std::size_t operator()(glyph_vertex const& bv) const noexcept
    {
     return hasher<glm::vec4>()(bv.vertex_pos_texcord);
    }
    };


struct base_vertex{
    glm::vec3 pos;
    glm::vec4 base_colour;
    glm::vec2 textel_uv;

 bool operator ==(const base_vertex& other) const
  {
    return pos == other.pos && base_colour == other.base_colour && textel_uv == other.textel_uv;
  }

};

template<> struct hasher<base_vertex>
    {
    std::size_t operator()(base_vertex const& bv) const noexcept
    {
     return ((hasher<glm::vec3>()(bv.pos) ^
            (hasher<glm::vec3>()(bv.base_colour) << 1)) >> 1) ^
            (hasher<glm::vec2>()(bv.textel_uv) << 1);
    }
    };

struct compute_vertex_A{
    glm::vec4 vert;
    bool operator ==(const compute_vertex_A& other) const noexcept
    {
        return vert == other.vert;
    }
};
template<> struct hasher<compute_vertex_A>
    {
    std::size_t operator()(compute_vertex_A const& bv) const noexcept
    {
     return hasher<glm::vec4>()(bv.vert);
    }
    };


    struct Model_View_Proj {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;

    bool operator ==(const Model_View_Proj& other) const noexcept
    {
        return view == other.view && proj == other.proj && model== other.model;
    }
    };

template<> struct hasher<Model_View_Proj>
    {
    std::size_t operator()(Model_View_Proj const& bv) const noexcept
    {
     return ((hasher<glm::mat4>()(bv.model) ^
            (hasher<glm::mat4>()(bv.view) << 1)) >> 1) ^
            (hasher<glm::mat4>()(bv.proj) << 1);
    }
    };


/*
*
*extending the hasher function so templates can be aded without polluting standerd library namesapce.. also, feel free to extend.

@::EXTENTIONS::::
static var:: last_hash;
pt_func::oytput_debug()->string



last_hash
.. TODO::: finialze the debuger functions
*
*
*/

/*

namespace std {
    template<> struct hash<base_vertex> {
        size_t operator()(base_vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^
                   (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
                   (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}*/

#endif
