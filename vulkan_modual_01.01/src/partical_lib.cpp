

#include "../headers/partical_lib.hpp"
#include "../headers/vk_abstracionz.hpp"



  
void compute_partic_attracto_sim::allocations(VkPhysicalDevice& physical_Device,VkDevice& logical_device, VkCommandPool& cmd_pool)
{

	std::cout << "#->allocations\n";
	    VkBuffer stagingBuffer;

        	vk_utiltiyz::create_buffer(physical_Device,logical_device,memorySize,VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
           VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			stagingBuffer,compute_memory);

            	void *mapped;
	 if (	vkMapMemory(logical_device, compute_memory, 0, memorySize, 0, &mapped)  != VK_SUCCESS) {
            throw std::runtime_error("failed to compute_partic_attracto_sim::vkMapMemory !");
        }
		memcpy(mapped, positions.data(),  sizeof(positions));
	
		    VkMappedMemoryRange mappedRange{};
			mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
			mappedRange.memory = compute_memory;
			mappedRange.offset = 0;
			mappedRange.size = sizeof(positions);
			vkFlushMappedMemoryRanges(logical_device, 1, &mappedRange);

		memcpy(mapped,velocities.data(),  sizeof(velocities));
		    mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		    mappedRange.memory = compute_memory;
			mappedRange.offset =  sizeof(positions);
			mappedRange.size = sizeof(velocities);
			vkFlushMappedMemoryRanges(logical_device, 1, &mappedRange);			
		
	///    
	vkUnmapMemory(logical_device, compute_memory);

		vk_utiltiyz::create_buffer(physical_Device,logical_device,memorySize,VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,comp_buffer,compute_memory);




            

/*
//map memory

*/ 
//	exit(1);
    }

