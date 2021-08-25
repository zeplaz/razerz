

#include "vulkan_definz.hpp"

#include <list>


/* in draw
    float time = TimerState.GetDeltaTime();
    ProvideDataToShadersThroughPushConstants( ComputeCommandBuffer, *ComputePipelineLayout, VK_SHADER_STAGE_COMPUTE_BIT, 0, sizeof( float ), &time );
*/


/* pipeline create
 VkPushConstantRange push_constant_range = {
      VK_SHADER_STAGE_COMPUTE_BIT,    // VkShaderStageFlags     stageFlags
      0,                              // uint32_t               offset
      sizeof( float )                 // uint32_t               size
    };

    InitVkDestroyer( LogicalDevice, ComputePipelineLayout );
    if( !CreatePipelineLayout( *LogicalDevice, { *DescriptorSetLayout[1] }, { push_constant_range }, *ComputePipelineLayout ) ) {
      return false;
    }
*/


//constexpr unsigned int DISC_


 /*  //this needs to be moved to a modfiable situation...
       ///compute VERTEX
        VkDescriptorSetLayoutBinding vertex_compute_uboLayoutBinding{};
        vertex_compute_uboLayoutBinding.binding = 0;
        vertex_compute_uboLayoutBinding.descriptorCount = 1;
        vertex_compute_uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        vertex_compute_uboLayoutBinding.pImmutableSamplers = nullptr;
        vertex_compute_uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        //compute COMPUTE
        VkDescriptorSetLayoutBinding compute_compute_image_buf_LayoutBinding{};
        compute_compute_image_buf_LayoutBinding.binding = 1;
        compute_compute_image_buf_LayoutBinding.descriptorCount = 2;
        compute_compute_image_buf_LayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
        compute_compute_image_buf_LayoutBinding.pImmutableSamplers = nullptr;
        compute_compute_image_buf_LayoutBinding.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

        //compute FRAGMENT
        VkDescriptorSetLayoutBinding unifrom_bool_block_LayoutBinding{};
        unifrom_bool_block_LayoutBinding.binding = 0;
        unifrom_bool_block_LayoutBinding.descriptorCount = 1;
        unifrom_bool_block_LayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        unifrom_bool_block_LayoutBinding.pImmutableSamplers = nullptr;
        unifrom_bool_block_LayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

        VkDescriptorSetLayoutBinding unifrom_colour_plus_LayoutBinding{};
        unifrom_colour_plus_LayoutBinding.binding = 1;
        unifrom_colour_plus_LayoutBinding.descriptorCount = 1;
        unifrom_colour_plus_LayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        unifrom_colour_plus_LayoutBinding.pImmutableSamplers = nullptr;
        unifrom_colour_plus_LayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

        VkDescriptorSetLayoutBinding frag_compute_colour_map_LayoutBinding{};
        frag_compute_colour_map_LayoutBinding.binding = 2;
        frag_compute_colour_map_LayoutBinding.descriptorCount = 2;
        frag_compute_colour_map_LayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        frag_compute_colour_map_LayoutBinding.pImmutableSamplers = nullptr;
        frag_compute_colour_map_LayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;


        std::array<VkDescriptorSetLayoutBinding, 5> bindings = {vertex_compute_uboLayoutBinding, compute_compute_image_buf_LayoutBinding,
                                                                unifrom_bool_block_LayoutBinding,unifrom_colour_plus_LayoutBinding,frag_compute_colour_map_LayoutBinding};
       

    
        }*/

