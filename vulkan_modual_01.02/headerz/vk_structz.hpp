
#ifndef VULKANI_STRUCTZZ_HPP
#define VULKANI_STRUCTZZ_HPP


#include "vulkan_definz.hpp"

/*********************************************
 *
 * STRUCTZ::: used for parts in classes, and helpers ::: abstracting vulkan datastructes.
**
**********************************************/


/*********************************************


#########******struct vulkan_occurance*****#########


***********************************************/
struct DepthImage{
  VkImage image;
  VkDeviceMemory memory;
  VkImageView view;
};

struct vulkan_occurance
{
    size_t current_frame = 0;
    VkInstance vk_instance = VK_NULL_HANDLE;

    VkDebugUtilsMessengerEXT debug_messenger;

    VkPhysicalDevice physical_Device = VK_NULL_HANDLE;
    VkDevice logical_device  = VK_NULL_HANDLE;

    VkQueue graphics_queue;
    VkQueue present_queue;
    VkQueue compute_queue;

    VkRenderPass render_Pass;

    DepthImage depth_image;
}:

/*****************************
    WINDOW MANGMENT:
********************/
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



/********************************
UTILIZEZ CLASSES FOR INIALIZATION
*******************************/
class dev_comper
{
    public:
      bool operator() (const device_score_card& lhs, const device_score_card&rhs) const
      {
         return lhs.score < rhs.score;
      }
};



/*********************
** SWAP CHAIN STUCTZZ for ques etc
**********************/


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

#endif
