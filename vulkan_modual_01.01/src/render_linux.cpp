
#include "../headers/vulkan_api.hpp"
#include "../headers/discrptoz.hpp"

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
          std::cout << "\n#############################vkWaitForFences att fram::" <<  vk_occurance.currentFrame << "size of inflight::" << vk_occurance.inFlightFences.size() << "\n\n";
             vkWaitForFences(vk_occurance.logical_device, 1, &vk_occurance.inFlightFences[vk_occurance.currentFrame], VK_TRUE, UINT64_MAX);

        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(vk_occurance.logical_device, swapchan_handle.swapchain, UINT64_MAX, vk_occurance.imageAvailableSemaphores[vk_occurance.currentFrame], VK_NULL_HANDLE, &imageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            renew_swap_chain();
            return;
        } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }


        if (vk_occurance.imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
            vkWaitForFences(vk_occurance.logical_device, 1, &vk_occurance.imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
        }
        vk_occurance.imagesInFlight[imageIndex] = vk_occurance.inFlightFences[vk_occurance.currentFrame];




        VkPipelineStageFlags graphicsWaitStageMasks[] = { VK_PIPELINE_STAGE_VERTEX_INPUT_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

      
      VkSemaphore waitSemaphores[] = {vk_occurance.imageAvailableSemaphores[vk_occurance.currentFrame],vk_occurance.compute.compute_semaphore};
      VkSemaphore signalSemaphores[] = {vk_occurance.renderFinishedSemaphores[vk_occurance.currentFrame],vk_occurance.graphics.compute_semaphore}; 


        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

      

        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 2;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &vk_occurance.graphics.command_buffers[imageIndex];

        
        submitInfo.signalSemaphoreCount = 2;
        submitInfo.pSignalSemaphores = signalSemaphores;

        vkResetFences(vk_occurance.logical_device, 1, &vk_occurance.inFlightFences[vk_occurance.currentFrame]);

        if (vkQueueSubmit(vk_occurance.graphics_queue , 1, &submitInfo, vk_occurance.inFlightFences[vk_occurance.currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }



        
        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 2;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = {swapchan_handle.swapchain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        result = vkQueuePresentKHR(vk_occurance.present_queue, &presentInfo);



        VkPipelineStageFlags waitStageMask = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;

		// Submit compute commands
	
        VkSubmitInfo computeSubmitInfo{};
        computeSubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		computeSubmitInfo.commandBufferCount = 1;
		computeSubmitInfo.pCommandBuffers = &vk_occurance.compute.primary_command_buffer;
		computeSubmitInfo.waitSemaphoreCount = 1;
		computeSubmitInfo.pWaitSemaphores = &vk_occurance.graphics.compute_semaphore;
		computeSubmitInfo.pWaitDstStageMask = &waitStageMask;
		computeSubmitInfo.signalSemaphoreCount = 1;
		computeSubmitInfo.pSignalSemaphores = &vk_occurance.compute.compute_semaphore;

         if (vkQueueSubmit(vk_occurance.compute_queue, 1, &computeSubmitInfo,VK_NULL_HANDLE) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit compute command buffer!");
        }
		

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
            
           renew_swap_chain();
        } else if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }




        vk_occurance.currentFrame = (vk_occurance.currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;


//if resize::
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

   vkDeviceWaitIdle(vk_occurance.logical_device);

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