
#include "../headerz/vulkan_app.hpp"


vulkan_app::vulkan_app()
{
    vk_api = new vulkan_api();
}
void vulkan_app::loop()
{
    vk_api->renderLoop();
}

void shutdown()
{
  std::cout << "\n##########################\n#SNEED TO IMPLMENT PROPER SHUTDOWN HERE!\n###################";
}

bool vulkan_app::vulkan_inialz()
    {
        vk_api->inaltize_vulkan_instance();
        vk_utiltiyz::checkValidationLayerSupport();
        vk_api->setupDebugMessenger();

        vk_api->create_surface();
        vk_api->select_Physical_Device();
        vk_api->create_Logical_Device();

        vk_api->create_swap_Chain();
        vk_api->create_swapchan_imageviews();

        vk_api->create_rednerpass();
        vk_api->createDepthResources();
    };
