
#include "../headers/vulkan_api.hpp"

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

#include <queue>
//#include  <experimental/array>


#ifdef _WIN32
bool in_callback = false;
#define ERR_EXIT(err_msg, err_class)                                             \
    do {                                                                         \
        if (!demo->suppress_popups) MessageBox(NULL, err_msg, err_class, MB_OK); \
        exit(1);                                                                 \
    } while (0)
void DbgMsg(char *fmt, ...) {
    va_list va;
    va_start(va, fmt);
    vprintf(fmt, va);
    va_end(va);
    fflush(stdout);
}

#elif defined __ANDROID__
#include <android/log.h>
#define ERR_EXIT(err_msg, err_class)                                           \
    do {                                                                       \
        ((void)__android_log_print(ANDROID_LOG_INFO, "Vulkan Cube", err_msg)); \
        exit(1);                                                               \
    } while (0)
#ifdef VARARGS_WORKS_ON_ANDROID
void DbgMsg(const char *fmt, ...) {
    va_list va;
    va_start(va, fmt);
    __android_log_print(ANDROID_LOG_INFO, "Vulkan Cube", fmt, va);
    va_end(va);
}
#else  // VARARGS_WORKS_ON_ANDROID
#define DbgMsg(fmt, ...)                                                                  \
    do {                                                                                  \
        ((void)__android_log_print(ANDROID_LOG_INFO, "Vulkan Cube", fmt, ##__VA_ARGS__)); \
    } while (0)
#endif  // VARARGS_WORKS_ON_ANDROID
#else
#define ERR_EXIT(err_msg, err_class) \
    do {                             \
        printf("%s\n", err_msg);     \
        fflush(stdout);              \
        exit(1);                     \
    } while (0)
void DbgMsg(char *fmt, ...) {
    va_list va;
    va_start(va, fmt);
    vprintf(fmt, va);
    va_end(va);
    fflush(stdout);
}
#endif



vulkan_app::vulkan_app()
{
    vk_api = new vulkan_api();
}
void vulkan_app::loop()
{
    vk_api->renderLoop();
}

bool vulkan_app::vulkan_inialz()
    {
         vk_api->inaltize_vulkan_instance();

        vk_utiltiyz::checkValidationLayerSupport();

        vk_api->create_surface();
        
        vk_api->select_Physical_Device();

        vk_api->create_Logical_Device();
        vk_api->create_swap_Chain();
        vk_api->create_swapchan_imageviews();

        vk_api->create_rednerpass();
        vk_api->createDescriptorSetLayout();
       // vk_api.setup_Debugger();     
      
       //createGraphicsPipeline();
    };

void vulkan_api::createDescriptorSetLayout()
{
    //this needs to be moved to a modfiable situation...
        VkDescriptorSetLayoutBinding vertex_compute_uboLayoutBinding{};
        vertex_compute_uboLayoutBinding.binding = 0;
        vertex_compute_uboLayoutBinding.descriptorCount = 1;
        vertex_compute_uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        vertex_compute_uboLayoutBinding.pImmutableSamplers = nullptr;
        vertex_compute_uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutBinding compute_compute_image_buf_LayoutBinding{};
        compute_compute_image_buf_LayoutBinding.binding = 1;
        compute_compute_image_buf_LayoutBinding.descriptorCount = 2;
        compute_compute_image_buf_LayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
        compute_compute_image_buf_LayoutBinding.pImmutableSamplers = nullptr;
        compute_compute_image_buf_LayoutBinding.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;


}
void vulkan_api::create_rednerpass()
{       std::cout << "||->#############VULKAN__APICREATE RENDERCHAIN>#############################\n ";
        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = swapchan_handle.sc_imageFormat;
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentDescription depthAttachment{};
        depthAttachment.format = vk_utiltiyz::findDepthFormat(vk_occurance.physical_Device);
        depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkAttachmentDescription present_attachment = {};
        present_attachment.format =  swapchan_handle.sc_imageFormat;
		present_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
		present_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;				// Each subpass (or frame as we only have 1 subpass) we want to clear the last present
		present_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;				// What do we want to do with the data after the subpass, we want to store it away
		present_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;		// Dont use stencil currently
		present_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;	// Dont use stencil currently 
		present_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;			// The layout the attachment image subresource, in out case its undefined
		present_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;	

        VkAttachmentReference colorAttachmentRef{};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkAttachmentReference depthAttachmentRef{};
        depthAttachmentRef.attachment = 1;
        depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;
        subpass.pDepthStencilAttachment = &depthAttachmentRef;

        VkSubpassDependency dependency{};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        std::array<VkAttachmentDescription, 2> attachments = {colorAttachment, depthAttachment};
        VkRenderPassCreateInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        renderPassInfo.pAttachments = attachments.data();
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;
        renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies = &dependency;

        if (vkCreateRenderPass(vk_occurance.logical_device, &renderPassInfo, nullptr, &vk_occurance.render_Pass) != VK_SUCCESS) {
            throw std::runtime_error("failed to create render pass!");
        }
    }


bool vulkan_api::create_Logical_Device()
{
    queue_family_indices indices = vk_utiltiyz::get_que_fammily_indicas(vk_occurance.physical_Device,vk_occurance.surface);
    
    std::vector<VkDeviceQueueCreateInfo> d_q_createinfo_container;
    std::set<uint32_t> unique_queue_families{indices.graphics_Family.value(),indices.present_Family.value(),indices.compute_Family.value()}; 

    float queue_priority =DEFAULT_1_PRIORITY;

    for(uint32_t queue_family : unique_queue_families)
    {
        VkDeviceQueueCreateInfo queue_create_info{};
        queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_create_info.queueFamilyIndex = queue_family;
        queue_create_info.queueCount = 1;
        queue_create_info.pQueuePriorities = &queue_priority; 
        d_q_createinfo_container.push_back(queue_create_info);
    }

    VkPhysicalDeviceFeatures device_features{};
    device_features.samplerAnisotropy = VK_TRUE;
        /*
          device_features. = VK_TRUE; 
         *********************************** 
        device_features.tessellationShader = VK_TRUE; 
        device_features.dualSrcBlend = VK_TRUE; 
        device_features.multiViewport = VK_TRUE; 
        device_features.pipelineStatisticsQuery = VK_TRUE; 
        device_features.shaderStorageImageMultisample = VK_TRUE; 
        device_features.variableMultisampleRate = VK_TRUE; 
        device_features.geometryShader = VK_TRUE; 
        device_features.shaderStorageImageReadWithoutFormat = VK_TRUE; 
        device_features.shaderStorageImageWriteWithoutFormat = VK_TRUE; 
        device_features.shaderUniformBufferArrayDynamicIndexing = VK_TRUE; 
        device_features.shaderSampledImageArrayDynamicIndexing = VK_TRUE; 
        device_features.shaderStorageBufferArrayDynamicIndexing = VK_TRUE; 
        device_features.shaderStorageImageArrayDynamicIndexing = VK_TRUE;
    

        */
    VkDeviceCreateInfo create_info{};
    create_info.sType  = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    
    create_info.queueCreateInfoCount = static_cast<uint32_t>(d_q_createinfo_container.size());
    create_info.pQueueCreateInfos = d_q_createinfo_container.data();

    create_info.pEnabledFeatures = &device_features;

    create_info.enabledExtensionCount = static_cast<uint32_t>(DEF_Device_Extensions.size());
    create_info.ppEnabledExtensionNames = DEF_Device_Extensions.data();

 if (enableValidationLayers) {
            create_info.enabledLayerCount = static_cast<uint32_t>(validation_layerz.size());
            create_info.ppEnabledLayerNames = validation_layerz.data();
        } else {
            create_info.enabledLayerCount = 0;
        }


     if (vkCreateDevice(vk_occurance.physical_Device, &create_info, nullptr, &vk_occurance.logical_device) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }

    vkGetDeviceQueue(vk_occurance.logical_device,indices.graphics_Family.value(),0,&vk_occurance.graphics_queue);
    vkGetDeviceQueue(vk_occurance.logical_device,indices.compute_Family.value(),0,&vk_occurance.compute_queue);
    vkGetDeviceQueue(vk_occurance.logical_device,indices.present_Family.value(),0,&vk_occurance.present_queue);

}


/*
####*************************
*****************PLATFORM SPSIFIC CODE FOR WINDOW AND SCREEN CREATION 
#***********************
*/





#if defined(__linux__)

    void vulkan_api::resize_window_xcb(int h, int w, int x, int y)
    {
        uint32_t values[4];
        values[0] = x;
        values[1] = y;
        values[2] = w;
        values[3] = h;
     xcb_configure_window(m_window.connection_ptr, m_window.window_handle, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, values);
    }

void vulkan_api::renderLoop() {
  bool result = true;   
  bool running = true;
  xcb_generic_event_t *event;
  xcb_client_message_event_t *cm;

  while (running) {


   //event = xcb_wait_for_event(m_window.connection_ptr);
    event = xcb_poll_for_event(m_window.connection_ptr);
   
  
   
  
   if( event ) {
       //0x7f or ~0x80
        std::cout << "xcb__EVENT:::" << event->response_type << '\n'; 

    switch (event->response_type &0x7f) {
      
      
        case XCB_CONFIGURE_NOTIFY: {

             std::cout << "#####DEBUG__XCB_CONFIGURE_NOTIFY\:::\n";
              xcb_configure_notify_event_t *configure_event = (xcb_configure_notify_event_t*)event;
             
             // active_width = configure_event->width;
            //  active_height = configure_event->height;
              
              if( ((configure_event->width > 0) && (active_width != configure_event->width)) ||
                ((configure_event->height > 0) && (active_height != configure_event->height)) ) {

                std::cout << "configurevemt h and w  h::" << active_height << "w::" << active_width << '\n';
    
                window_resize_event = true;
                active_width = configure_event->width;
                active_height = configure_event->height;

                 std::cout << "configurevemt is not the same as the one that it iswindow_resize_event = true... ::" << active_height << "w::" << active_width << '\n';
              }
            }
        break;
      
      case XCB_CLIENT_MESSAGE: {
        cm = (xcb_client_message_event_t *)event;

        if (cm->data.data32[0] == m_window.wmDeleteWin) running = false;

        break;
      }
    }

    free(event);
   } else {
     
          // Draw
          if( window_resize_event ) {

              on_window_resize(m_window.window_handle, active_width, active_height);
              std::cout << "somelost else...window rezise is called did it happen. does this need mpore filling out utilzie the intel method.. \nSource code examples for API without Secrets: Introduction to Vulkan";
            window_resize_event = false;
            //if( !project.OnWindowSizeChanged() ) {
           //   result = false;
            //  break;
           // }
          }}
         /* if( project.ReadyToDraw() ) {
         //   if( !project.Draw() ) {
         //     result = false;
         //     break;
            }
          } else {
              std::cout << "\n************\n###ReadyToDraw false####YOU SHOULD HAVE A THREAD SLEEP HERE/\n***********\n";
            //std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
          }*/
        
        //    return result;
  }

  xcb_destroy_window(m_window.connection_ptr, m_window.window_handle);
}

void vulkan_api::create_surface()
{

        this->createWindow();

        VkXcbSurfaceCreateInfoKHR surfaceCreateInfo = {};
        surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
        surfaceCreateInfo.pNext = NULL;
        surfaceCreateInfo.flags = 0;
        surfaceCreateInfo.connection = m_window.connection_ptr;
        surfaceCreateInfo.window = m_window.window_handle;


        VkResult result =
    vkCreateXcbSurfaceKHR(vk_occurance.vk_instance, &surfaceCreateInfo, NULL, &vk_occurance.surface);
    if(!result == VK_SUCCESS)
    {
        std::cerr<< "\\\n###########EEROROROROROROSUFFCAE FAUKED TI CREATE<in manual window mode..\n,,";
        exit(-4);
    }
}

void vulkan_api::createWindow() 
{

    int screenp = 0;
    m_window.connection_ptr = xcb_connect(NULL, &screenp);

    if (xcb_connection_has_error(m_window.connection_ptr))
    {
        std::cerr << "\n############ERRRRRRRROOOOOOOOOOOOOO\nFailed to connect to X server using XCB.\n\n";
        exit(-5);
    }
 
     active_width= PRESET_VULK_WIDTH;
     active_height =  PRESET_VULK_HEIGHT;
  xcb_screen_iterator_t iter =
    xcb_setup_roots_iterator(xcb_get_setup(m_window.connection_ptr));

for (int s = screenp; s > 0; s--)
    xcb_screen_next(&iter);

   m_window.screen_ptr = iter.data; 

   m_window.window_handle = xcb_generate_id(m_window.connection_ptr);

    uint32_t eventMask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    uint32_t valueList[] = { m_window.screen_ptr->black_pixel,  XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_STRUCTURE_NOTIFY };



xcb_create_window(
    m_window.connection_ptr,
    XCB_COPY_FROM_PARENT,
    m_window.window_handle,
    m_window.screen_ptr->root,
    0,
    0,
    PRESET_VULK_WIDTH,
    PRESET_VULK_HEIGHT,
    0,
    XCB_WINDOW_CLASS_INPUT_OUTPUT,
    m_window.screen_ptr->root_visual,
    eventMask,
    valueList);
    
    xcb_change_property(
    m_window.connection_ptr,
    XCB_PROP_MODE_REPLACE,
    m_window.window_handle,
    XCB_ATOM_WM_NAME,
    XCB_ATOM_STRING,
    8,
    strlen(APPLICATION_NAME),
    APPLICATION_NAME);

    xcb_change_property(m_window.connection_ptr, XCB_PROP_MODE_REPLACE, m_window.window_handle,
                        XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8,
                        strlen(APPLICATION_NAME), APPLICATION_NAME);

    xcb_intern_atom_cookie_t wmDeleteCookie = xcb_intern_atom(
        m_window.connection_ptr, 0, strlen("WM_DELETE_WINDOW"), "WM_DELETE_WINDOW");
    xcb_intern_atom_cookie_t wmProtocolsCookie =
        xcb_intern_atom(m_window.connection_ptr, 0, strlen("WM_PROTOCOLS"), "WM_PROTOCOLS");
    xcb_intern_atom_reply_t *wmDeleteReply =
        xcb_intern_atom_reply(m_window.connection_ptr, wmDeleteCookie, NULL);
    xcb_intern_atom_reply_t *wmProtocolsReply =
        xcb_intern_atom_reply(m_window.connection_ptr, wmProtocolsCookie, NULL);
    m_window.wmDeleteWin = wmDeleteReply->atom;
    m_window.wmProtocols = wmProtocolsReply->atom;

    xcb_change_property(m_window.connection_ptr, XCB_PROP_MODE_REPLACE, m_window.window_handle,
                        wmProtocolsReply->atom, 4, 32, 1, &wmDeleteReply->atom);

        xcb_map_window(m_window.connection_ptr, m_window.window_handle);
        xcb_flush(m_window.connection_ptr);
    
    std::cout <<"\n***********\n|||||||||####WINDOW CREATED FINSHED>>>||||||\n\n";

  }


#endif // __LINUX__
                               
    

VkInstanceCreateInfo instance_CreateInfo(VkApplicationInfo & app_info,const 
                     std::vector<const char*>& extensions, unsigned int extensions_count,
                     const std::vector<const char*>& layers, unsigned int layerCount)
{
	VkInstanceCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	info.pApplicationInfo = &app_info;                          // Pointer to the application information created
	info.enabledExtensionCount = extensions_count;              // The amount of extensions we wish to enable
	info.ppEnabledExtensionNames = extensions.data();                  // The raw data of the extensions to enable
	
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        if (enableValidationLayers) {
            info.enabledLayerCount = static_cast<uint32_t>(layers.size());
            info.ppEnabledLayerNames = layers.data();

            external_vulkan::populateDebugMessengerCreateInfo(debugCreateInfo);
            info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        } else {
            info.enabledLayerCount = 0;

            info.pNext = nullptr;
        }
                        // The raw data of the layers to enable
	return info;
}


void vulkan_api::setupDebugMessenger() {
        if (!enableValidationLayers) return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        external_vulkan::populateDebugMessengerCreateInfo(createInfo);

        if (external_vulkan::CreateDebugUtilsMessengerEXT(vk_occurance.vk_instance, &createInfo, nullptr, &vk_occurance.debugMessenger) != VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug messenger!");
        }
    }

   void vulkan_api::inaltize_vulkan_instance()

   {
    VkApplicationInfo vk_app_info{};
    vk_app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    vk_app_info.pApplicationName = APPLICATION_NAME;
    vk_app_info.applicationVersion = VK_MAKE_VERSION(1,0,0);
    vk_app_info.pEngineName = "vk_engine_test";
    vk_app_info.engineVersion = VK_MAKE_VERSION(1,0,0);
    vk_app_info.apiVersion    = VK_MAKE_VERSION(1,2,0); 

    auto extensions = vk_utiltiyz::getRequiredExtensions();

        
    VkInstanceCreateInfo create_inst_info = instance_CreateInfo(vk_app_info,extensions,
                                                               static_cast<uint32_t>(extensions.size()),
                                                               validation_layerz,layer_count);   
   
     
        if (vkCreateInstance(&create_inst_info, nullptr, &vk_occurance.vk_instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
 

    std::cout << "\n####_cCrEATEed INSTANCE:\n";//::::...vkruslt:::" <<  vk_result << "\n #####\n"; 

   }


  


    int32_t vulkan_api::device_score(VkPhysicalDeviceProperties& in_pdp,VkPhysicalDeviceFeatures& in_pdf)
    {
                
                
    int32_t pointz=1;        
   // pointz +=in_pdp.limits.maxUniformBufferRange;
    //pointz +=in_pdp.limits.maxMemoryAllocationCount;
    pointz +=in_pdp.limits.maxSamplerAllocationCount;
    ///pointz +=in_pdp.limits.maxStorageBufferRange%4; 
std::cout << "=" << pointz <<"POINTZ\n|##"; 
    pointz *=in_pdp.limits.maxColorAttachments;

    if(in_pdf.geometryShader)
    pointz *=2;
    std::cout << "=" << pointz <<"POINTZ\n|##"; 
    
    if(in_pdf.multiViewport)
    pointz *=3; //static_cast<uint>(in_pdf.geometryShader)*2*(pointz + in_pdf.geometryShader);
    std::cout << "=" << pointz <<"POINTZ\n|##"; 
    
    if(in_pdf.tessellationShader)
    pointz *=7; //static_cast<uint>(in_pdf.multiViewport)*3*(pointz + in_pdf.multiViewport);
    std::cout << "=" << pointz <<"POINTZ\n|##"; 
   
    switch(in_pdp.deviceType)
    {
    case VK_PHYSICAL_DEVICE_TYPE_OTHER :         pointz *= 10000;
    break; 
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: pointz *= 100;
    break;
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:   pointz *= 1000;
    break; 
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:    pointz *= 10;
    break;   
    case VK_PHYSICAL_DEVICE_TYPE_CPU:             pointz /= 10;
    break;
    }
    std::cout << "=" << pointz <<"POINTZ\n|##"; 

    return pointz; 

    }


    bool vulkan_api::select_Physical_Device()
    {
        uint32_t device_count = 0;
       // std::vector<std::pair<int32_t,int>> device_records_scorecard;
        std::vector<device_score_card> device_records_scorecard; 
        std::priority_queue<device_score_card,std::vector<device_score_card>,dev_comper> pq2_score;

        vkEnumeratePhysicalDevices(vk_occurance.vk_instance,&device_count,nullptr);

        if(device_count ==0)
        {
        std::cerr << "\n###ERRROR NO DEVICE DETECTED>>>OHNONO!!####\n##############\n";
        return false;
        }
        else 
        {
            std::cout << "DEVICES FOUND:::total number::" << device_count << '\n';    
        }

        
        std::vector<VkPhysicalDevice> devices(device_count);
        vkEnumeratePhysicalDevices(vk_occurance.vk_instance,&device_count,devices.data());
        
        std::vector<int32_t> device_points(device_count);
        VkPhysicalDeviceProperties phy_dev_prop;   
        VkPhysicalDeviceFeatures  phy_dev_feturez;   

        for(int i =0; i < device_count; i++)
        {
            

        //VkPhysicalDeviceFeatures2 phy_dev_feturez2;
       // VkPhysicalDeviceFeatures2KHR phy_dev_feturez2KHR;
        
        vkGetPhysicalDeviceFeatures(devices.at(i),&phy_dev_feturez);
        //vkGetPhysicalDeviceFeatures2(devices.at(i),&phy_dev_feturez2);
        // vkGetPhysicalDeviceFeatures2KHR(devices.at(i),&phy_dev_feturez2KHR);
        std::cout << phy_dev_feturez;
        
        vkGetPhysicalDeviceProperties(devices.at(i),&phy_dev_prop);
         

        std::cout << "####VkPhysicalDeviceProperties for device::" << i << '\n' <<
        "#apiVersion:: " << phy_dev_prop.apiVersion << '\n'
        << VK_VERSION_MAJOR(phy_dev_prop.apiVersion) << '.'
        << VK_VERSION_MINOR(phy_dev_prop.apiVersion) << '.'
        << VK_VERSION_PATCH(phy_dev_prop.apiVersion) << '.' << '\n' <<
        "#driverVersion:: " << phy_dev_prop.driverVersion << '\n'<<
        "deviceID:: " << phy_dev_prop.deviceID << '\n'<<
        "DeviceName:: " << phy_dev_prop.deviceName << '\n'<<
        "#VendorID:: " << phy_dev_prop.vendorID << '\n'<<
        "pipelineCacheUUID:: " << phy_dev_prop.pipelineCacheUUID << '\n' 
         << phy_dev_prop.limits << "#***\n"<<
          phy_dev_prop.deviceType << "*******#######\n"<<'\n';
        
             // ADD VkPhysicalDeviceLimits .. huge list " " << phy_dev_prop. << '\n'<<
        
          device_points.at(i) =  device_score(phy_dev_prop,phy_dev_feturez);
          

          if(!vk_utiltiyz::check_required_device_extentions(devices.at(i)))
          {
              device_points.at(i)*-1;
          } 
        std::cout<< "\n###->#Device_pointz:::index::" << i << "\n#POINTZ::" << device_points.at(i) << "||###\n\n";

          
        //std::pair<int32_t,int> device_pair_score = std::make_pair(device_points.at(i),i);
         device_score_card dsc;
         dsc.index = i;
         dsc.score =  device_points.at(i);
        // device_records_scorecard.push_back(dsc);
         pq2_score.push(dsc);
        }
       
        //std::priority_queue<device_score_card> pq_sore(device_records_scorecard);
      
         // 
        vk_occurance.physical_Device = devices.at(pq2_score.top().index);
        std::cout << "WInNER DEVICE INDEX::" << pq2_score.top().index <<'\n';
        vkGetPhysicalDeviceProperties((devices.at(pq2_score.top().index)),&phy_dev_prop);

        apiVersion = phy_dev_prop.apiVersion; 
    


        vkGetPhysicalDeviceMemoryProperties(vk_occurance.physical_Device, &vk_occurance.device_memory_properties);
        return true; 
    }
       /* int priorty_device(std::vector<std::pair<int32_t,int>>& in_sk_rk)
        {
       
        }

    /* std::priority_queue<int32_t> 
        std::map<int32_t,int> device_sorted = 
        std::make_heap (device_points.begin(),device_points.end());
        if()
     
*/

    
      /*  for(const auto& device : devices)
        {
            if (isDeviceSuitable(device))
            {
                physicaldevice
            }
        }
         */  
        /*
       for(uint32_t i =0; i<device_count;i++)
        {           
       //     VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT 
        }
        return true;*/
               
    



  

   void vulkan_api::device_setup(){}


   std::ostream& operator<<(std::ostream& os, const VkPhysicalDeviceFeatures& vkpdf)
   {

       /*
               "::"  << vkpdf. <<'\n'  << 
        */   
       os << "\n########VkPhysicalDeviceFeatures###\n" <<

        "imageCubeArray::"  << vkpdf.imageCubeArray << '\n' << 
        "independentBlend::"  << vkpdf.independentBlend << '\n' <<
        "##***geometryShader****::"  << vkpdf.geometryShader << '\n' <<
        "tessellationShader::"  << vkpdf.tessellationShader << '\n' <<
        "dualSrcBlend::"  << vkpdf.dualSrcBlend << '\n' <<
        "##****multiViewpor*****t::"  << vkpdf.multiViewport << '\n' <<
        "samplerAnisotropy::"  << vkpdf.samplerAnisotropy << '\n' <<
        "pipelineStatisticsQuery::"  << vkpdf.pipelineStatisticsQuery << '\n' <<
        "variableMultisampleRate::"  << vkpdf.variableMultisampleRate << '\n' <<
        "vertexPipelineStoresAndAtomics::"  << vkpdf.vertexPipelineStoresAndAtomics << '\n' <<
        "occlusionQueryPrecise::"  << vkpdf.occlusionQueryPrecise << '\n' <<
        "shaderStorageImageExtendedFormats::"  << vkpdf.shaderStorageImageExtendedFormats << '\n' <<
        "sparseResidencyBuffer::"  << vkpdf.sparseResidencyBuffer << '\n' <<
        "sparseResidencyAliased::"  << vkpdf.sparseResidencyAliased <<'\n'  <<
        "shaderStorageImageMultisample::"  << vkpdf.shaderStorageImageMultisample <<'\n'  <<
        "shaderStorageImageReadWithoutFormat::"  << vkpdf.shaderStorageImageReadWithoutFormat <<'\n'  << 
        "shaderStorageImageWriteWithoutFormat::"  << vkpdf.shaderStorageImageWriteWithoutFormat <<'\n'  <<    
        "shaderUniformBufferArrayDynamicIndexing::"  << vkpdf.shaderUniformBufferArrayDynamicIndexing <<'\n'  << 
        "shaderSampledImageArrayDynamicIndexing::"  << vkpdf.shaderSampledImageArrayDynamicIndexing <<'\n'  << 
        "shaderStorageBufferArrayDynamicIndexing::"  << vkpdf.shaderStorageBufferArrayDynamicIndexing <<'\n'  << 
        "shaderStorageImageArrayDynamicIndexing::"  << vkpdf.shaderStorageImageArrayDynamicIndexing <<"\n*******************\n\n"; 

        return os;
   }
 
   std::ostream& operator<<(std::ostream& os, const VkPhysicalDeviceLimits& vkpdl)
{
     os << "\n###VkPhysicalDeviceLimits:###\n" <<
    "maxStorageBufferRange::"  <<vkpdl.maxStorageBufferRange << '\n' << 
    "maxImageArrayLayers::"  <<vkpdl.maxImageArrayLayers << '\n' <<    
    "maxTexelBufferElements::"  <<vkpdl.maxTexelBufferElements << '\n' <<
    "maxUniformBufferRange::"  <<vkpdl.maxUniformBufferRange << '\n' <<
    "maxStorageBufferRange ::"  <<vkpdl.maxStorageBufferRange << '\n' <<
    "maxPushConstantsSize::"  <<vkpdl.maxPushConstantsSize << '\n' <<
    "maxMemoryAllocationCount::"  <<vkpdl.maxMemoryAllocationCount << '\n' <<
    "maxSamplerAllocationCount::"  <<vkpdl.maxSamplerAllocationCount << '\n' <<
    "maxVertexInputAttributes ::"  <<vkpdl.maxVertexInputAttributes << '\n' <<
    "maxVertexInputBindings::"  <<vkpdl.maxVertexInputBindings << '\n' <<
    "maxFragmentInputComponents::"  <<vkpdl.maxFragmentInputComponents << '\n' <<
    "maxFragmentOutputAttachments::"  <<vkpdl.maxFragmentOutputAttachments << '\n' <<  
    "maxViewports::" << vkpdl.maxViewports << '\n' << 
    "timestampPeriod::" << vkpdl.timestampPeriod << '\n' <<             
    "maxClipDistances::" << vkpdl.maxClipDistances << '\n' <<                
    "maxCullDistances::" << vkpdl.maxCullDistances << '\n' <<                   
    "maxColorAttachments::" << vkpdl.maxColorAttachments << '\n' <<     
    "maxClipDistances::" << vkpdl.maxClipDistances << '\n' <<     
    "maxFramebufferWidth::" << vkpdl.maxFramebufferWidth << '\n' <<     
    "maxFramebufferHeight::" << vkpdl.maxFramebufferHeight << '\n' <<     
    "maxFramebufferLayers::" << vkpdl.maxFramebufferLayers << "\n*******************\n\n";    
                  
    return os; 
}  


std::ostream& operator<<(std::ostream& os, const VkPhysicalDeviceType& vkpdf)
{   
    std::cout << "\n@#######******VK_PHYSICAL_DEVICE_TYPE*********#########\n";
    switch(vkpdf)
    {
    case VK_PHYSICAL_DEVICE_TYPE_OTHER :          std::cout << "#-> VK_PHYSICAL_DEVICE_TYPE_OTHER\n";
    break; 
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: std::cout << "#->VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU \n";
    break;
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:   std::cout << "#->VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU \n";
    break; 
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:    std::cout << "#-> VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU\n";
    break;   
    case VK_PHYSICAL_DEVICE_TYPE_CPU:            std::cout << "#-> VK_PHYSICAL_DEVICE_TYPE_CPU\n";
    break;
    }

}

 /*  void vulkan_app::shutdown()
   {
        vkDestroyInstance(
        vk_occurance.vk_instance,
        NULL   
       );
        vkDestroySwapchainKHR(vk_occurance.device, vk_occurance.swapChain, nullptr);
        vkDestroyDevice(vk_occurance.device, nullptr);
   }*/
/*

    VK_PHYSICAL_DEVICE_TYPE_OTHER = 0,
    VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU = 1,
    VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU = 2,
    VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU = 3,
    VK_PHYSICAL_DEVICE_TYPE_CPU = 4,
    */