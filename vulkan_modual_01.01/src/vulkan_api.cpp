
#include "../headers/vulkan_api.hpp"
#include "../headers/discrptoz.hpp"


#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

#include <queue>

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
        ((void)__android_log_print(ANDROID_LOG_INFO, "Vulkan app", err_msg)); \
        exit(1);                                                               \
    } while (0)
#ifdef VARARGS_WORKS_ON_ANDROID
void DbgMsg(const char *fmt, ...) {
    va_list va;
    va_start(va, fmt);
    __android_log_print(ANDROID_LOG_INFO, "Vulkanapp", fmt, va);
    va_end(va);
}
#else  // VARARGS_WORKS_ON_ANDROID
#define DbgMsg(fmt, ...)                                                                  \
    do {                                                                                  \
        ((void)__android_log_print(ANDROID_LOG_INFO, "Vulkanapp", fmt, ##__VA_ARGS__)); \
    } while (0)
#endif  // VARARGS_WORKS_ON_ANDROID
#else
#define ERR_EXIT(err_msg, err_class) \
    do {                             \
        printf("%s\n", err_msg);     \
        fflush(stdout);              \
        exit(-1);                     \
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
    vm_parser = new parser_vulkan_modual();
}
void vulkan_app::loop()
{
    vk_api->renderLoop();
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

///end of genreall
        vk_api->createDescriptorSetLayout();
        vk_api->create_semaphore_fencez();

        parser_run();
        vk_api->set_parser(vm_parser);
        vk_api->createGraphicsPipeline();
        vk_api->createComputePipeline();
        vk_api->createCommandPool();
        vk_api->createDepthResources();
        vk_api->createFramebuffers();
        vk_api->createVertexBuffer();

        vk_api->createUniformBuffers();
        vk_api->setup_partical_A();
        vk_api->createDescriptorPool();
        vk_api->createDescriptorSets();

        vk_api->build_compute_comand_buffers();

        vk_api->createCommandBuffers();
    };

static std::vector<char> readFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);
        std::cout << "reading file_" << filename <<'\n';
        if (!file.is_open()) {
            throw std::runtime_error("failed to open file!");
        }
        size_t fileSize = (size_t) file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

      //  fseek(file, 0, SEEK_END);
        file.seekg(std::ios_base::end);
	    size_t size = file.tellg();

        std::cout << "\n##DEBUG:::FILESIZE:END<<" <<size <<"\n\n";
        file.close();

        return buffer;

        }



void vulkan_api::on_window_resize(xcb_window_t window, int w, int h)
    {

        std::cout << "###DEBUG:::on window resize this is only the linux function move to some kind of template.. for os type.z.  and why cant i use a void *?\n";
        VkSurfaceCapabilitiesKHR surface_capabilities;
        VkResult vkr  = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vk_occurance.physical_Device,vk_occurance.surface,&surface_capabilities);

        if(w>surface_capabilities.maxImageExtent.width) w = surface_capabilities.maxImageExtent.width;
        if(w>surface_capabilities.maxImageExtent.height) w = surface_capabilities.maxImageExtent.height;

        if(w ==0 || h == 0) return;

        active_height = h;
        active_width = w;
        renew_swap_chain();
    }


void vulkan_api::setup_partical_A()
{
    const glm::vec4 ORGIN_DEFULT = glm::vec4(0.1,0.1,0.5,0.0);
    partical_A_sym.set_orgin(ORGIN_DEFULT);

    partical_A_sym.gen_pos();
    partical_A_sym.gen_velocities();
    partical_A_sym.allocations(vk_occurance.physical_Device,vk_occurance.logical_device,vk_occurance.graphics.commandPool);

}

