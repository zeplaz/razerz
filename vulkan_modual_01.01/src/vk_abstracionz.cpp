
#include "../headers/vk_abstracionz.hpp"


  
    void swapchainz_handle::create(uint32_t& width, uint32_t& height,bool resize, VkPhysicalDevice& phy_device,VkSurfaceKHR& in_surface,VkDevice& logical_device,
     bool vsync)
    {

     VkSwapchainKHR old_sw_chain = swapchain;
        
       

    swapchain_support_details swapchain_details = vk_utiltiyz::query_swapchain_support(phy_device,in_surface);  

      VkSurfaceFormatKHR surfaceFormat = vk_utiltiyz::select_surface_format(swapchain_details.formats);


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

        createInfo.minImageCount = image_Count;
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

        vkGetSwapchainImagesKHR(logical_device, swapchain, &image_Count, nullptr);
        sc_images.resize(image_Count);
        vkGetSwapchainImagesKHR(logical_device, swapchain, &image_Count, sc_images.data());

        sc_colorFormat = surfaceFormat.format;
        sc_extent = extent;
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



VkShaderModule vk_utiltiyz::create_shaderModual(const std::vector<char>& code, VkDevice& logical_device)
{
  VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        VkShaderModule shaderModule;
        if (vkCreateShaderModule(logical_device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
            throw std::runtime_error("failed to create shader module!");
        }

        return shaderModule;   
}


        VkFormat vk_utiltiyz::findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features,VkPhysicalDevice& phy_device) {
        for (VkFormat format : candidates) {
            VkFormatProperties props;
            vkGetPhysicalDeviceFormatProperties(phy_device, format, &props);

            if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
                return format;
            } else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
                return format;
            }
        }

        throw std::runtime_error("failed to find supported format!");
    }

    VkFormat vk_utiltiyz::findDepthFormat(VkPhysicalDevice& phy_device) {
        return findSupportedFormat(
            {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
            VK_IMAGE_TILING_OPTIMAL,
            VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT,phy_device
        );
    }

std::vector<const char*> vk_utiltiyz::getRequiredExtensions() {
     
#ifdef USEZ_GLFW
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = //glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);    

#else 
    std::vector<const char*> extensions(DEF_Instance_extentions);      
#endif 
    
    if (enableValidationLayers) 
    {
     extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    std::cout << "\n\n ######DEBGUGE___TRASEING EXTENTIONZ>>>getRequiredExtensions::>number of exentions::need::" << extensions.size() << '\n';
    return extensions;     
    
    }


    std::vector<VkExtensionProperties> vk_utiltiyz::supported_device_extentions(VkPhysicalDevice& device)
    {
        uint32_t extention_count;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extention_count, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extention_count);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extention_count, availableExtensions.data());

    #ifdef DEBUG_01
        
               std::string temp= "#######DEBUG####AVALIABLE DEVICE EXTENTIONS ON DEVICE::aMUSTctiaveoutput\n:";
           // logging(temp.data());
          //  logging(device);
            for(int i =0; i < availableExtensions.size(); i++)
                {
                   // logging(availableExtensions.at(i).extensionName);
                }
               
          // std::cout << "#######DEBUG####AVALIABLE DEVICE EXTENTIONS see file logger.logtx ON DEVICE:::" <<  device << '\n';
         /*for (auto it = availableExtensions.begin();it != availableExtensions.end(); ++it) 
                 
            
                 std::cout << "#->extensionName::" << it->extensionName << '\n'
                 << "specVersion::" << it->specVersion << "\n***************\n" ;
              

        } */ 
    #endif
        return availableExtensions;
        
    }


    VkPresentModeKHR vk_utiltiyz::select_present_mode(const std::vector<VkPresentModeKHR>& pmode)
       {
        for (const auto& availablePresentMode : pmode)
        {
         if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
         {
             std::cout << "####MAILBOX PRESENT_MODE***********########*****\n\n";
            return availablePresentMode;
         }
        }
    std::cout << "####FIFO PRESENT_MODE***********########*****\n\n";
    return VK_PRESENT_MODE_FIFO_KHR;
    }

    bool vk_utiltiyz::check_required_device_extentions(VkPhysicalDevice& device)
    {
    std::set<std::string> requiredExtensions(DEF_Device_Extensions.begin(), DEF_Device_Extensions.end());


    for (const auto& extension : vk_utiltiyz::supported_device_extentions(device)) {

               
      // SENDTHIS TO LOGGER   std::cout << "\n ######DEBGUGE__extension.extensionName:::" << extension.extensionName << '\n';
            requiredExtensions.erase(extension.extensionName);
            
        }
#ifdef DEBUG_01
    std::cout << "\n\n ######DEBGUGE___TRASEING EXTENTIONZ>>>check_required_extentions::>numrequiredExtensions:: afterpuge" << requiredExtensions.size() << '\n';
    if(!requiredExtensions.empty())
    {   
      std::for_each(requiredExtensions.cbegin(), requiredExtensions.cend(), [](std::string x) 
        {
            std::cout << "\n ######DEBGUGE___TRASEING EXTENTIONZ>>>check_required_extentions::> FAILDED TO FIND:::" << x << '\n';
        });
    }
#endif 
        return requiredExtensions.empty();
    }   


    swapchain_support_details vk_utiltiyz::query_swapchain_support(VkPhysicalDevice& device, VkSurfaceKHR& in_surface )
     {
        std::cout << "\n*****************###DEBUG:: swapchain_support_details query swapchain_support\n\********************\n"; 
        swapchain_support_details details;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, in_surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, in_surface, &formatCount, nullptr);

        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, in_surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, in_surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, in_surface, &presentModeCount, details.presentModes.data());
        }





