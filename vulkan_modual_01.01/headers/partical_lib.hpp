#ifndef PARTICAL_LIB_01_VULKAN_HPP
#define PARTICAL_LIB_01_VULKAN_HPP


#include "vulkan_definz.hpp"
#include <chrono>



namespace partical_compA
{

const glm::vec4 ORGIN_DEFULT = glm::vec4(0.1,0.1,0.5,0.0);

constexpr int  VERTEX_BINDER = 0;

constexpr int  MAX_ATTRACTORS = 24;
constexpr int MAX_PARTICAL_COLOUR_CHANNELZ = 4;

constexpr int  PARTICLE_GROUP_SIZE     = 512;
constexpr int  PARTICLE_GROUP_COUNT   = 4096;
constexpr int  PARTICLE_COUNT          = (PARTICLE_GROUP_SIZE * PARTICLE_GROUP_COUNT);

constexpr int WORKGROUP_SIZE = 512;

const int  PARTCL_UNI_BIDN_INDX = 1;
const int  PARTCL_U_VELOC_INDEX =2;
const int  PARTCL_POS_VOLOCITY_INDX = 3;
const int  PARTCL_U_POS_INDEX =4;
const int  PARTCL_U_ORGIN_INDEX =5;


static inline  long tick_current_return()
  {
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);

    auto ap_now_epo = now_ms.time_since_epoch();
    long now_duration = ap_now_epo.count();

    std::chrono::milliseconds dur(now_duration);
    std::chrono::time_point<std::chrono::system_clock> dt_tic(dur);
    std::cout << "\n->#LONG TICCK RETURN::"<< now_duration <<'\n';
    return now_duration;
  }

  static inline float random_float()
  {
    float res;
    unsigned int tmp;
    static unsigned int seed = 0xFFFF0C59;

    seed *= 16807;

    tmp = seed ^ (seed >> 4) ^ (seed << 15);

    *((unsigned int *) &res) = (tmp >> 9) | 0x3F800000;

    //std::cout << "\nres::"<<res << " rez-1.0f" << res - 1.0f <<'\n';
    return (res - 1.0f);
   }

  static glm::vec3 random_vector(float minmag = 0.0f, float maxmag = 1.0f)
  {
      glm::vec3 randomvec(random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f);
      randomvec = glm::normalize(randomvec);
      randomvec *= (random_float() * (maxmag - minmag) + minmag);

    //  std::cout <<"\nradvec::" << 'x'<< randomvec.x <<'\n'
    //  <<'y' <<randomvec.y << '\n'
    //  <<'z' << randomvec.y << '\n';
      return randomvec;
  }
/*
struct Particle {
		glm::vec2 pos;								// Particle position
		glm::vec2 vel;								// Particle velocity

	};

struct computeUBO {							// Compute shader uniform block object
			float deltaT;							//		Frame delta time
			float destX;							//		x position of the attractor
			float destY;							//		y position of the attractor
			int32_t particleCount = PARTICLE_COUNT;
		} comp_ubo;*/


}

using namespace partical_compA;
struct compute_partic_attracto_sim
{

	compute_partic_attracto_sim()
	{


	 memorySize = sizeof(glm::vec4)*positions.size()+sizeof(glm::vec4)*velocities.size();
	 std::cout << "###bufferSize::" << memorySize <<'\n';
	// exit(1);
//	 vertexSize = bufferSize;
	}


  struct uniform_buffer_objz
  {
     alignas(16)glm::mat4 mvp[3];
     alignas(16)glm::vec4 orgin;
     alignas(16)glm::vec4 partc_attractor[MAX_ATTRACTORS];

     alignas(16)bool has_channelz;
     alignas(16)bool has_colour_map;

     alignas(16)glm::vec4 colour_channelz[MAX_PARTICAL_COLOUR_CHANNELZ];

  } uboz;


  glm::vec3 pos;


  static long frame_count;
  uint32_t last_ticks=0;
  uint32_t start_ticks=0;
  uint32_t current_time=0;

  float time;
  float delta_time;


  std::array<float, MAX_ATTRACTORS>attractor_masses;
  std::array<glm::vec4,PARTICLE_COUNT> positions;
  std::array<glm::vec4,PARTICLE_COUNT> velocities;



  VkBuffer vertexBuffer;
  VkDeviceMemory vertexBufferMemory;
  VkDeviceSize vertexSize;

   uint32_t bufferSize;
   VkBuffer comp_buffer;
   VkDeviceSize memorySize;
   VkDeviceMemory compute_memory;

void allocations(VkPhysicalDevice& physical_Device,VkDevice& logical_device, VkCommandPool& cmd_pool);

	inline void set_orgin(glm::vec4 in_orgin)
	{
		uboz.orgin = in_orgin;
	}

  inline void gen_pos()
  {
    for (int i = 0; i < PARTICLE_COUNT; i++)
    {
       positions.at(i) = uboz.orgin+glm::vec4(random_vector(-10.0f, 10.0f), random_float());
    }

  }

  inline void gen_velocities()
  {
	  for (int i = 0; i < PARTICLE_COUNT; i++)
    {
	  velocities.at(i) = glm::vec4(random_vector(-0.1f, 0.1f), 0.0f);
	}
  }


};


const VkPushConstantRange compute_push_ranges[] =
{
    {
        VK_SHADER_STAGE_COMPUTE_BIT,    // stageFlags
        0,                                      // offset
        4                                       // size
    },
};



const VkDescriptorSetLayoutBinding active_disc_set_bindingsv2[] =
{
	//graphicz set 0 startt at [0]
	{
		0,
		VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		3,
		VK_SHADER_STAGE_VERTEX_BIT,
		NULL
	},

//frag set 0.//startt at [1]
//

	{
	1,
	VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
	1,
	VK_SHADER_STAGE_FRAGMENT_BIT,
	NULL
	},

	{
	 2,
	 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
	 MAX_PARTICAL_COLOUR_CHANNELZ,
	 VK_SHADER_STAGE_FRAGMENT_BIT,
	 NULL
	},

	{
	 3,
	 VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
	 1,
	 VK_SHADER_STAGE_FRAGMENT_BIT,
	 NULL
	},

	{
	 4,
	 VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
	 1,
	 VK_SHADER_STAGE_FRAGMENT_BIT,
     NULL
	},

	//compute set 0 //startt at [5]
	{
	 0,
	 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
	 1,
	 VK_SHADER_STAGE_COMPUTE_BIT,
	 NULL
	},
	{
	 1,
	 VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
	 MAX_ATTRACTORS,
	 VK_SHADER_STAGE_COMPUTE_BIT,
	 NULL
	},
	//compute set 1 //startt at [7]
	{
	2,
	VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,
	1,
	VK_SHADER_STAGE_COMPUTE_BIT,
	NULL
	},
	{
	3,
		VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,
	1,
	VK_SHADER_STAGE_COMPUTE_BIT,
	NULL
	},
//VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,//VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,				//
};


const VkDescriptorSetLayoutCreateInfo desc_set_layouts_INFOv2[]=
{
{
     VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
	 NULL,
	 0,
	 5,
	&active_disc_set_bindingsv2[0]
},

{
     VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
	 NULL,
	 0,
	 2,
	 &active_disc_set_bindingsv2[5]
},

{
     VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
	 NULL,
	 0,
	 2,
	 &active_disc_set_bindingsv2[7]
}

};




#endif
