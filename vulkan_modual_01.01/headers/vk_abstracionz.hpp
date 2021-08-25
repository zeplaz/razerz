
#ifndef ABSTRACTIONS_VULKAN_HPP
#define ABSTRACTIONS_VULKAN_HPP

#include <set>

#include "vulkani_strucz.hpp"

namespace vk_utiltiyz{

    static uint32_t Image_Count_Surface = 3; 
    VkShaderModule create_shaderModual(const std::vector<unsigned int>& code, VkDevice& logical_device);
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

    VkImageView createImageView(VkDevice& in_device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
     
    uint32_t findMemoryType(VkPhysicalDevice& physicalDevice ,uint32_t typeFilter, VkMemoryPropertyFlags properties);

    void createImage(VkPhysicalDevice& phsical_device, VkDevice& device,uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
                     VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory); 

    void create_buffer(VkPhysicalDevice& phsical_device, VkDevice& logical_device, VkDeviceSize dsize,
                       VkBufferUsageFlags usage, VkMemoryPropertyFlags proprerties,
                       VkBuffer& buffer, VkDeviceMemory& buff_mem);
  
    void copyBuffer(VkDevice& device,VkCommandPool& in_commandPool, VkQueue& in_q, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    VkCommandBuffer beginSingleTimeCommands(VkDevice& device,VkCommandPool& in_commandPool);
    void endSingleTimeCommands(VkDevice& device, VkQueue& in_q,VkCommandPool& in_commandPool, VkCommandBuffer commandBuffer); 
  
  VkCommandBuffer createCommandBuffer(VkDevice& logical_device,VkCommandBufferLevel level, VkCommandPool pool, bool begin);


}


class swapchainz_handle {

public:
	VkFormat sc_colorFormat;
	VkColorSpaceKHR sc_colorSpace;
	VkSwapchainKHR swapchain = VK_NULL_HANDLE;

//	uint32_t image_Count;
	std::vector<VkImage> sc_images;
	std::vector<VkFramebuffer> sc_framebuffers;

  std::vector<VkImageView> sc_image_views;

	uint32_t queueNodeIndex = UINT32_MAX;

  //VkFormat   sc_imageFormat;
  VkExtent2D sc_extent;

	void create( uint32_t& width,  uint32_t& height,bool resize, VkPhysicalDevice& phy_device,
              VkSurfaceKHR& in_surface,VkDevice& logical_device  ,bool vsync = false);

  void create_image_view(VkDevice& logical_device);
   
	VkResult acquireNextImage(VkSemaphore presentCompleteSemaphore, uint32_t* imageIndex);

	VkResult queuePresent(VkQueue queue, uint32_t imageIndex, VkSemaphore waitSemaphore = VK_NULL_HANDLE);
  
	void cleanup();

  VkExtent2D select_swap_2Dextent_from_surface_capabilities(const VkSurfaceCapabilitiesKHR& sc_z,const uint32_t& width,
                                                              const uint32_t& height,bool window_resize);
  uint32_t swapchain_image_count(const VkSurfaceCapabilitiesKHR &sc_z);
  

  void cleanupSwapChain(VkDevice& device) {

        for (auto framebuffer : sc_framebuffers) {
            vkDestroyFramebuffer(device, framebuffer, nullptr);
        }
     

        for (auto imageView : sc_image_views) {
            vkDestroyImageView(device, imageView, nullptr);
        }

        vkDestroySwapchainKHR(device, swapchain, nullptr);

    }
  };

#endif