void vulkan_api::build_compute_comand_buffers()
{

   VkCommandBufferAllocateInfo allocInfo_compute{};
        allocInfo_compute.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo_compute.commandPool =  vk_occurance.compute.commandPool;
        allocInfo_compute.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo_compute.commandBufferCount = (uint32_t)1;

        if (vkAllocateCommandBuffers(vk_occurance.logical_device, &allocInfo_compute,&vk_occurance.compute.primary_command_buffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers!");
        }


            VkCommandBufferBeginInfo cmdBufferBeginInfo{};
        	cmdBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        vkBeginCommandBuffer(vk_occurance.compute.primary_command_buffer, &cmdBufferBeginInfo);

                    VkBufferMemoryBarrier buffer_barrier =
				{
					VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER,
					nullptr,
					0,
					VK_ACCESS_SHADER_WRITE_BIT,
					vk_occurance.graphics.queueFamilyIndex,
                    vk_occurance.compute.queueFamilyIndex,
					partical_A_sym.comp_buffer,
					0,
					partical_A_sym.memorySize
				};


                vkCmdPipelineBarrier(
					vk_occurance.compute.primary_command_buffer,
					VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
                	VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
					0,
					0, nullptr,
					1, &buffer_barrier,
					0, nullptr);

        std::cout << "vk_occurance.graphics.queueFamilyIndex::" << vk_occurance.graphics.queueFamilyIndex <<
         "  vk_occurance.compute.queueFamilyIndex::"<<    vk_occurance.compute.queueFamilyIndex <<'\n';

        vkCmdBindPipeline(vk_occurance.compute.primary_command_buffer, VK_PIPELINE_BIND_POINT_COMPUTE, vk_occurance.compute.pipeline);
		vkCmdBindDescriptorSets(vk_occurance.compute.primary_command_buffer, VK_PIPELINE_BIND_POINT_COMPUTE, vk_occurance.compute.pipelineLayout, 0,
         1, &vk_occurance.compute.descriptorSets[0], 0, 0);


			vkCmdPushConstants(
					vk_occurance.compute.primary_command_buffer,
					vk_occurance.compute.pipelineLayout,
					VK_SHADER_STAGE_COMPUTE_BIT,
					0,
					sizeof(float),
					&partical_A_sym.delta_time);
    std::cout << "######->	vkCmdDispatch(vk_occurance.compute.primary_command_buffer,\n";
		vkCmdDispatch(vk_occurance.compute.primary_command_buffer, PARTICLE_COUNT / WORKGROUP_SIZE, 1, 1);


        VkBufferMemoryBarrier buffer_barrier2 =
			{
				VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER,
				nullptr,
				VK_ACCESS_SHADER_WRITE_BIT,
				0,
				vk_occurance.compute.queueFamilyIndex,
				vk_occurance.graphics.queueFamilyIndex,
				partical_A_sym.comp_buffer,
				0,
				partical_A_sym.memorySize
			};

			vkCmdPipelineBarrier(
				vk_occurance.compute.primary_command_buffer,
				VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
				0,
				0, nullptr,
				1, &buffer_barrier2,
				0, nullptr);


		vkEndCommandBuffer(vk_occurance.compute.primary_command_buffer);
}
    /*/transferCmd = vk_utiltiyz::createCommandBuffer(vk_occurance.logical_device,VK_COMMAND_BUFFER_LEVEL_PRIMARY, vk_occurance.compute.commandPool, true);

            //acquare barreier
            VkBufferMemoryBarrier acq_buffer_barrier =
				{
					VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER,
					nullptr,
					0,
					VK_ACCESS_SHADER_WRITE_BIT,
					vk_occurance.graphics.queueFamilyIndex,
                    vk_occurance.compute.queueFamilyIndex,
					partical_A_sym.comp_buffer,
					0,
					partical_A_sym.memorySize
				};


                vkCmdPipelineBarrier(
					vk_occurance.graphics.command_buffers[i],
					VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
                	VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
					0,
					0, nullptr,
					1, &acq_buffer_barrier,
					0, nullptr);
///realse berrer
                VkBufferMemoryBarrier release_buffer_barrier =
			{
				VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER,
				nullptr,
				VK_ACCESS_SHADER_WRITE_BIT,
				0,
				vk_occurance.compute.queueFamilyIndex,
				vk_occurance.graphics.queueFamilyIndex,
				partical_A_sym.comp_buffer,
				0,
				partical_A_sym.memorySize
			};
			vkCmdPipelineBarrier(
				transferCmd,
				VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
				0,
				0, nullptr,
				1, &release_buffer_barrier,
				0, nullptr);


     if (vkEndCommandBuffer(transferCmd) != VK_SUCCESS)
     {
         throw("ERROR:::vkEndCommandBuffer failed");
     }

		VkSubmitInfo submitInfo {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;


		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &transferCmd;
		// Create fence to ensure that the command buffer has finished executing
		VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = 0;
		VkFence fence;

         if (vkCreateFence(vk_occurance.logical_device, &fenceInfo, nullptr, &fence) != VK_SUCCESS)
         {
            throw("ERROR:::vkCreateFence failed");
         }

         if (vkQueueSubmit(vk_occurance.compute_queue, 1, &submitInfo, fence) != VK_SUCCESS)
         {
            throw("ERROR:::vkQueueSubmit failed");
         }

          if (vkWaitForFences(vk_occurance.logical_device, 1, &fence, VK_TRUE, UINT64_MAX) != VK_SUCCESS)
         {
            throw("ERROR:::vkWaitForFences failed");
         }


		vkDestroyFence(vk_occurance.logical_device, fence, nullptr);

	    vkFreeCommandBuffers(vk_occurance.logical_device, vk_occurance.compute.commandPool, 1, &transferCmd);
	        {

            VkCommandBufferBeginInfo beginInfo_compute =
            {
                VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                0,
                VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
                0
            };

              if (vkBeginCommandBuffer(vk_occurance.compute.primary_command_buffer, &beginInfo_compute) != VK_SUCCESS) {
                throw std::runtime_error("failed to begin recording command buffer!");
            }

        VkBufferMemoryBarrier buffer_barrier =
			{
				VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER,
				nullptr,
				0,
				VK_ACCESS_SHADER_WRITE_BIT,
                    vk_occurance.graphics.queueFamilyIndex,
                    vk_occurance.compute.queueFamilyIndex,
					partical_A_sym.vertexBuffer,
					0,
					partical_A_sym.vertexSize
			};


			vkCmdPipelineBarrier(
				vk_occurance.compute.primary_command_buffer,
				VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
				VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				0,
				0, nullptr,
				1, &buffer_barrier,
				0, nullptr);

        vkCmdBindPipeline(vk_occurance.compute.primary_command_buffer, VK_PIPELINE_BIND_POINT_COMPUTE, vk_occurance.compute.pipeline);
		vkCmdBindDescriptorSets(vk_occurance.compute.primary_command_buffer, VK_PIPELINE_BIND_POINT_COMPUTE, vk_occurance.compute.pipelineLayout, 0,
                             1, &vk_occurance.descriptorSets[1], 0, 0);


		vkCmdDispatch(vk_occurance.compute.primary_command_buffer, PARTICLE_COUNT / WORKGROUP_SIZE, 1, 1);

		// Add barrier to ensure that compute shader has finished writing to the buffer
		// Without this the (rendering) vertex shader may display incomplete results (partial data from last frame)
	//	if (vk_occurance.graphics.queueFamilyIndex != compute.queueFamilyIndex)
		{
			VkBufferMemoryBarrier buffer_barrier =
			{
				VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER,
				nullptr,
				VK_ACCESS_SHADER_WRITE_BIT,
				0,
				vk_occurance.compute.queueFamilyIndex,
				vk_occurance.graphics.queueFamilyIndex,
				partical_A_sym.comp_buffer,
				0,
				partical_A_sym.memorySize
			};

			vkCmdPipelineBarrier(
				vk_occurance.compute.primary_command_buffer,
				VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
				0,
				0, nullptr,
				1, &buffer_barrier,
				0, nullptr);
		}

		vkEndCommandBuffer(vk_occurance.compute.primary_command_buffer);

        }*/

void vulkan_api::createCommandBuffers()
{
   // vk_occurance.compute.command_buffers.resize(swapchan_handle.sc_images.size());

    vk_occurance.graphics.command_buffers.resize(swapchan_handle.sc_images.size());
    //vk_occurance.compute.primary_command_buffer

        VkCommandBufferAllocateInfo allocInfo_graphics{};
        allocInfo_graphics.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo_graphics.commandPool =  vk_occurance.graphics.commandPool;
        allocInfo_graphics.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo_graphics.commandBufferCount = (uint32_t) vk_occurance.graphics.command_buffers.size();


         if (vkAllocateCommandBuffers(vk_occurance.logical_device, &allocInfo_graphics,  vk_occurance.graphics.command_buffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers!");
        }


            VkCommandBufferBeginInfo beginInfo_graphics{};
            beginInfo_graphics.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = vk_occurance.render_Pass;
            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent =swapchan_handle.sc_extent;

            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = {0.4f, 0.1f, 0.2f, 1.0f};
            clearValues[1].depthStencil = {1.0f, 0};

            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();


        for (size_t i = 0; i < vk_occurance.graphics.command_buffers.size(); i++)
        {

             renderPassInfo.framebuffer = swapchan_handle.sc_framebuffers[i];

            if (vkBeginCommandBuffer(vk_occurance.graphics.command_buffers[i], &beginInfo_graphics) != VK_SUCCESS)
             {
                throw std::runtime_error("failed to begin recording command buffer!");
            }

            vkCmdBeginRenderPass(vk_occurance.graphics.command_buffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);


            vkCmdBindPipeline(vk_occurance.graphics.command_buffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, vk_occurance.graphics.pipeline);

            VkBuffer vertexBuffers[] = {partical_A_sym.comp_buffer};
            VkDeviceSize offsets[] = {0};
            vkCmdBindVertexBuffers(vk_occurance.graphics.command_buffers[i],VERTEX_BUFFER_BIND_ID, 1, &partical_A_sym.comp_buffer, offsets);

            vkCmdBindDescriptorSets(vk_occurance.graphics.command_buffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS,vk_occurance.graphics.pipelineLayout, 0, 1, &vk_occurance.graphics.descriptorSets[i], 0, nullptr);

            vkCmdDraw(vk_occurance.graphics.command_buffers[i], PARTICLE_COUNT, 1, 0, 0);

            vkCmdEndRenderPass(vk_occurance.graphics.command_buffers[i]);

				VkBufferMemoryBarrier buffer_barrier =
				{
					VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER,
					nullptr,
					VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT,
					0,
					vk_occurance.graphics.queueFamilyIndex,
					vk_occurance.compute.queueFamilyIndex,
					partical_A_sym.comp_buffer,
					0,
					partical_A_sym.memorySize
				};

				vkCmdPipelineBarrier(
					vk_occurance.graphics.command_buffers[i],
					VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
					VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
					0,
					0, nullptr,
					1, &buffer_barrier,
					0, nullptr);

            if (vkEndCommandBuffer(vk_occurance.graphics.command_buffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to record command buffer!");
            }


        }

}


void vulkan_api::createDescriptorPool()
{
    std::cout << "->#######createDescriptorPool()#############\n";
        std::array<VkDescriptorPoolSize, 3> poolSizes{};
        poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        poolSizes[0].descriptorCount = static_cast<uint32_t>(swapchan_handle.sc_images.size()*5);

        poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        poolSizes[1].descriptorCount = static_cast<uint32_t>(swapchan_handle.sc_images.size()*5);

        poolSizes[2].type = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
        poolSizes[2].descriptorCount =  static_cast<uint32_t>(swapchan_handle.sc_images.size()*5);

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
        poolInfo.pPoolSizes = poolSizes.data();
        poolInfo.maxSets = static_cast<uint32_t>(swapchan_handle.sc_images.size()*(5+2+3));


     if (vkCreateDescriptorPool(vk_occurance.logical_device, &poolInfo, nullptr, &vk_occurance.descriptorPool) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create descriptor pool!");
        }
}

void  vulkan_api::createDescriptorSets()
{
    std::cout << "-->##########createDescriptorSets()#############\n";
    std::vector<VkDescriptorSetLayout> layouts;

    for(int i = 0; i <swapchan_handle.sc_images.size(); i++)
        {
            layouts.push_back(vk_occurance.descriptor_set_layout[0]);

           }
        std::cout << "###\nsizelayout>>" << layouts.size()<< "   scimge::size::" << swapchan_handle.sc_images.size() << "###############<<<<<\n\n";

        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = vk_occurance.descriptorPool;
        allocInfo.descriptorSetCount = static_cast<uint32_t>(swapchan_handle.sc_images.size());
        allocInfo.pSetLayouts = layouts.data();

        vk_occurance.graphics.descriptorSets.resize(swapchan_handle.sc_images.size());
        if (vkAllocateDescriptorSets(vk_occurance.logical_device, &allocInfo, vk_occurance.graphics.descriptorSets.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate descriptor sets!");
        }


        VkDescriptorSetAllocateInfo allocInfo_comp{};
        allocInfo_comp.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo_comp.descriptorPool = vk_occurance.descriptorPool;
        allocInfo_comp.descriptorSetCount = 2;
        allocInfo_comp.pSetLayouts = &vk_occurance.descriptor_set_layout[1];

        vk_occurance.compute.descriptorSets.resize(2);
        if (vkAllocateDescriptorSets(vk_occurance.logical_device, &allocInfo_comp, vk_occurance.compute.descriptorSets.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate descriptor sets!");
        }

    std::cout << "#################vkAllocateDescriptorSets compleate;\n";

          std::array<VkWriteDescriptorSet, 2> descriptorWrites1{};
        std::cout << "partical_A_sym::memorysize:" << partical_A_sym.memorySize
        << "\nTOTAL RANGE SIZE::"<< sizeof(partical_A_sym.positions)+ sizeof(partical_A_sym.velocities) <<'\n';
//exit(1);
            VkDescriptorBufferInfo bufferInfo_comp_pos{};
            bufferInfo_comp_pos.buffer = partical_A_sym.comp_buffer;
            bufferInfo_comp_pos.offset = 0;
            bufferInfo_comp_pos.range = sizeof(partical_A_sym.positions);

            VkDescriptorBufferInfo bufferInfo_comp_vel{};
            bufferInfo_comp_vel.buffer = partical_A_sym.comp_buffer;
            bufferInfo_comp_vel.offset = sizeof(partical_A_sym.positions);
            bufferInfo_comp_vel.range =  sizeof(partical_A_sym.velocities);

            VkDescriptorBufferInfo bufferinfoz_comp_texel[] = {bufferInfo_comp_pos,bufferInfo_comp_vel};


            descriptorWrites1[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites1[1].dstSet = vk_occurance.compute.descriptorSets[1];
            descriptorWrites1[1].dstBinding = 2;
            descriptorWrites1[1].dstArrayElement = 0;
           // descriptorWrites1[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			descriptorWrites1[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
			descriptorWrites1[1].descriptorCount = 2;
            descriptorWrites1[1].pBufferInfo = &bufferinfoz_comp_texel[0];

            VkDescriptorBufferInfo bufferInfo_comp01{};
            bufferInfo_comp01.buffer = vk_occurance.compute.uniformBuffers[0];
            bufferInfo_comp01.offset = 0;
            bufferInfo_comp01.range = sizeof(compute_partic_attracto_sim::uboz.orgin);

            VkDescriptorBufferInfo bufferInfo_comp02{};
            bufferInfo_comp02.buffer = vk_occurance.compute.uniformBuffers[1];
            bufferInfo_comp02.offset = 0;
            bufferInfo_comp02.range = sizeof(compute_partic_attracto_sim::uboz.partc_attractor);
           VkDescriptorBufferInfo bufferinfoz_comp01[] = {bufferInfo_comp01,bufferInfo_comp02};

            descriptorWrites1[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites1[0].dstSet = vk_occurance.compute.descriptorSets[0];
            descriptorWrites1[0].dstBinding = 0;
            descriptorWrites1[0].dstArrayElement = 0;
            descriptorWrites1[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptorWrites1[0].descriptorCount = 2;
            descriptorWrites1[0].pBufferInfo = &bufferinfoz_comp01[0];



             std::cout << "#################vkUpdateDescriptorSets::descriptorWrites1 begin;\n";
      // vkUpdateDescriptorSets(vk_occurance.logical_device, static_cast<uint32_t>(descriptorWrites1.size()), descriptorWrites1.data(), 0, nullptr);
             vkUpdateDescriptorSets(vk_occurance.logical_device, 1, &descriptorWrites1[0], 0, nullptr);
           //  exit(1);
int j = 0;
    for (size_t i = 0; i < swapchan_handle.sc_images.size(); i++)
     {
            std::cout << "->bufferInfoz::begin\n";
            VkDescriptorBufferInfo bufferInfo_graph_01{};
            bufferInfo_graph_01.buffer = vk_occurance.graphics.uniformBuffers[j];
            bufferInfo_graph_01.offset = 0;
            bufferInfo_graph_01.range = sizeof(compute_partic_attracto_sim::uboz.mvp);
            std::cout << "->bufferInfoz::bufferInfo2::" << sizeof(vk_occurance.graphics.uniformBuffers[j+1]) <<'\n' ;

            VkDescriptorBufferInfo bufferInfo_graph_02{};
            bufferInfo_graph_02.buffer = vk_occurance.graphics.uniformBuffers[j+2];
            bufferInfo_graph_02.offset = 0;
            bufferInfo_graph_02.range = sizeof(compute_partic_attracto_sim::uboz.has_channelz+compute_partic_attracto_sim::uboz.has_colour_map);

             std::cout << "->bufferInfoz::bufferInfo5\n";

            VkDescriptorBufferInfo bufferInfo_graph_03{};
            bufferInfo_graph_03.buffer = vk_occurance.graphics.uniformBuffers[j+3];
            bufferInfo_graph_03.offset = 0;
            bufferInfo_graph_03.range = sizeof(compute_partic_attracto_sim::uboz.colour_channelz);

             std::cout << "->bufferInfoz::bufferInfo4\n";

            std::cout << "->bufferInfoz::bufferInfo3\n";

           VkDescriptorBufferInfo bufferinfoz_graph01[] = {bufferInfo_graph_01,bufferInfo_graph_02,bufferInfo_graph_03};


            std::cout << "->bufferInfoz::end\n";
     j+=3;

            std::cout << "->descriptorWrites::begin\n";

            std::array<VkWriteDescriptorSet, 1> descriptorWrites{};

            //int binding = desc_set_layouts_INFO[3].pBindings[i].binding;
            descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[0].dstSet = vk_occurance.graphics.descriptorSets[0];
            descriptorWrites[0].dstBinding = 0;
            descriptorWrites[0].dstArrayElement = 0;
            descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptorWrites[0].descriptorCount = 3;
            descriptorWrites[0].pBufferInfo = &bufferinfoz_graph01[0];


        //    vkUpdateDescriptorSets(vk_occurance.logical_device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);


        }


}

void vulkan_api::createDescriptorSetLayout()
{

    if (vkCreateDescriptorSetLayout(vk_occurance.logical_device, &desc_set_layouts_INFOv2[0], nullptr, &vk_occurance.descriptor_set_layout[0]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor set layout0!");}
   //exit(1);

    if (vkCreateDescriptorSetLayout(vk_occurance.logical_device, &desc_set_layouts_INFOv2[1], nullptr, &vk_occurance.descriptor_set_layout[1]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor set layout1!");   }

 if (vkCreateDescriptorSetLayout(vk_occurance.logical_device, &desc_set_layouts_INFOv2[2], nullptr, &vk_occurance.descriptor_set_layout[2]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor set layout1!");   }
}


void vulkan_api::createTexelStorage()
{


}
void vulkan_api::createUniformBuffers()
{
VkDeviceSize mvp_bs = sizeof(compute_partic_attracto_sim::uboz.mvp);
VkDeviceSize h_bools_bs = sizeof(compute_partic_attracto_sim::uboz.has_colour_map+compute_partic_attracto_sim::uboz.has_channelz);
VkDeviceSize col_chnl_bs = sizeof(compute_partic_attracto_sim::uboz.colour_channelz);

VkDeviceSize orgin_bs = sizeof(compute_partic_attracto_sim::uboz.orgin);
VkDeviceSize part_attr_bs = sizeof(compute_partic_attracto_sim::uboz.partc_attractor);

       vk_occurance.graphics.uniformBuffers.resize(swapchan_handle.sc_images.size()*3);
       vk_occurance.graphics.uniformBuffersMemory.resize(swapchan_handle.sc_images.size()*3);

        vk_occurance.compute.uniformBuffers.resize(2);
       vk_occurance.compute.uniformBuffersMemory.resize(2);


      vk_utiltiyz::create_buffer(vk_occurance.physical_Device, vk_occurance.logical_device, orgin_bs, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,  vk_occurance.compute.uniformBuffers[0], vk_occurance.compute.uniformBuffersMemory[0]);

      vk_utiltiyz::create_buffer(vk_occurance.physical_Device, vk_occurance.logical_device, part_attr_bs, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,  vk_occurance.compute.uniformBuffers[1], vk_occurance.compute.uniformBuffersMemory[1]);

    int j = 0;
        for (size_t i = 0; i < swapchan_handle.sc_images.size(); i++)
        {
            vk_utiltiyz::create_buffer(vk_occurance.physical_Device, vk_occurance.logical_device, mvp_bs, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,  vk_occurance.graphics.uniformBuffers[j], vk_occurance.graphics.uniformBuffersMemory[j]);

            vk_utiltiyz::create_buffer(vk_occurance.physical_Device, vk_occurance.logical_device, h_bools_bs, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,  vk_occurance.graphics.uniformBuffers[j+2], vk_occurance.graphics.uniformBuffersMemory[j+2]);

            vk_utiltiyz::create_buffer(vk_occurance.physical_Device, vk_occurance.logical_device, col_chnl_bs, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,  vk_occurance.graphics.uniformBuffers[j+3], vk_occurance.graphics.uniformBuffersMemory[j+3]);

        j +=3;
        }

}


void vulkan_api::createVertexBuffer()
    {
      /*VkDeviceSize partical_A_v_bufferSize = sizeof(vertex_vulkan<glm::vec4>)*PARTICLE_COUNT;
      VkBuffer stagingBuffer;
      VkDeviceMemory stagingBufferMemory;

      vk_utiltiyz::create_buffer(vk_occurance.physical_Device, vk_occurance.logical_device,partical_A_v_bufferSize,
                                 VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                 stagingBuffer, stagingBufferMemory);



        void* data;
        vkMapMemory(vk_occurance.logical_device, stagingBufferMemory, 0, partical_A_v_bufferSize, 0, &data);
            memcpy(data, partical_A_sym.positions.data(), (size_t) partical_A_v_bufferSize);
        vkUnmapMemory(vk_occurance.logical_device, stagingBufferMemory);

          vk_utiltiyz::create_buffer(vk_occurance.physical_Device, vk_occurance.logical_device, partical_A_v_bufferSize,
                                     VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                                      partical_A_sym.vertexBuffer, partical_A_sym.vertexBufferMemory);

        vk_utiltiyz::copyBuffer(vk_occurance.logical_device,vk_occurance.graphics.commandPool,vk_occurance.graphics_queue, stagingBuffer, partical_A_sym.vertexBuffer, partical_A_v_bufferSize);

        vkDestroyBuffer(vk_occurance.logical_device, stagingBuffer, nullptr);
        vkFreeMemory(vk_occurance.logical_device, stagingBufferMemory, nullptr);

  */
    }

void vulkan_api::createCommandPool()
{
    queue_family_indices indices = vk_utiltiyz::get_que_fammily_indicas(vk_occurance.physical_Device,vk_occurance.surface);

        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = indices.graphics_Family.value();

        if (vkCreateCommandPool(vk_occurance.logical_device, &poolInfo, nullptr, &vk_occurance.graphics.commandPool) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create graphics command pool!");
        }

        if(indices.graphics_Family.value() != indices.compute_Family.value())
        {
            std::cout << "\n###->CREATEING INDEPENTED COMD POOL FOR COMPUTE QUE########\n";
            VkCommandPoolCreateInfo poolInfo2{};
            poolInfo2.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
            poolInfo2.queueFamilyIndex = indices.compute_Family.value();
            poolInfo2.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        if (vkCreateCommandPool(vk_occurance.logical_device, &poolInfo2, nullptr,&vk_occurance.compute.commandPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create graphics command pool!");
        }
        }

        else
        {
           std::cout << "\n###->COMD POOL FOR COMPUTE QUE is same as graphics ques.########\n";
           vk_occurance.compute.commandPool = vk_occurance.graphics.commandPool;
           exit(1);
        }
        vk_occurance.compute.queueFamilyIndex = indices.compute_Family.value();
        vk_occurance.graphics.queueFamilyIndex= indices.graphics_Family.value();
      //  exit(1);


     }

 void vulkan_api::create_swapchan_imageviews()
    {
        std::cout << "###### vkAPI::create_swapchan_imageviews\n******########********\n";
        swapchan_handle.create_image_view(vk_occurance.logical_device);
    }

    bool vulkan_api::create_swap_Chain()
    {
        std::cout << "######VKAPI::create_swapchain\n******########********\n";

         swapchan_handle.create(active_width,active_height,false,vk_occurance.physical_Device,vk_occurance.surface,vk_occurance.logical_device);

    }

void vulkan_api::setupDebugMessenger() {
        if (!enableValidationLayers) return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        external_vulkan::populateDebugMessengerCreateInfo(createInfo);

        if (external_vulkan::CreateDebugUtilsMessengerEXT(vk_occurance.vk_instance, &createInfo, nullptr, &vk_occurance.debugMessenger) != VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug messenger!");
        }
    }

    void vulkan_api::createDepthResources()
    {
          VkFormat depthFormat =  vk_utiltiyz::findDepthFormat(vk_occurance.physical_Device);

        vk_utiltiyz::createImage(vk_occurance.physical_Device,vk_occurance.logical_device,swapchan_handle.sc_extent.width, swapchan_handle.sc_extent.height, 1, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
         VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vk_occurance.depthImage, vk_occurance.depthImageMemory);
       vk_occurance.depthImageView =vk_utiltiyz::createImageView(vk_occurance.logical_device, vk_occurance.depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, 1);
    }


    void vulkan_api::createFramebuffers()
    {
          swapchan_handle.sc_framebuffers.resize(swapchan_handle.sc_image_views.size());

        for (size_t i = 0; i < swapchan_handle.sc_image_views.size(); i++) {
            std::array<VkImageView, 2> attachments = {
                swapchan_handle.sc_image_views[i],
                vk_occurance.depthImageView
            };

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass =  vk_occurance.render_Pass;
            framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
            framebufferInfo.pAttachments = attachments.data();
            framebufferInfo.width = swapchan_handle.sc_extent.width;
            framebufferInfo.height = swapchan_handle.sc_extent.height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(vk_occurance.logical_device, &framebufferInfo, nullptr, &swapchan_handle.sc_framebuffers.at(i)) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer!");
            }
        }

    }


    void vulkan_api::create_semaphore_fencez()
    {
        //if(MAX_FRAMES_IN_FLIGHT<)
       std::cout <<"imagezus::"<<  vk_utiltiyz::Image_Count_Surface << "\n";
        vk_occurance.imageAvailableSemaphores.resize(vk_utiltiyz::Image_Count_Surface );
        vk_occurance.renderFinishedSemaphores.resize(vk_utiltiyz::Image_Count_Surface );
        vk_occurance.inFlightFences.resize(vk_utiltiyz::Image_Count_Surface);
        vk_occurance.imagesInFlight.resize(swapchan_handle.sc_images.size(),VK_NULL_HANDLE);

        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo{};
        //create_semaphore_fencez
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < vk_utiltiyz::Image_Count_Surface+1; i++) {
            std::cout << "###->vkCreateFence.at::" << i <<'\n';
            if (vkCreateSemaphore(vk_occurance.logical_device, &semaphoreInfo, nullptr, &vk_occurance.imageAvailableSemaphores[i]) != VK_SUCCESS ||
                vkCreateSemaphore(vk_occurance.logical_device, &semaphoreInfo, nullptr, &vk_occurance.renderFinishedSemaphores[i]) != VK_SUCCESS ||
                vkCreateFence(vk_occurance.logical_device, &fenceInfo, nullptr, &vk_occurance.inFlightFences[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create synchronization objects for a frame!");
            }
        }
      //  exit(1);
		if(vkCreateSemaphore(vk_occurance.logical_device, &semaphoreInfo, nullptr, &vk_occurance.graphics.compute_semaphore)!= VK_SUCCESS )
        {
           throw std::runtime_error("failed to create synchronization for graphics commpute semaphore for a frame!");
        }

        if(vkCreateSemaphore(vk_occurance.logical_device, &semaphoreInfo, nullptr, &vk_occurance.compute.compute_semaphore)!= VK_SUCCESS )
        {
           throw std::runtime_error("failed to create synchronization for graphics commpute semaphore for a frame!");
        }

    }


    void vulkan_api::createComputePipeline()
    {
        std::cout << "###########createComputePipeline\n";
        // VkShaderModule comp_A_comp_ShaderModule = vk_utiltiyz::create_shaderModual(in_pars_vk_model->return_raw_SPIRV("compute_partical_A",Shader_Stagez::COMPUTE_SHADER),vk_occurance.logical_device);

        auto comp_A_comp_data =readFile("../shaderzglsl/precomplied/comp_computepartical_A.spv");
        VkShaderModule comp_A_comp_ShaderModule = vk_utiltiyz::create_shaderModual(comp_A_comp_data,vk_occurance.logical_device);

        VkPipelineShaderStageCreateInfo comp_A_comp_ShaderStageInfo{};
        comp_A_comp_ShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        comp_A_comp_ShaderStageInfo.flags= 0;
        comp_A_comp_ShaderStageInfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;
        comp_A_comp_ShaderStageInfo.module = comp_A_comp_ShaderModule;
        comp_A_comp_ShaderStageInfo.pName = "main";
        comp_A_comp_ShaderStageInfo.pSpecializationInfo = NULL;

        VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
        pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutCreateInfo.setLayoutCount = 2;
        pipelineLayoutCreateInfo.pSetLayouts = &vk_occurance.descriptor_set_layout[1];
        pipelineLayoutCreateInfo.pushConstantRangeCount= 1;
        pipelineLayoutCreateInfo.pPushConstantRanges = &compute_push_ranges[0];
        if(vkCreatePipelineLayout(vk_occurance.logical_device, &pipelineLayoutCreateInfo, NULL, &vk_occurance.compute.pipelineLayout)!=VK_SUCCESS)
        {
        throw std::runtime_error("failed to create vkCreatePipelineLayout!");
        };

        VkComputePipelineCreateInfo pipelineCreateInfo = {};
        pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
        pipelineCreateInfo.flags = 0;
        pipelineCreateInfo.stage = comp_A_comp_ShaderStageInfo;
        pipelineCreateInfo.layout = vk_occurance.compute.pipelineLayout;
        pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
        pipelineCreateInfo.basePipelineIndex = 0;

        VkResult res;

         if( (res = vkCreateComputePipelines(vk_occurance.logical_device, NULL, 1, &pipelineCreateInfo, NULL, &vk_occurance.compute.pipeline)) !=VK_SUCCESS)
         {
              throw std::runtime_error("failed to create vkCreateComputePipelines!");
         }
         std::cout << "res for vkCreateComputePipelines::" << res <<'\n';

        vkDestroyShaderModule(vk_occurance.logical_device, comp_A_comp_ShaderModule, nullptr);
    }

     void vulkan_api::createGraphicsPipeline()
     {
         std::cout <<"\n###GRAPHIC_PIPELINE\n";
       /*  VkShaderModule comp_A_vert_ShaderModule = vk_utiltiyz::create_shaderModual(in_pars_vk_model->return_raw_SPIRV("compute_partical_A",Shader_Stagez::VERTEX_SHADER),vk_occurance.logical_device);
         VkShaderModule comp_A_frag_ShaderModule = vk_utiltiyz::create_shaderModual(in_pars_vk_model->return_raw_SPIRV("compute_partical_A",Shader_Stagez::FRAGMENT_SHADER),vk_occurance.logical_device);
        */

        auto comp_A_vert_data =readFile("../shaderzglsl/precomplied/vert_computepartical_A.spv");
        auto comp_A_frag_data =readFile("../shaderzglsl/precomplied/frag_computepartical_A.spv");

        VkShaderModule comp_A_vert_ShaderModule = vk_utiltiyz::create_shaderModual(comp_A_vert_data,vk_occurance.logical_device);
        VkShaderModule comp_A_frag_ShaderModule = vk_utiltiyz::create_shaderModual(comp_A_frag_data,vk_occurance.logical_device);


        VkPipelineShaderStageCreateInfo comp_A_vertShaderStageInfo{};
        comp_A_vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        comp_A_vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        comp_A_vertShaderStageInfo.module = comp_A_vert_ShaderModule;
        comp_A_vertShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo comp_A_fragShaderStageInfo{};
        comp_A_fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        comp_A_fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        comp_A_fragShaderStageInfo.module = comp_A_frag_ShaderModule;
        comp_A_fragShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo shaderStages[] = {comp_A_vertShaderStageInfo,comp_A_fragShaderStageInfo};

        VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;



        auto comp_A_attr_disc = ptr_parser->get_vertex_input_attr_desc("compute_partical_A");

        #ifdef DEBUG_01
        std:: cout << "\n########################------>>>>>>>#DEBUG:::vertexAttributeDescriptionCount" << comp_A_attr_disc.size() << "\n\n";
        #endif // DEBUG


        vertexInputInfo.vertexBindingDescriptionCount = 1;
        vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(comp_A_attr_disc.size());

        auto bindingDescription =vertex_vulkan<glm::vec4>::get_binding_descrption(0);

       std::cout << "##VERTEX_INPUTISTUFF:::\n"
       << "bindingDescription.binding;" << bindingDescription.binding <<  "  inputRate:::" <<  bindingDescription.inputRate
       << "   stride:: " << bindingDescription.stride << '\n' <<
       "comp_A_attr_disc size:::" << comp_A_attr_disc.size() <<'\n';
       if(comp_A_attr_disc.size()>0)
       {
           std::cout
           << "\nlocation::" << comp_A_attr_disc.at(0).location <<
              "\nbinding::"  << comp_A_attr_disc.at(0).binding <<
              "\noffset::"   << comp_A_attr_disc.at(0).offset <<
              "\nformat::"   << comp_A_attr_disc.at(0).format << '\n';
       }
      // exit(1);
        //bindingDescription.location;

        vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
        vertexInputInfo.pVertexAttributeDescriptions = comp_A_attr_disc.data();


        VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float) swapchan_handle.sc_extent.width;
        viewport.height = (float) swapchan_handle.sc_extent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor{};
        scissor.offset = {0, 0};
        scissor.extent = swapchan_handle.sc_extent;

        VkPipelineViewportStateCreateInfo viewportState{};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.pViewports = &viewport;
        viewportState.scissorCount = 1;
        viewportState.pScissors = &scissor;

        VkPipelineRasterizationStateCreateInfo rasterizer{};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.depthClampEnable = VK_FALSE;
        rasterizer.rasterizerDiscardEnable = VK_FALSE;
        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizer.lineWidth = 1.0f;
        rasterizer.cullMode = VK_CULL_MODE_NONE;
        rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        rasterizer.depthBiasEnable = VK_FALSE;

        VkPipelineMultisampleStateCreateInfo multisampling{};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        VkPipelineDepthStencilStateCreateInfo depthStencil{};
        depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        depthStencil.depthTestEnable = VK_TRUE;
        depthStencil.depthWriteEnable = VK_TRUE;
        depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
        depthStencil.depthBoundsTestEnable = VK_FALSE;
        depthStencil.stencilTestEnable = VK_FALSE;

        VkPipelineColorBlendAttachmentState colorBlendAttachment{};
        colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        colorBlendAttachment.blendEnable = VK_FALSE;

        VkPipelineColorBlendStateCreateInfo colorBlending{};
        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlending.logicOpEnable = VK_FALSE;
        colorBlending.logicOp = VK_LOGIC_OP_COPY;
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &colorBlendAttachment;
        colorBlending.blendConstants[0] = 0.0f;
        colorBlending.blendConstants[1] = 0.0f;
        colorBlending.blendConstants[2] = 0.0f;
        colorBlending.blendConstants[3] = 0.0f;

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 1;
        pipelineLayoutInfo.pSetLayouts = &vk_occurance.descriptor_set_layout[0];


        if (vkCreatePipelineLayout(vk_occurance.logical_device, &pipelineLayoutInfo, nullptr, &vk_occurance.graphics.pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline  graphics layout!");
        }

        VkGraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = 2;
        pipelineInfo.pStages = shaderStages;
        pipelineInfo.pVertexInputState = &vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pDepthStencilState = &depthStencil;
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.layout = vk_occurance.graphics.pipelineLayout;
        pipelineInfo.renderPass = vk_occurance.render_Pass;
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

        if (vkCreateGraphicsPipelines(vk_occurance.logical_device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &vk_occurance.graphics.pipeline) != VK_SUCCESS) {
            throw std::runtime_error("failed to create graphics pipeline!");
        }

         vkDestroyShaderModule(vk_occurance.logical_device, comp_A_frag_ShaderModule, nullptr);
         vkDestroyShaderModule(vk_occurance.logical_device, comp_A_vert_ShaderModule, nullptr);
     }



void vulkan_api::create_rednerpass()
{       std::cout << "||->#############VULKAN__APICREATE RENDERCHAIN>#############################\n ";
        VkAttachmentDescription colorAttachment{};
        std::cout << " swapchan_handle.sc_imageFormat;:" <<  swapchan_handle.sc_colorFormat << '\n';
      //  exit(1);
        colorAttachment.format = swapchan_handle.sc_colorFormat;
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
/*
        VkAttachmentDescription present_attachment = {};
            present_attachment.format =  swapchan_handle.sc_imageFormat;
    		present_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
    		present_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;				// Each subpass (or frame as we only have 1 subpass) we want to clear the last present
    		present_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;				// What do we want to do with the data after the subpass, we want to store it away
    		present_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;		// Dont use stencil currently
    		present_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;	// Dont use stencil currently
    		present_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;			// The layout the attachment image subresource, in out case its undefined
    		present_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
*/
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
    device_features.vertexPipelineStoresAndAtomics = VK_TRUE;
    device_features.fragmentStoresAndAtomics = VK_TRUE;
    device_features.tessellationShader = VK_TRUE;
    device_features.dualSrcBlend = VK_TRUE;
    device_features.multiViewport = VK_TRUE;
    device_features.shaderStorageImageMultisample = VK_TRUE;
    device_features.variableMultisampleRate = VK_TRUE;
    device_features.geometryShader = VK_TRUE;
   // device_features.shaderTessellationAndGeometryPointSize = VK_TRUE;
        /*
          device_features. = VK_TRUE;
         ***********************************

        device_features.pipelineStatisticsQuery = VK_TRUE;

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




VkInstanceCreateInfo instance_CreateInfo(VkApplicationInfo & app_info,const
                     std::vector<const char*>& extensions, unsigned int extensions_count,
                     const std::vector<const char*>& layers, unsigned int layerCount)
{
	VkInstanceCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	info.pApplicationInfo = &app_info;                          // Pointer to the application information created
	info.enabledExtensionCount = extensions_count;              // The amount of extensions we wish to enable
	info.ppEnabledExtensionNames = extensions.data();                  // The raw data of the extensions to enable


	return info;
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

          VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        if (enableValidationLayers) {
            std::cout << "\n###########################DEBUG-->>>#CreateDebugUtilsMessengerEXT:###################################################\n";
            create_inst_info.enabledLayerCount = static_cast<uint32_t>(validation_layerz.size());
            create_inst_info.ppEnabledLayerNames = validation_layerz.data();

             external_vulkan::populateDebugMessengerCreateInfo(debugCreateInfo);
            create_inst_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        } else {
            create_inst_info.enabledLayerCount = 0;
            create_inst_info.pNext = nullptr;
        }

        if (vkCreateInstance(&create_inst_info, nullptr, &vk_occurance.vk_instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }



    std::cout << "\n####_cCrEATEed INSTANCE:\n";//::::...vkruslt:::" <<  vk_result << "\n #####\n";
    #ifdef DEBUG_01
   //
   //  external_vulkan::CreateDebugger(vk_occurance.vk_instance);

    #endif // DEBUG

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

        vk_occurance.physical_Device = devices.at(pq2_score.top().index);
        std::cout << "WInNER DEVICE INDEX::" << pq2_score.top().index <<'\n';
        vkGetPhysicalDeviceProperties((devices.at(pq2_score.top().index)),&phy_dev_prop);

        apiVersion = phy_dev_prop.apiVersion;

        vkGetPhysicalDeviceMemoryProperties(vk_occurance.physical_Device, &vk_occurance.device_memory_properties);
        return true;
    }


   std::ostream& operator<<(std::ostream& os, const VkPhysicalDeviceFeatures& vkpdf)
   {
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
        "fragmentStoresAndAtomics::"  << vkpdf.fragmentStoresAndAtomics << '\n' <<
        "shaderTessellationAndGeometryPointSize::"  << vkpdf.shaderTessellationAndGeometryPointSize << '\n' <<
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