#ifdef DEBUG_01
       
        std::cout << "\n\n###::::PRINTOUT OF swap chain support details|||######\n" << 
        "\n #####capablitiez######:: VkSurfaceCapabilitiesKHR\n"<< 
        "minImageCount::       " << details.capabilities.minImageCount <<'\n'<< 
        "maxImageCount::       " << details.capabilities.maxImageCount <<'\n'<< 
        "currentExtent.width:: " << details.capabilities.currentExtent.width <<'\n'<< 
        "currentExtent.height::" << details.capabilities.currentExtent.height <<'\n'<< 
        "minImageExtent:: "      << details.capabilities.minImageExtent.width <<'\n'<< 
        "minImageExtent:: "      << details.capabilities.minImageExtent.height <<'\n'<<
        "maxImageExtent.width::" << details.capabilities.maxImageExtent.width <<'\n'<<
        "maxImageExtent.height::"<< details. capabilities.maxImageExtent.height <<'\n'<<
        "maxImageArrayLayers::"  << details.capabilities.maxImageArrayLayers <<'\n'<<
        "SUPPORTED::VkSurfaceTransformFlagsKHR:: "<< details.capabilities.currentTransform <<'\n'<<
        "CURRENT::VkSurfaceTransformFlagBitsKHR::"<< details.capabilities.currentTransform <<'\n'<< 
        "SUPPORTED::VkCompositeAlphaFlagsKHR "    << details.capabilities.supportedCompositeAlpha <<'\n'<<
        "SUPPORTED::VkImageUsageFlags "           << details.capabilities.supportedUsageFlags <<'\n'<< "******************\n";


        std:: cout <<  "\n###::::Detailz::vksurfaceformateKHR:::\n";
        for(int i =0; i<details.formats.size(); i++)
        {   
            
            std::cout << "->##at index::" << i << '\n'  
                      << "-#->#VkFormat:::" << details.formats.at(i).format <<'\n'
                      << "-#->#VkColorSpaceKHR:::" << details.formats.at(i).colorSpace <<'\n';
        }

        std::cout << "\n ###::::Detailz::VkPresentModeKHR:::\n";
        for(int i =0; i<details.presentModes.size(); i++)
        {
          std::cout <<  "->##at index::" << i << '\n'<<  "-#->#VkPresentModeKHR" << details.presentModes.at(i) << '\n';
        }

     std:: cout <<  "\n###::::###ENDDD30####:::\n";
        #endif

        return details;
    };

