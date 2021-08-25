
#ifndef VULKANI_STRUCTZZ_HPP
#define VULKANI_STRUCTZZ_HPP

//#include <vulkan/vulkan.h>

#include "vulkan_definz.hpp"


#define GET_INSTANCE_PROC_ADDR(inst, entrypoint)                                                              \
    {                                                                                                         \
        demo->fp##entrypoint = (PFN_vk##entrypoint)vkGetInstanceProcAddr(inst, "vk" #entrypoint);             \
        if (demo->fp##entrypoint == NULL) {                                                                   \
            ERR_EXIT("vkGetInstanceProcAddr failed to find vk" #entrypoint, "vkGetInstanceProcAddr Failure"); \
        }                                                                                                     \
    }

static PFN_vkGetDeviceProcAddr g_gdpa = NULL;

#define GET_DEVICE_PROC_ADDR(dev, entrypoint)                                                                    \
    {                                                                                                            \
        if (!g_gdpa) g_gdpa = (PFN_vkGetDeviceProcAddr)vkGetInstanceProcAddr(demo->inst, "vkGetDeviceProcAddr"); \
        demo->fp##entrypoint = (PFN_vk##entrypoint)g_gdpa(dev, "vk" #entrypoint);                                \
        if (demo->fp##entrypoint == NULL) {                                                                      \
            ERR_EXIT("vkGetDeviceProcAddr failed to find vk" #entrypoint, "vkGetDeviceProcAddr Failure");        \
        }                                                                                                        \
    }

/*********************************************
 *
 * STRUCTZ::: used for parts in classes, and helpers ::: abstracting vulkan datastructes.
**
**********************************************/

/*
** SWAP CHAIN STUCTZZ
*/



//
typedef struct queue_family_indices
    {
        std::optional<uint32_t> graphics_Family;
        std::optional<uint32_t> present_Family;
        std::optional<uint32_t> compute_Family;
        std::optional<uint32_t> transfer_Family;
    // VK_QUEUE_SPARSE_BINDING_BIT

        bool does_exist()
        {
        return graphics_Family.has_value() &&  present_Family.has_value();
      }
    };

typedef struct swapchain_support_details_type
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
}swapchain_support_details;

struct device_score_card
{
    int index;
    int32_t score;

    bool operator ==(const device_score_card &b) const
    {
      if(this->index == b.index)
      {return true;}

      return false;
     }

    bool operator !=(const device_score_card &b) const
         {
             if (this->score != b.score)
             {return true;}

             return false;
         }
    bool operator <(const device_score_card &b) const
         {
            if (this->score < b.score)
            {return true;}


            return false;
         }
    bool operator >(const device_score_card &b) const
         {
            if (this->score > b.score)
            {return true;}

            return false;
         }
     };

     /*
//*********************************************


#########******struct vulkan_occurance*****#########


***********************************************
*/

struct vulkan_occurance
{

    size_t currentFrame = 0;
    VkInstance vk_instance = VK_NULL_HANDLE;

    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;

    VkPhysicalDevice physical_Device = VK_NULL_HANDLE;
    VkDevice logical_device;

    VkPhysicalDeviceMemoryProperties device_memory_properties;

    VkQueue graphics_queue;
    VkQueue present_queue;
    VkQueue compute_queue;

    VkRenderPass render_Pass;
   // VkDescriptorSetLayout graphics_descriptorSetLayout;
   // VkDescriptorSetLayout compute_descriptorSetLayout;
   // VkPipelineLayout graphics_pipeline_Layout;
   // VkPipelineLayout compute_pipeline_Layout;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;

    VkDescriptorSetLayout descriptor_set_layout[3];


    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;

   VkDescriptorPool descriptorPool;


    struct {
		uint32_t queueFamilyIndex;					// Used to check if compute and graphics queue families differ and require additional barriers
		VkPipelineLayout pipelineLayout;			// Layout of the graphics pipeline
		VkPipeline pipeline;						// Particle rendering pipeline
		VkSemaphore compute_semaphore;                      // Execution dependency between compute & graphic submission
        std::vector<VkCommandBuffer> command_buffers;
        VkCommandPool commandPool;

        std::vector<VkDescriptorSet> descriptorSets;

        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;

	} graphics;

    struct {
		uint32_t queueFamilyIndex;					// Used to check if compute and graphics queue families differ and require additional barriers
	    VkCommandPool commandPool;					// Use a separate command pool (queue family may differ from the one used for graphics)
			// Command buffer storing the dispatch commands and barriers
		VkSemaphore compute_semaphore;                      // Execution dependency between compute & graphic submission
		VkPipelineLayout pipelineLayout;			// Layout of the compute pipeline
		VkPipeline pipeline;
        VkCommandBuffer primary_command_buffer;
        std::vector<VkCommandBuffer> command_buffers;

       // VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;

        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;

	}compute;
};

/*********************************************

***********************************************
*/

#if defined(_WIN32)
 struct  manual_window_parmz
 {
     HINSTANCE instance;
     HWND      window_handle;

 }
#elif defined(__linux__)

struct  manual_window_parmz
{
    xcb_connection_t * connection_ptr;
    xcb_window_t window_handle;
    xcb_screen_t * screen_ptr;
    xcb_atom_t wmProtocols;
    xcb_atom_t wmDeleteWin;

};

#elif defined(VK_USE_PLATFORM_XLIB_KHR)

struct  manual_window_parmz
{

      Display            *display_ptr;
      Window              widnow_handle;
};

#endif// end of OS spsific code.

class base_windows_handler {
    public :
    virtual bool on_window_resize() = 0;
    virtual bool draw() = 0;

    virtual bool ready_to_render() const final
    {
        return can_be_rendered;
    }

    base_windows_handler() : can_be_rendered(false) {};

    virtual ~base_windows_handler() = default;

    protected :
    bool can_be_rendered;
};


class vulkan_window_ctlr
{
public:

    bool create( const char *nameofwindow);
    bool window_render_loop(base_windows_handler &in_window_handle) const;
    manual_window_parmz     get_manual_window_controls() const;
private :
    manual_window_parmz window_controls;
};
//utiltizeclasses

class dev_comper
{
public:
  bool operator() (const device_score_card& lhs, const device_score_card&rhs) const
  {
     return lhs.score < rhs.score;
  }
};


/***************************************************\


/*&memory type belongs to a heap with the VK_MEMORY_HEAP_DEVICE_LOCAL_BIT set.

= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT

 VK_BUFFER_USAGE_TRANSFER_SRC_BIT = 0x00000001,
    VK_BUFFER_USAGE_TRANSFER_DST_BIT = 0x00000002,
    VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT = 0x00000004,
    VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT = 0x00000008,
    VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT = 0x00000010,
    VK_BUFFER_USAGE_STORAGE_BUFFER_BIT = 0x00000020,
    VK_BUFFER_USAGE_INDEX_BUFFER_BIT = 0x00000040,
    VK_BUFFER_USAGE_VERTEX_BUFFER_BIT = 0x00000080,
    VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT = 0x00000100,
*/


class manged_buffer_memory
{

    VkDeviceSize data_size= VK_NULL_HANDLE;
  //  VkMemoryPropertyFlags buff_mem_flags;
    VkBuffer buffer = VK_NULL_HANDLE;
    VkDeviceMemory buffer_memory= VK_NULL_HANDLE;

    public:

   void initalize(VkDeviceSize size, VkBufferCreateFlags flags, VkBufferUsageFlags usage =VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VkSharingMode sharemode = VK_SHARING_MODE_CONCURRENT,
                  uint32_t qfamindex =0, pQueueFamilyIndices qfamIndices = VK_NULL_HANDLE)
   {

     data_size =size;
       VkBufferCreateInfo buffinfo {};

        buffinfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        buffinfo.flags = flags;
        buffinfo.size = data_size;
        buffinfo.usage = usage;
        buffinfo.sharingMode =sharemode;
        buffinfo.queueFamilyIndexCount =qfamindex;
        buffinfo.pQueueFamilyIndices =qfamIndices;
   }


   void update_size(VkDeviceSize in_size)
   {
     //destory memory and remake it!
   }

};
/*
 // Provided by VK_AMD_device_coherent_memory
    VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD = 0x00000040,
  // Provided by VK_AMD_device_coherent_memory
    VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD = 0x00000080,
*/



#endif
/*
class file_reader
{

    friend std::fstream& operator >> (std::fstream& fs, std::vector<char>& fr);
    std::vector<char> operator()(const std::string& filename)
    {
        read_file(filename);
    }

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
};

 std::fstream& operator >> (std::fstream& fs, std::vector<char>& fr)
{
        if(!fs.is_open())
    {
        std::cerr << "#######ERRRO::fileread__static function error***failed to open.. ...\n\n";
        throw std::runtime_error(  "THROW ERROR:FILE>FAILD TO OPEN>");
    }

    size_t file_size = (size_t)fs.tellg();
    std::vector<char> buffer(file_size);
    fs.seekg(0);
    fs.read(buffer.data(),file_size);
    //fs.close();
    fr = buffer;
    return fs;

}
*/
