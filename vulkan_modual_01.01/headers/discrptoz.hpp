

#include "vulkan_definz.hpp"

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