/*
struct descriptor_handle
{
    VkDescriptorPool descp_pool;
    VkDescriptorSetLayout descp_set_layout;
    VkDescriptorSet descrp_set;
    VkWriteDescriptorSet descp_write_set;
    //void setup_pools(std::vector<std::pair<int,VkDescriptorType>>& des_type, VkDevice& in_device, int max_set= 1);
    //void create_layout(VkShaderStageFlagBits what_shd_stage, int binding_index);
    
};


void discriptor_setup(uint32_t pooldesc_count,VkDescriptorType type)
{
VkDescriptorPoolSize poolSize{};
poolSize.type = type;
poolSize.descriptorCount = pooldesc_count;




descriptor_handle elem_compute_partical;

elem_compute_partical.descp_pool; 

}

/*
    SAMPLER - Can be used to sample images.
    COMBINED_IMAGE_SAMPLER - Combines a sampler and associated image. (VkNeo)
    SAMPLED_IMAGE - Used in conjunction with a SAMPLER.
    STORAGE_IMAGE - Read/write image memory.
    UNIFORM_TEXEL_BUFFER - Read only array of homogeneous data.
    STORAGE_TEXEL_BUFFER - Read/write array of homogeneous data.
    UNIFORM_BUFFER - Read only structured buffer.  (VkNeo)
    STORAGE_BUFFER - Read/write structured buffer.
    UNIFORM_BUFFER_DYNAMIC - Same as UNIFORM_BUFFER, but better for storing multiple objects and simply offsetting into them.
    STORAGE_BUFFER_DYNAMIC - Same as STORAGE_BUFFER, but better for storing multiple objects and simply offsetting into them.
    INPUT_ATTACHMENT - Used for unfiltered image views.  
*/
/*
int CreateDescriptorSetLayout( 
		const shader_t & vertexShader, 
		const shader_t & fragmentShader, 
		renderProg_t & renderProg ) {
	
	// Descriptor Set Layout
	{
		std::list< VkDescriptorSetLayoutBinding > layoutBindings;
		VkDescriptorSetLayoutBinding binding = {};
		binding.descriptorCount = 1;
		
		uint32_t bindingId = 0;

		binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		for ( int i = 0; i < vertexShader.bindings.Num(); ++i ) {
			binding.binding = bindingId++;
			binding.descriptorType = GetDescriptorType( vertexShader.bindings[ i ] );
			renderProg.bindings.push_back( vertexShader.bindings[ i ] );

			layoutBindings.push_back( binding );
		}

		binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
		for ( int i = 0; i < fragmentShader.bindings.Num(); ++i ) {
			binding.binding = bindingId++;
			binding.descriptorType = GetDescriptorType( fragmentShader.bindings[ i ] );
			renderProg.bindings.push_back( fragmentShader.bindings[ i ] );

			layoutBindings.push_back( binding );
		}

        binding.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
         for ( int i = 0; i < compute_shaderz.bindings.Num(); ++i ) {   
            binding.binding = bindingId++;
			binding.descriptorType = GetDescriptorType( fragmentShader.bindings[ i ] );
			renderProg.bindings.push_back( fragmentShader.bindings[ i ] );

			layoutBindings.push_back( binding );
         }


		VkDescriptorSetLayoutCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		createInfo.bindingCount = layoutBindings.Num();
		createInfo.pBindings = layoutBindings.Ptr();

		vkCreateDescriptorSetLayout( vkcontext.device, &createInfo, NULL, &renderProg.descriptorSetLayout );
	}

	// Pipeline Layout
	{
		VkPipelineLayoutCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		createInfo.setLayoutCount = 1;
		createInfo.pSetLayouts = &renderProg.descriptorSetLayout;

		vkCreatePipelineLayout( vkcontext.device, &createInfo, NULL, &renderProg.pipelineLayout );
	}
}



static void CreateDescriptorPools( VkDescriptorPool (&pools)[ NUM_FRAME_DATA ] ) {
	const int numPools = 2;
	VkDescriptorPoolSize poolSizes[ numPools ];
	poolSizes[ 0 ].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[ 0 ].descriptorCount = MAX_DESC_UNIFORM_BUFFERS;   // 8192
	poolSizes[ 1 ].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSizes[ 1 ].descriptorCount = MAX_DESC_IMAGE_SAMPLERS;    // 12384

	VkDescriptorPoolCreateInfo poolCreateInfo = {};
	poolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolCreateInfo.pNext = NULL;
	poolCreateInfo.maxSets = MAX_DESC_SETS; // 16384
	poolCreateInfo.poolSizeCount = numPools;
	poolCreateInfo.pPoolSizes = poolSizes;

	for ( int i = 0; i < NUM_FRAME_DATA; ++i ) {
		ID_VK_CHECK( vkCreateDescriptorPool( vkcontext.device, &poolCreateInfo, NULL, &pools[ i ] ) );
	}*/
/*
    void descriptor_handle::setup_pools(std::vector<std::pair<int,VkDescriptorType>>& des_type, VkDevice& in_device, int max_set= 1)
    {   
        unsigned int dscp_size = des_type.size(); 
        std::vector<VkDescriptorPoolSize> pool_size(dscp_size);

        for( int i = 0; i < dscp_size;i++)
        {
            pool_size.at(i).type = des_type.at(i).second;
            pool_size.at(i).descriptorCount = des_type.at(i).first;
        }

        VkDescriptorPoolCreateInfo create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        create_info.poolSizeCount = pool_size.size(); 
        create_info.pPoolSizes = pool_size.data();
        create_info.maxSets = max_set;

        VkResult create_descriptor_pool = vkCreateDescriptorPool(
            in_device, &create_info, nullptr,&descp_pool
       );
    
    }

    void descriptor_handle::create_layout(VkShaderStageFlagBits what_shd_stage, int binding_index)
    {

  VkDescriptorSetLayoutBinding layout_binding ={};

    }
  
*/