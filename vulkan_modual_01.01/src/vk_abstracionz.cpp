
#include "../headers/vk_abstracionz.hpp"




      void vk_utiltiyz::copyBuffer(VkDevice& device,VkCommandPool& in_commandPool, VkQueue& in_q, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
        VkCommandBuffer commandBuffer = beginSingleTimeCommands(device,in_commandPool);

        VkBufferCopy copyRegion{};
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

        endSingleTimeCommands(device,in_q,in_commandPool,commandBuffer);
    }   


    VkCommandBuffer vk_utiltiyz::beginSingleTimeCommands(VkDevice& device,VkCommandPool& in_commandPool) 
    {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = in_commandPool;
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        return commandBuffer;
}

void vk_utiltiyz::endSingleTimeCommands(VkDevice& device, VkQueue& in_q,VkCommandPool& in_commandPool, VkCommandBuffer commandBuffer) 
{
        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(in_q, 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(in_q);

        vkFreeCommandBuffers(device, in_commandPool, 1, &commandBuffer);
}



 VkCommandBuffer vk_utiltiyz::createCommandBuffer(VkDevice& logical_device,VkCommandBufferLevel level, VkCommandPool pool, bool begin)
	{
		

        	VkCommandBufferAllocateInfo commandBufferAllocateInfo {};
			commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			commandBufferAllocateInfo.commandPool = pool;
			commandBufferAllocateInfo.level = level;
			commandBufferAllocateInfo.commandBufferCount = 1;
		VkCommandBuffer cmdBuffer;

     if (vkAllocateCommandBuffers(logical_device, &commandBufferAllocateInfo, &cmdBuffer) != VK_SUCCESS) {
      throw std::runtime_error("failed to alllocae comd buffer in vk_utiltiyz createc0mand buffer!");
     }
		if (begin)
		{   
            	VkCommandBufferBeginInfo cmdBufferBeginInfo {};
			cmdBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			

            if (vkBeginCommandBuffer(cmdBuffer, &cmdBufferBeginInfo) != VK_SUCCESS) {
            }
		
		}
		return cmdBuffer;
	}


    void vk_utiltiyz::create_buffer(VkPhysicalDevice& phy_device, VkDevice& logical_device,VkDeviceSize dsize, VkBufferUsageFlags usage, 
    VkMemoryPropertyFlags proprerties, VkBuffer& buffer, VkDeviceMemory& buff_mem)
     {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = dsize;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

       if (vkCreateBuffer(logical_device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to create buffer!");
        }


        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(logical_device, buffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = vk_utiltiyz::findMemoryType(phy_device,memRequirements.memoryTypeBits, proprerties);

        if (vkAllocateMemory(logical_device, &allocInfo, nullptr, &buff_mem) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate buffer memory!");
        }

        vkBindBufferMemory(logical_device, buffer, buff_mem, 0);
    }

                  
    std::string memproflag_to_string(VkMemoryPropertyFlags inflag)
    {
        std::string outstring = "####PROPRTYLIST::";
        outstring += inflag;
        outstring += "\n";
        switch(inflag)
        {
        case  VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT :
    {
        outstring += "VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT\n";          
    }
        case  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT :
    {
        outstring += "VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT\n";         
    }
        case  VK_MEMORY_PROPERTY_HOST_COHERENT_BIT :
    {
        outstring += "VK_MEMORY_PROPERTY_HOST_COHERENT_BIT\n";           
    }

        case  VK_MEMORY_PROPERTY_HOST_CACHED_BIT :
    {
        outstring += "VK_MEMORY_PROPERTY_HOST_CACHED_BIT\n";          
    }

        case  VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT :
    {
        outstring += "VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT\n";        
    }

        case  VK_MEMORY_PROPERTY_PROTECTED_BIT :
    {
        outstring += "VK_MEMORY_PROPERTY_PROTECTED_BIT\n";      
    }

        case  VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD :
    {
        outstring += "VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD\n";        
    }

        case  VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD :
    {
        outstring += "VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD\n";        
    }
    //default : outstring = "FAILED TO DETECT>> OR ZERO.";
     }
    
    return outstring;
    }

    std::string memheapflag_to_string(VkMemoryHeapFlags flag)
    {
      std::string outstring = "####PROPRTYLIST::";
       outstring+= flag; 
       outstring += " \n";
        switch(flag)
        {
            case VK_MEMORY_HEAP_DEVICE_LOCAL_BIT: 
            {
                 outstring += "VK_MEMORY_HEAP_DEVICE_LOCAL_BIT\n";
            }

            case VK_MEMORY_HEAP_MULTI_INSTANCE_BIT :
            {
                  outstring += "VK_MEMORY_HEAP_MULTI_INSTANCE_BIT\n";
            }
          
        }

        return outstring;

    }

     uint32_t vk_utiltiyz::findMemoryType(VkPhysicalDevice& physicalDevice ,uint32_t typeFilter, VkMemoryPropertyFlags properties)
     {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);
    /*   #ifdef DEBUG_01
    
        std::cout<< " \n###########FINDEMMEORY_INFO::############# \n memoryTypeCount::" << memProperties.memoryTypeCount << '\n'
                 << "\n memoryHeapCount::" << memProperties.memoryHeapCount << "\n ####MEMORYTYPE INFO::############\n";

                 for(int i =0; i < memProperties.memoryTypeCount; i++)
                 {
                    std::cout << "\n->heapIndex" << memProperties.memoryTypes[i].heapIndex << 
                    "\npropertyFlags::"<< memproflag_to_string(memProperties.memoryTypes[i].propertyFlags)
                    <<"######################\n";
                 }
            std::cout << "\n#####MEMORYHEAPS::#######\n";
                 for(int i =0; i < memProperties.memoryHeapCount; i++)
                 {
                    std::cout << "\n->i::" << i << "\n->heapsize::" << memProperties.memoryHeaps[i].size << 
                    "\npropertyFlags::"<< memheapflag_to_string(memProperties.memoryHeaps[i].flags) <<"######################\n";
                 }
   
       #endif // DEBUG*/

        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
        
         {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                std::cout << "MEMORY INDEX SELCTED::" << i <<'\n';
               
                return i;
                
            }
        }

        throw std::runtime_error("failed to find suitable memory type!");
        
    }


     void vk_utiltiyz::createImage(VkPhysicalDevice& phsical_device, VkDevice& logical_device,uint32_t width, uint32_t height, uint32_t mipLevels, 
                                 VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image,
                                 VkDeviceMemory& imageMemory) {
        VkImageCreateInfo imageInfo{};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.extent.width = width;
        imageInfo.extent.height = height;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = mipLevels;
        imageInfo.arrayLayers = 1;
        imageInfo.format = format;
        imageInfo.tiling = tiling;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageInfo.usage = usage;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateImage(logical_device, &imageInfo, nullptr, &image) != VK_SUCCESS) {
            throw std::runtime_error("failed to create image!");
        }

        VkMemoryRequirements memRequirements;
        vkGetImageMemoryRequirements(logical_device, image, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = findMemoryType(phsical_device,memRequirements.memoryTypeBits, properties);

        if (vkAllocateMemory(logical_device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate image memory!");
        }

        vkBindImageMemory(logical_device, image, imageMemory, 0);
    }  

VkShaderModule vk_utiltiyz::create_shaderModual(const std::vector<unsigned int>& code, VkDevice& logical_device)
{
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = sizeof(code[0]) * code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        VkShaderModule shaderModule;
        if (vkCreateShaderModule(logical_device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
            throw std::runtime_error("failed to create shader module!");
        }

        return shaderModule;
}

VkShaderModule vk_utiltiyz::create_shaderModual(const std::vector<char>& code, VkDevice& logical_device)
{       
    #ifdef DEBUG_01
        std::cout << "create_shaderModual..size" << code.size() << '\n';
        std::cout << "create_shaderModual..bytesize" << (sizeof(code[0]) * code.size()) << '\n';
                std::cout << "create_shaderModual..charsize" << (sizeof(char) * code.size()) << '\n';


    #endif    
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = sizeof(code[0]) * code.size();

       
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
//exit(1);
        return details;
    }


VkImageView vk_utiltiyz::createImageView(VkDevice& in_device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels) {
        VkImageViewCreateInfo viewInfo{};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.image = image;
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewInfo.format = format;
        viewInfo.subresourceRange.aspectMask = aspectFlags;
        viewInfo.subresourceRange.baseMipLevel = 0;
        viewInfo.subresourceRange.levelCount = mipLevels;
        viewInfo.subresourceRange.baseArrayLayer = 0;
        viewInfo.subresourceRange.layerCount = 1;

        VkImageView imageView;
        if (vkCreateImageView(in_device, &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
            throw std::runtime_error("failed to create texture image view!");
        }

        return imageView;
    }


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

        std::cout<<"####QUEFAIMILZ::: TOTAL::queueFamilyCount"<< queueFamilyCount << '\n'; 
        
        bool found_graphic = false; 
        bool pandg_set = false; 
        for (const auto& queueFamily : queueFamilies) {

            std::cout << "QINDEX::" << i << '\n'; 
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphics_Family = i;
                std::cout << "#->@##VK_QUEUE_GRAPHICS_BIT found!\n";
                found_graphic = true;
            }

         if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT) {
                indices.compute_Family = i;
                  std::cout << "#->@##VK_QUEUE_COMPUTE_BIT found!\n";
            }

         if (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT) 
           {
                std::cout << "#->@##VK_QUEUE_TRANSFER_BIT found!\n";
                indices.transfer_Family = i;
            }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

        if (presentSupport && pandg_set == false)
             {
                std::cout << "#->@##present_Family found! at i::" << i << '\n';
                indices.present_Family = i;
                pandg_set = true;
             }
             
            i++;
        }
       std::cout << "compute_Family::"<< indices.compute_Family.value() << "   present_Family::" << indices.present_Family.value() << '\n';  
       // exit(1);    
        return indices;
    }
    
VkSurfaceFormatKHR vk_utiltiyz::select_surface_format(std::vector<VkSurfaceFormatKHR>& formatez)
    {
        std::cout << "NUMOFFORMATE ABALBLE::" << formatez.size() << '\n';
         return{ VK_FORMAT_B8G8R8A8_UNORM, VK_COLORSPACE_SRGB_NONLINEAR_KHR };
        for (const auto& availableFormat : formatez) {
            std::cout << "formate>>" << availableFormat.format << '\n';
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                std::cout << "#########select_surface_format::FORMATE::VK_FORMAT_B8G8R8A8_SRGB\n";
              //  return availableFormat;
            }
        }
   

         if( (formatez.size() == 1) &&(formatez[0].format == VK_FORMAT_UNDEFINED) )
        {
            std::cout << "#############there was only one. oh no\n";
                   }
        std::cout << "SOMEOTHER FORMATE AT ZEROPOS>>>\n";
       
        // return formatez[0];
        /*
        
       
    for( VkSurfaceFormatKHR &surface_format : formatez)
    {
        if( surface_format.format ==  )
        {
           return surface_format;
        }
    }// Return the first format from the

    return formatez[0];
*/
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
