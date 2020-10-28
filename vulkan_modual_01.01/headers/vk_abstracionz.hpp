
#ifndef ABSTRACTIONS_VULKAN_HPP
#define ABSTRACTIONS_VULKAN_HPP

#include <set>

#include "vulkani_strucz.hpp"


namespace vk_utiltiyz{

    VkShaderModule create_shaderModual(const std::vector<char>& code, VkDevice& logical_device);

    std::vector<const char*> getRequiredExtensions();
     
    bool check_required_device_extentions(VkPhysicalDevice& device);

    std::vector<VkExtensionProperties> supported_device_extentions(VkPhysicalDevice& device);

     bool get_queueFamily(const VkPhysicalDevice& phycal_device, VkQueueFlagBits flags, uint32_t& queue_family_index); 
    
    VkSurfaceFormatKHR select_surface_format(std::vector<VkSurfaceFormatKHR> & formatez);

    VkPresentModeKHR select_present_mode(const std::vector<VkPresentModeKHR>& pmode);

    queue_family_indices get_que_fammily_indicas(VkPhysicalDevice& device, VkSurfaceKHR& surface );

    swapchain_support_details query_swapchain_support(VkPhysicalDevice& device,VkSurfaceKHR& in_surface);
    std::vector<VkExtensionProperties> supported_device_extentions(VkPhysicalDevice& device);

     bool checkValidationLayerSupport(); 


        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features,VkPhysicalDevice& phy_device);
        VkFormat findDepthFormat(VkPhysicalDevice& phy_device);
  
}


class swapchainz_handle {


public:
	VkFormat sc_colorFormat;
	VkColorSpaceKHR sc_colorSpace;
	VkSwapchainKHR swapchain = VK_NULL_HANDLE;


	uint32_t image_Count;
	std::vector<VkImage> sc_images;
	std::vector<swapchain_buffer> sc_buffers;

     std::vector<VkImageView> sc_image_views;

	uint32_t queueNodeIndex = UINT32_MAX;

    
    VkFormat   sc_imageFormat;
    VkExtent2D sc_extent;


	void create( uint32_t& width,  uint32_t& height,bool resize, VkPhysicalDevice& phy_device,VkSurfaceKHR& in_surface,VkDevice& logical_device  ,bool vsync = false);
   
     void create_image_view(VkDevice& logical_device)
     {
         std::cout << "############create image view###############::swapchainz_handle::abstractionz.hpp\n";
        sc_image_views.resize(sc_images.size());
        for(int i = 0; i < sc_images.size(); i++)
        {
            VkImageViewCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image = sc_images[i];
            createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            createInfo.format = sc_colorFormat;
            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel = 0;
            createInfo.subresourceRange.levelCount = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount = 1;

            if (vkCreateImageView(logical_device, &createInfo, nullptr, &sc_image_views[i]) != VK_SUCCESS) {
          throw std::runtime_error("failed to create image views!");
}


        }
     }
      
     
    
	VkResult acquireNextImage(VkSemaphore presentCompleteSemaphore, uint32_t* imageIndex);
	VkResult queuePresent(VkQueue queue, uint32_t imageIndex, VkSemaphore waitSemaphore = VK_NULL_HANDLE);
	void cleanup();

    VkExtent2D select_swap_2Dextent_from_surface_capabilities(const VkSurfaceCapabilitiesKHR& sc_z,const uint32_t& width, 
                                                              const uint32_t& height,bool window_resize);



    uint32_t swapchain_image_count(const VkSurfaceCapabilitiesKHR &sc_z)
    {
        uint32_t image_count = sc_z.minImageCount + 2;
        std::cout << "imagecountsc_z.minImageCount::" << image_count<< '\n';
        std::cout << "isc_z.maxImageCount:" << sc_z.maxImageCount << '\n';

        if( (sc_z.maxImageCount > 0) &&(image_count > sc_z.maxImageCount)) 
        {
            image_count = sc_z.maxImageCount;
            std::cout << "isc_z.maxImageCount:" << image_count<< '\n';
        }
        

        return image_count;
    }


};




#endif