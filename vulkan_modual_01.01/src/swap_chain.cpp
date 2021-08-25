
#include "../headers/vk_abstracionz.hpp"



  uint32_t swapchainz_handle::swapchain_image_count(const VkSurfaceCapabilitiesKHR &sc_z)
    {
         if(sc_z.minImageCount + 2 > MAX_FRAMES_IN_FLIGHT)
          vk_utiltiyz::Image_Count_Surface =  sc_z.minImageCount + 2;
          else
          vk_utiltiyz::Image_Count_Surface = MAX_FRAMES_IN_FLIGHT;
          
        std::cout << "imagecountsc_z.minImageCount::" << vk_utiltiyz::Image_Count_Surface<< '\n';
        std::cout << "isc_z.maxImageCount:" << sc_z.maxImageCount << '\n';

        if( (sc_z.maxImageCount > 0) &&(vk_utiltiyz::Image_Count_Surface > sc_z.maxImageCount))
        {
            vk_utiltiyz::Image_Count_Surface = sc_z.maxImageCount;
            std::cout << "isc_z.maxImageCount:" << vk_utiltiyz::Image_Count_Surface<< '\n';
        }
        return vk_utiltiyz::Image_Count_Surface;
    }

void swapchainz_handle::create_image_view(VkDevice& logical_device)
     {
         std::cout << "############create image view###############::swapchainz_handle::abstractionz.hpp:::size::\n";
        sc_image_views.resize(sc_images.size());
         std::cout << sc_image_views.size() << '\n';
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

            if (vkCreateImageView(logical_device, &createInfo, nullptr, &sc_image_views[i]) != VK_SUCCESS)
             {
              throw std::runtime_error("failed to create image views!");
             }
        }
    }



void swapchainz_handle::create(uint32_t& width, uint32_t& height,bool resize, VkPhysicalDevice& phy_device,
                              VkSurfaceKHR& in_surface,VkDevice& logical_device, bool vsync)
  {

    VkSwapchainKHR old_sw_chain = swapchain;

    swapchain_support_details swapchain_details = vk_utiltiyz::query_swapchain_support(phy_device,in_surface);

    VkSurfaceFormatKHR surfaceFormat = vk_utiltiyz::select_surface_format(swapchain_details.formats);
    //exit(1);
    VkPresentModeKHR presentMode = vk_utiltiyz::select_present_mode(swapchain_details.presentModes);

    VkExtent2D extent = select_swap_2Dextent_from_surface_capabilities(swapchain_details.capabilities,width, height,resize);

    queue_family_indices indices = vk_utiltiyz::get_que_fammily_indicas(phy_device,in_surface);

   if (swapchain_details.capabilities.currentExtent.width == (uint32_t)-1)
  	{
  		// If the surface size is undefined, the size is set to
  		// the size of the images requested.
  		extent.width = width;
  		extent.height = height;
  	}
      else
  	{
  		// If the surface size is defined, the swap chain size must match
  		extent = swapchain_details.capabilities.currentExtent;
  		width = swapchain_details.capabilities.currentExtent.width;
  		height = swapchain_details.capabilities.currentExtent.height;
  	}

    uint32_t image_count = swapchain_image_count(swapchain_details.capabilities);

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = in_surface;

        createInfo.minImageCount = image_count;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;


           uint32_t queueFamilyIndices[] = {indices.graphics_Family.value(), indices.present_Family.value()};

        if (indices.graphics_Family != indices.present_Family) {
            //. = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        } else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        }

        createInfo.preTransform = swapchain_details.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;

        createInfo.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(logical_device, &createInfo, nullptr, &swapchain) != VK_SUCCESS) {
            throw std::runtime_error("failed to create swap chain!");
        }

        vkGetSwapchainImagesKHR(logical_device, swapchain, &image_count, nullptr);
        sc_images.resize(image_count);
        vkGetSwapchainImagesKHR(logical_device, swapchain, &image_count, sc_images.data());

        std::cout << "surfaceFormat" << surfaceFormat.format << '\n';
      //  exit(1);
        this->sc_colorFormat = surfaceFormat.format;
        this->sc_extent = extent;
    }

    VkResult swapchainz_handle::acquireNextImage(VkSemaphore presentCompleteSemaphore, uint32_t* imageIndex)
    {

    }
	VkResult swapchainz_handle::queuePresent(VkQueue queue, uint32_t imageIndex, VkSemaphore waitSemaphore)
    {

    }

    void swapchainz_handle::cleanup()
    {

    }


VkExtent2D swapchainz_handle::select_swap_2Dextent_from_surface_capabilities(const VkSurfaceCapabilitiesKHR& sc_z,const uint32_t& width,
                                                                                 const uint32_t& height,bool window_resize)
    {
      if((sc_z.currentExtent.width != std::numeric_limits<uint32_t>::max()) && (!window_resize))
      	{
      		std::cout <<"\n\tchooseSwapExtent[" << __FILE__ << ":" << __LINE__ <<"]:" << sc_z.currentExtent.width <<" x " << sc_z.currentExtent.height << std::flush;
      		return sc_z.currentExtent;
      	}

     else
      {
        std:: cout << "UNFINSHED>::: ::>>>>>>> get_drawable.. (window,&active_width,&active_height); /\
        \nFINSH THIS FUNCTION AND NAME IT? in select_swap_2Dextent_from_surface_capabilities\n\n";

        VkExtent2D new_extent;
        new_extent.width  = static_cast<uint32_t>(width);
        new_extent.height = static_cast<uint32_t>(height);
        return new_extent;
      }
    }