bool vk_utiltiyz::checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

       
    for (const auto& layerProperties : availableLayers) 
     {
        std::cout << "##DEBUG:::AVALIABLE::LAYERZ::layerProperties layerName:: " << layerProperties.layerName << "\n***********" << '\n';
     }
          
    for (const char* layerName : validation_layerz) {
        bool layerFound = false;
        
        for (const auto& layerProperties : availableLayers) {

         if (strcmp(layerName, layerProperties.layerName) == 0) 
         {
            std::cout << "#####Layer activated::" <<  layerProperties.layerName <<'\n'<<'\n';
            layerFound = true;
            break;
          }
          }

        if (!layerFound) {
           std::cout << "#####ERROR_DEBUG:::layer vaidation has faild.. hope itz not debug mode...\n*****\n";
           return false;
           }
        }
        std::cout << "\n#####layers vaildaed...contune with debug setup.\n";
        return true;

}


    queue_family_indices vk_utiltiyz::get_que_fammily_indicas(VkPhysicalDevice& device, VkSurfaceKHR& surface )
     {

        queue_family_indices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphics_Family = i;
                std::cout << "#->@##VK_QUEUE_GRAPHICS_BIT found!\n";
            }

         if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT) {
                indices.compute_Family = i;
                  std::cout << "#->@##VK_QUEUE_COMPUTE_BIT found!\n";
            }

                 if (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT) {
                       std::cout << "#->@##VK_QUEUE_TRANSFER_BIT found!\n";
                indices.transfer_Family = i;
            }

    VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

            if (presentSupport) {
                  std::cout << "#->@##present_Family found!\n";
                indices.present_Family = i;
            }

            if (indices. does_exist()) {
                break;
            }

            i++;
        }

        return indices;
    }


         VkSurfaceFormatKHR vk_utiltiyz::select_surface_format(std::vector<VkSurfaceFormatKHR> & formatez)
    {
        if( (formatez.size() == 1) &&(formatez[0].format == VK_FORMAT_UNDEFINED) ) 
        {
            return{ VK_FORMAT_R8G8B8A8_UNORM, VK_COLORSPACE_SRGB_NONLINEAR_KHR };
        }
    for( VkSurfaceFormatKHR &surface_format : formatez) 
    {
        if( surface_format.format == VK_FORMAT_R8G8B8A8_UNORM ) 
        {
           return surface_format;
        }
    }// Return the first format from the 
    
    return formatez[0];

    }


  bool vk_utiltiyz::get_queueFamily(const VkPhysicalDevice& phycal_device, VkQueueFlagBits flags, uint32_t& queue_family_index) 
   {
       uint32_t queue_family_count =0;
       
       vkGetPhysicalDeviceQueueFamilyProperties(
           phycal_device, &queue_family_count, 
           nullptr);

       VkQueueFamilyProperties* qu_families = new VkQueueFamilyProperties[queue_family_count];
      
       vkGetPhysicalDeviceQueueFamilyProperties(
           phycal_device,
           &queue_family_count, 
           qu_families);

    for(uint32_t i = 0; i< queue_family_count; i++)
    {   

       // vkGetPhysicalDeviceXcbPresentationSupportKHR(phycal_device,qu_families[i],m_window.connection,m_window.screen->root_visual)
      if(qu_families[i].queueCount > 0)
       {
        if(qu_families[i].queueFlags & flags)
         {
             delete[] qu_families;
             return true;
         }
       }        
    }    delete[] qu_families;
    return false;  
   }

