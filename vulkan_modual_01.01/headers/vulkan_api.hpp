
#ifndef LOC_VULKAN_API_01
#define LOC_VULKAN_API_01




//#include <vulkan/vulkan.h>
///#include <optional>
///#include <vector>



#include "vk_abstracionz.hpp"


/*
//*********************************************


#########******class vulkan_app{*****#########


***********************************************
*/
//forward declationz
struct vulkan_api;

//

class vulkan_app{


//make this a pointer...
    vulkan_api* vk_api;

    public : 

    vulkan_app();
    void run()
    {
        //initwindow();
        vulkan_inialz();
        loop();
        //shutdown();
    }
    private : 
    void loop();
    bool vulkan_inialz();
    void shutdown();

};


/*
//*********************************************


#########******struct vulkan_api*****#########


***********************************************
*/

struct vulkan_api
{   
// data members.
    vulkan_occurance vk_occurance;
    VkDebugReportCallbackEXT debugger;
    logger logging;

    uint32_t apiVersion; 


    swapchainz_handle swapchan_handle;

    uint32_t active_width; 
    uint32_t active_height;
    bool window_resize_event; /// this should be perhaps bound to the viewport andsuch.... but for now a higher scope seems simpler.
    
    manual_window_parmz m_window;

/*
*******funcionz///************
*/



////////////////////*********************////////////
// for manual screeen/window creation
#if defined(_WIN32)
    void createWindow(HINSTANCE hInstance);
#elif defined(__linux__)
    void createWindow();
    void resize_window_xcb(int h, int w, int x, int y);


    void on_window_resize(xcb_window_t window, int w, int h)
    {   

        std::cout << "###DEBUG:::on window resize this is only the linux function move to some kind of template.. for os type.z.  and why cant i use a void *?\n";
        VkSurfaceCapabilitiesKHR surface_capabilities;
        VkResult vkr  = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vk_occurance.physical_Device,vk_occurance.surface,&surface_capabilities);

        if(w>surface_capabilities.maxImageExtent.width) w = surface_capabilities.maxImageExtent.width;
        if(w>surface_capabilities.maxImageExtent.height) w = surface_capabilities.maxImageExtent.height;

        if(w ==0 || h == 0) return;

        active_height = h;
        active_width = w;
        renew_swap_chain();
    }
#endif

void renderLoop();

//////////////////////////FUNCTIONAL FUNCTION LIST>>>>ISH
////////////////////*********************///////////

    void inaltize_vulkan_instance();
    void create_surface();
    bool select_Physical_Device();
    bool create_Logical_Device();




    void create_swapchan_imageviews()
    {
            std::cout << "###### vkAPI::create_swapchan_imageviews\n******########********\n";
        swapchan_handle.create_image_view(vk_occurance.logical_device);
    }

    bool create_swap_Chain()
    {       
        std::cout << "######VKAPI::create_swapchain\n******########********\n";
     	        //swapchain_support_details swapchain_details = vk_utiltiyz::query_swapchain_support(vk_occurance.physical_Device); 
            //bool resize, VkPhysicalDevice& phy_device,VkSurfaceKHR& in_surface  ,bool vsync = false);
         swapchan_handle.create(active_width,active_height,false,vk_occurance.physical_Device,vk_occurance.surface,vk_occurance.logical_device); 


    }

    void create_rednerpass();
    void createDescriptorSetLayout();

//////////////////////////////UNDERCONSTRUCTION OR ILL SORTED>////////////////////////////////////

    

///END OF NESSARY INIZLATION PRIMIARY FUNCTIONS REMADER ARE HELPERS OR OTHER USEISL STUFF< ALSO ALOT OF THIS NEEDS TO BE CPP>> 
////////////////IDK> A new file though.. 

 

    void renew_swap_chain()
    {   

        std::cerr << "\n**************&&&&&&&&&&&&&&&&&&&&&&&&********************\n#####WARNNING SEUVITY LEVELL#####\n \/\
                    ###################THIS IS A dummy functionz :::amount_of_images_in_swap_chain::: MIGHT NEED BE REPLACED>>>> \/\
                    DOES NOT RENEW SWAPCHIAN AS ITS IMSPOABLE>>> \nTO CURRNTLY NON EXISTING CREATE_SWAPCHAIN  MOW however for testing of func renew_swap_chain disable this function \n/\
                    *********^^^^^***********##### \n";
    
    swapchain_support_details swapchain_details = vk_utiltiyz::query_swapchain_support(vk_occurance.physical_Device,vk_occurance.surface);  
    uint32_t amount_of_images_in_swap_chain = swapchan_handle.swapchain_image_count(swapchain_details.capabilities);

     
    std::cout << "amount_of_images_in_swap_chain::" <<  amount_of_images_in_swap_chain <<'\n';
    
    vkDeviceWaitIdle(vk_occurance.logical_device);

    std::cout << "DEVISTWAITIDALD\n";
       /* vkFreeCommandBuffers(vk_occurance.logical_device, vk_occurance.command_pool,amount_of_images_in_swap_chain,vk_occurance.command_buffers.data());
        
        std::cout << "vkFreeCommandBuffers\n";
         */
         vk_occurance.command_buffers.clear();
    std::cout << "command_buffers.clear(\n";


    }




    bool setup_Debugger();
    
    void device_setup();

    void setupDebugMessenger();
   

    int32_t device_score(VkPhysicalDeviceProperties& in_pdp,VkPhysicalDeviceFeatures& in_pdf);
  
    bool check_required_extentions(VkPhysicalDevice& device, const std::vector<const char*> dev_ext, uint32_t ext_count);

   
  
    inline void setup_debug()
    {
      debugger= external_vulkan::CreateDebugger(vk_occurance.vk_instance);
    }   
   


};



#endif 