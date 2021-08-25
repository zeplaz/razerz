

#ifndef LOC_VULKAN_API_02
#define LOC_VULKAN_API_02

/*
//*********************************************

#########******struct vulkan_api*****#########

***********************************************
*/



struct vulkan_api
{
    uint32_t apiVersion;

    vulkan_occurance vk_occurance;
    swapchainz_handle swapchan_handle;

    uint32_t active_width;
    uint32_t active_height;

    bool window_resize_event; /// this should be perhaps bound to the viewport andsuch.... but for now a higher scope seems simpler.

    manual_window_parmz m_window;
    /*
    *******funcionz///************
    */
    ////////////////////*********************////////////
    // for manual screeen/window creation/////
    #if defined(_WIN32)
        void createWindow(HINSTANCE hInstance);
    #elif defined(__linux__)
        void createWindow();
        void resize_window_xcb(int h, int w, int x, int y);
        void on_window_resize(xcb_window_t window, int w, int h);
    #endif
    void renderLoop();

    //////////////////////////FUNCTIONAL FUNCTION LIST INIALZE>>>>ISH
    ////////////////////*********************///////////

        void inaltize_vulkan_instance();
        void setupDebugMessenger();

        void create_surface();
        bool select_Physical_Device();
        bool create_Logical_Device();
        void create_swapchan_imageviews();
        bool create_swap_Chain();

        void create_rednerpass();

        void createDepthResources();
/////////

void build_current_scene()
{
  /*
  vk_api->createDescriptorSetLayout();
  vk_api->create_semaphore_fencez();
  vk_api->createGraphicsPipeline();
  vk_api->createComputePipeline();
  vk_api->createCommandPool();
  vk_api->createFramebuffers();
  vk_api->createVertexBuffer();

  vk_api->createUniformBuffers();
  vk_api->setup_partical_A();
  vk_api->createDescriptorPool();
  vk_api->createDescriptorSets();

  vk_api->build_compute_comand_buffers();

  vk_api->createCommandBuffers();
  */
}



#endif
