
#ifndef LOC_VULKAN_API_01
#define LOC_VULKAN_API_01

#include "vk_abstracionz.hpp"
#include "vk_shaderz.hpp"
#include "partical_lib.hpp"
/*
//*********************************************

#########******class vulkan_app{*****#########

***********************************************
*/
//forward declationz
struct vulkan_api;

class vulkan_app{

    vulkan_api* vk_api;
    parser_vulkan_modual* vm_parser;

    public :

    vulkan_app();
    void run()
    {
        vulkan_inialz();
        loop();
        //shutdown();
    }
    private :
    void parser_run()
    {
      vm_parser->shader_info_reader(SHADER_INFO_PATHNAME);
    }
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
    parser_vulkan_modual*  ptr_parser;

    VkDebugReportCallbackEXT debugger;
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
    logger logging;

    uint32_t apiVersion;

    swapchainz_handle swapchan_handle;

    uint32_t active_width;
    uint32_t active_height;
    bool window_resize_event; /// this should be perhaps bound to the viewport andsuch.... but for now a higher scope seems simpler.

    manual_window_parmz m_window;


    //scene stuff.
    compute_partic_attracto_sim partical_A_sym;

    void genrate_partical_A_data();


    //

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
    void on_window_resize(xcb_window_t window, int w, int h);
#endif

void renderLoop();

void setup_partical_A();

void set_parser(parser_vulkan_modual* in_pars_vk_model)
{
    ptr_parser = in_pars_vk_model;
}
//////////////////////////FUNCTIONAL FUNCTION LIST>>>>ISH
////////////////////*********************///////////

    void inaltize_vulkan_instance();
    void setupDebugMessenger();

    void create_surface();
    bool select_Physical_Device();
    bool create_Logical_Device();
    void create_swapchan_imageviews();
    bool create_swap_Chain();

    void create_rednerpass();
    
    void createDescriptorSetLayout();
    void create_semaphore_fencez();

    void createComputePipeline();
    void createGraphicsPipeline();
    void createCommandPool();
    void createDepthResources();
    void createFramebuffers();

    void createVertexBuffer();
    void createUniformBuffers();

    void createTexelStorage();


    void createDescriptorPool();

    void createDescriptorSets() ;

    void build_compute_comand_buffers();
    void  createCommandBuffers();

    void discriptor_test_setup();


    int32_t device_score(VkPhysicalDeviceProperties& in_pdp,VkPhysicalDeviceFeatures& in_pdf);

    bool check_required_extentions(VkPhysicalDevice& device, const std::vector<const char*> dev_ext, uint32_t ext_count);

    inline void setup_debug()
    {
      debugger= external_vulkan::CreateDebugger(vk_occurance.vk_instance);
    }



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

        swapchan_handle.cleanupSwapChain(vk_occurance.logical_device);

        vkDestroyImageView(vk_occurance.logical_device, vk_occurance.depthImageView, nullptr);
        vkDestroyImage(vk_occurance.logical_device, vk_occurance.depthImage, nullptr);
        vkFreeMemory(vk_occurance.logical_device, vk_occurance.depthImageMemory, nullptr);

        vkFreeCommandBuffers(vk_occurance.logical_device, vk_occurance.graphics.commandPool, static_cast<uint32_t>(vk_occurance.graphics.command_buffers.size()), vk_occurance.graphics.command_buffers.data());

        vkDestroyPipeline(vk_occurance.logical_device, vk_occurance.graphics.pipeline, nullptr);
        vkDestroyPipelineLayout(vk_occurance.logical_device, vk_occurance.graphics.pipelineLayout, nullptr);


        vkDestroyRenderPass(vk_occurance.logical_device, vk_occurance.render_Pass, nullptr);
        vkDestroyDescriptorPool(vk_occurance.logical_device,vk_occurance.descriptorPool, nullptr);
     //    vkDestroyDescriptorPool(vk_occurance.logical_device,vk_occurance.compute.descriptorPool, nullptr);

         vk_occurance.graphics.command_buffers.clear();
        // vk_occurance.compute.command_buffers.clear();

    std::cout << "command_buffers.clear(\n";


      for (size_t i = 0; i < vk_occurance.graphics.uniformBuffers.size(); i++) {
            vkDestroyBuffer(vk_occurance.logical_device, vk_occurance.graphics.uniformBuffers[i], nullptr);
            vkFreeMemory(vk_occurance.logical_device, vk_occurance.graphics.uniformBuffersMemory[i], nullptr);
        }
         for (size_t i = 0; i < vk_occurance.compute.uniformBuffers.size(); i++) {
        vkDestroyBuffer(vk_occurance.logical_device, vk_occurance.compute.uniformBuffers[i], nullptr);
            vkFreeMemory(vk_occurance.logical_device, vk_occurance.compute.uniformBuffersMemory[i], nullptr);
         }
       this->create_swap_Chain();
       this->create_swapchan_imageviews();

       this->create_rednerpass();
       this->createGraphicsPipeline();
     //  this->createComputePipeline();
       this->createDepthResources();
       this->createFramebuffers();
       this->createUniformBuffers();
       this->createDescriptorPool();
       this->createDescriptorSets();
       this->createCommandBuffers();




    }

};

#endif
