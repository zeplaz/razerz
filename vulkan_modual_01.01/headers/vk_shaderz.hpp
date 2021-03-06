#ifndef VULKAN_MODUAL_SHADERZ_01_HPP
#define VULKAN_MODUAL_SHADERZ_01_HPP


//clibz
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


//STLz
#include <tuple>
#include <functional>
#include <sstream>
#include <algorithm>
#include <unordered_map>

//glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>


//glslang
//#include "3rd_party/glslang_linux_Release/include/glslang/Public/ShaderLang.h"
//#include "3rd_party/glslang_linux_Release/include/glslang/SPIRV/GlslangToSpv.h"
//#include "3rd_party/glslang_linux_Release/include/glslang/SPIRV/spirv.hpp"

#include <glslang/Public/ShaderLang.h>
//#include "3rd_party/glslang-master/glslang/Public/ShaderLang.h"
#include <glslang/SPIRV/GlslangToSpv.h>
#include <glslang/SPIRV/SpvTools.h>
#include <glslang/SPIRV/spirv.hpp>
#include <glslang/build_info.h>
//#include <glslang/OSDependent/osinclude.h>

#include <glslang/SPIRV/GLSL.std.450.h>
#include <glslang/SPIRV/doc.h>
#include <glslang/SPIRV/disassemble.h>

//#include <spirv/unified1/spirv.hpp11>

//#include <DirStackFileIncluder.h>
/*
#pragma comment(lib,"3rd_party/glslang_linux_Release/lib/libglslang.a")
#pragma comment(lib,"3rd_party/glslang_linux_Release/lib/libMachineIndependent.a")
#pragma comment(lib,"3rd_party/glslang_linux_Release/lib/libGenericCodeGen.a")
#pragma comment(lib,"3rd_party/glslang_linux_Release/lib/libOSDependent.a")
*/

// inernal
#include "vulkan_definz.hpp"

const int  PARTCL_UNI_BIDN_INDX = 3;
const int  PARTCL_U_VELOC_INDEX =4;
const int  PARTCL_U_POS_INDEX =5;
const int  PARTCL_U_ORGIN_INDEX =6;


#ifdef __unix 
constexpr const char* DEFUALT_ROOT_SHDER_PATH = "../shaderzglsl";
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),  (mode)))==NULL
#else
constexpr const char* DEFUALT_ROOT_SHDER_PATH = "..\shaderzglsl";
#endif


//usingz and enumz
using vx_attr_desc_tuple =  std::tuple<uint32_t, uint32_t,VkFormat,uint32_t> ;
//VK_FORMAT_R32G32_SFLOAT

enum VX_ATTR_DESC_LOC{
  
 VX_BINDING_LOC = 0,
 VX_LOCATION_LOC = 1,
 VX_FORMAT_LOC = 2,
 VX_OFFSET_LOC = 3

};

enum RAW_SHADER_LOC 
{
    RAW_SHADER_NAME_POS  = 1,
    RAW_SHADER_PATH_FLAGZ_POS  = 2
   
};

constexpr int GLSL_DEFULT_VER = 120;


/*
*
*extending the hasher function so templates can be aded without polluting standerd library namesapce.. also, feel free to extend.

@::EXTENTIONS::::
static var:: last_hash;
pt_func::oytput_debug()->string 



last_hash 
.. TODO::: finialze the debuger functions 
*
*
*/


template<typename type>
class hasher: public std::hash<type>{

    
    static size_t last_hash;

    std::string output_debug()
    {
        //  std::string temp = "LAST_hahs::" + std::to_string(last_hash);
        return std::string("LAST_hash::" + std::to_string(last_hash));

    }
};



struct glyph_vertex{
   glm::vec4  vertex_pos_texcord;

   bool operator ==(const glyph_vertex& other) const noexcept
   {
    return vertex_pos_texcord == other.vertex_pos_texcord;
   }
};

template<> struct hasher<glyph_vertex>
    {
    std::size_t operator()(glyph_vertex const& bv) const noexcept
    {
     return hasher<glm::vec4>()(bv.vertex_pos_texcord);
    }
    };


struct base_vertex{
    glm::vec3 pos;
    glm::vec4 base_colour;
    glm::vec2 textel_uv;

 bool operator ==(const base_vertex& other) const
  {
    return pos == other.pos && base_colour == other.base_colour && textel_uv == other.textel_uv; 
  }

};

template<> struct hasher<base_vertex>
    {
    std::size_t operator()(base_vertex const& bv) const noexcept
    {
     return ((hasher<glm::vec3>()(bv.pos) ^
            (hasher<glm::vec3>()(bv.base_colour) << 1)) >> 1) ^
            (hasher<glm::vec2>()(bv.textel_uv) << 1);
    }
    };

struct compute_vertex_A{
    glm::vec4 vert;
    bool operator ==(const compute_vertex_A& other) const noexcept
    {
        return vert == other.vert;
    }
};
template<> struct hasher<compute_vertex_A>
    {
    std::size_t operator()(compute_vertex_A const& bv) const noexcept
    {
     return hasher<glm::vec4>()(bv.vert);
    }
    };

/*

namespace std {
    template<> struct hash<base_vertex> {
        size_t operator()(base_vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^
                   (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
                   (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}*/


struct shader_pipe_raw
{

std::string folder_path;    
Shader_Stagez stage_flags;
EShLanguage esl_stage_flags;
std::string pipe_name;
std::vector<std::string> stage_filenames;

std::vector<std::pair<EShLanguage,std::string>> stage_pair;


std::vector<VkVertexInputAttributeDescription> vinput_attr_des;
std::vector<VkDescriptorSetLayoutBinding> desc_layout_bindingz;

/*
std::string code_path(int index)
{   

    
    std::stringstream iss(stage_filenames)
    std::string path = folder_path;
    path +=stage_filenames.at(index);
    return path;
}*/

};


std::string trim(const std::string& str, std::vector<char> toremove);

class razar_vulkan_includer : public glslang::TShader::Includer
{   
    public : 
  razar_vulkan_includer() : externalLocalDirectoryCount(0) {}
  
 virtual IncludeResult* includeLocal(const char* headerName,
                                        const char* includerName,
                                        size_t inclusionDepth) override
    {  
        return readLocalPath(headerName, includerName, (int)inclusionDepth);
    }
        virtual void pushExternalLocalDirectory(const std::string& dir)
    {
        directoryStack.push_back(dir);
        externalLocalDirectoryCount = (int)directoryStack.size();
    }

    virtual void releaseInclude(IncludeResult* result) override
    {
        if (result != nullptr) {
            delete [] static_cast<tUserDataElement*>(result->userData);
            delete result;
        }
    }

    virtual ~razar_vulkan_includer() override { }


    protected :
        int externalLocalDirectoryCount;
        std::vector<std::string> directoryStack;
        typedef char tUserDataElement;
      virtual IncludeResult* readLocalPath(const char* headerName, const char* includerName, int depth)
    {
        // Discard popped include directories, and
        // initialize when at parse-time first level.
        directoryStack.resize(depth + externalLocalDirectoryCount);
        if (depth == 1)
            directoryStack.back() = getDirectory(includerName);

        // Find a directory that works, using a reverse search of the include stack.
        for (auto it = directoryStack.rbegin(); it != directoryStack.rend(); ++it) {
            std::string path = *it + '/' + headerName;
            std::replace(path.begin(), path.end(), '\\', '/');
            std::ifstream file(path, std::ios_base::binary | std::ios_base::ate);
            if (file) {
                directoryStack.push_back(getDirectory(path));
                return newIncludeResult(path, file, (int)file.tellg());
            }
        }

        return nullptr;
    }

        virtual std::string getDirectory(const std::string path) const
    {
        size_t last = path.find_last_of("/\\");
        return last == std::string::npos ? "." : path.substr(0, last);
    }
        virtual IncludeResult* newIncludeResult(const std::string& path, std::ifstream& file, int length) const
    {
        char* content = new tUserDataElement [length];
        file.seekg(0, file.beg);
        file.read(content, length);
        return new IncludeResult(path, content, length, content);
    }
                                     
};

class parser_vulkan_modual{

protected : 
TBuiltInResource Defult_Resources;
static std::unordered_map<std::string,shader_pipe_raw> shader_raw_pipez;
static std::unordered_map<std::string, std::pair<Shader_Stagez,std::vector<std::vector<unsigned int>>>> compled_pipe_code;
static bool glslangInitialized;

void init_glslang();

public : 
~parser_vulkan_modual()
{
  glslang::FinalizeProcess();
  glslangInitialized = false;
}
parser_vulkan_modual()
{
  init_glslang();
}

VkFormat parse_vk_formate(std::stringstream& iss);
Shader_Stagez shader_stages_active(std::stringstream& in_sstream);
EShLanguage shader_stage_SPIRV(std::stringstream& in_sstream);

uint32_t shader_offset(std::stringstream& iss);

void shader_info_reader(const char* in_path);
void pipe_define_data(std::stringstream& iss);

void gen_complie_from_pipe(shader_pipe_raw& in_raw_pipe);
const std::vector<unsigned int> gen_SPIRV(EShLanguage in_shd_type, std::string path);

};


template<class data_struct>
struct vertex_vulkan{


  data_struct data;
  

    static VkVertexInputBindingDescription get_binding_descrption(uint32_t index_binding)
    {
        VkVertexInputBindingDescription binding_description{};
        binding_description.binding = index_binding;
        binding_description.stride = sizeof(data_struct);
        binding_description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return binding_description;
    }

static VkVertexInputAttributeDescription get_attraibute_descriptions(vx_attr_desc_tuple& in_attr_desc)
{
    VkVertexInputAttributeDescription attr_desc{};
    attr_desc.binding = std::get<VX_BINDING_LOC>(in_attr_desc);
    attr_desc.location = std::get<VX_LOCATION_LOC>(in_attr_desc);
    attr_desc.format = std::get<VX_FORMAT_LOC>(in_attr_desc); 
    attr_desc.offset = std::get<VX_OFFSET_LOC>(in_attr_desc);

}

bool operator ==(const vertex_vulkan& other) const {
    return data == other.data; 
}

size_t operator()(vertex_vulkan const& vv) const noexcept
{   
    //size_t val = 
    return    std::hash<data_struct>{}(data);
}
/*
    static std::vector<VkVertexInputAttributeDescription> get_attraibute_descriptions(vx_attr_desc_tuple& in_attr_desc)
    {

        //std::vector<vx_attr_desc_tuple> attuvyte_descs(); 
       // std::vector<vx_attr_desc_tuple>




    }*/
};


class fix_funnction_handle{

VkPipelineVertexInputStateCreateInfo gen_vertex_input_info()
{
VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
vertexInputInfo.vertexBindingDescriptionCount = 0;
vertexInputInfo.pVertexBindingDescriptions = nullptr; // Optional
vertexInputInfo.vertexAttributeDescriptionCount = 0;
vertexInputInfo.pVertexAttributeDescriptions = nullptr; // Optional

return vertexInputInfo;


}
VkPipelineInputAssemblyStateCreateInfo gen_assembly_state_info()
{

VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
inputAssembly.primitiveRestartEnable = VK_FALSE;

return inputAssembly;

}


};

class vulkan_shader_uility
{
   /*/ bool read_shader()
    {

           FILE* shaderStream;

            if(fopen_s(&shaderStream,file_path.string().c_str(),"rb")!=NULL)
            {

}
    }*/

};
static void InitResources(TBuiltInResource &Defult_Resources) {
    Defult_Resources.maxLights = 120;
		Defult_Resources.maxClipPlanes = 6;
		Defult_Resources.maxTextureUnits = 32;
		Defult_Resources.maxTextureCoords = 32;
		Defult_Resources.maxVertexAttribs = 64;
		Defult_Resources.maxVertexUniformComponents = 4096;
		Defult_Resources.maxVaryingFloats = 64;
		Defult_Resources.maxVertexTextureImageUnits = 32;
		Defult_Resources.maxCombinedTextureImageUnits = 80;
		Defult_Resources.maxTextureImageUnits = 32;
		Defult_Resources.maxFragmentUniformComponents = 4096;
		Defult_Resources.maxDrawBuffers = 32;
		Defult_Resources.maxVertexUniformVectors = 128;
		Defult_Resources.maxVaryingVectors = 8;
		Defult_Resources.maxFragmentUniformVectors = 16;
		Defult_Resources.maxVertexOutputVectors = 16;
		Defult_Resources.maxFragmentInputVectors = 15;
		Defult_Resources.minProgramTexelOffset = -8;
		Defult_Resources.maxProgramTexelOffset = 7;
		Defult_Resources.maxClipDistances = 8;
		Defult_Resources.maxComputeWorkGroupCountX = 65535;
		Defult_Resources.maxComputeWorkGroupCountY = 65535;
		Defult_Resources.maxComputeWorkGroupCountZ = 65535;
		Defult_Resources.maxComputeWorkGroupSizeX = 1024;
		Defult_Resources.maxComputeWorkGroupSizeY = 1024;
		Defult_Resources.maxComputeWorkGroupSizeZ = 64;
		Defult_Resources.maxComputeUniformComponents = 1024;
		Defult_Resources.maxComputeTextureImageUnits = 16;
		Defult_Resources.maxComputeImageUniforms = 8;
		Defult_Resources.maxComputeAtomicCounters = 8;
		Defult_Resources.maxComputeAtomicCounterBuffers = 1;
		Defult_Resources.maxVaryingComponents = 60;
		Defult_Resources.maxVertexOutputComponents = 64;
		Defult_Resources.maxGeometryInputComponents = 64;
		Defult_Resources.maxGeometryOutputComponents = 128;
		Defult_Resources.maxFragmentInputComponents = 128;
		Defult_Resources.maxImageUnits = 8;
		Defult_Resources.maxCombinedImageUnitsAndFragmentOutputs = 8;
		Defult_Resources.maxCombinedShaderOutputResources = 8;
		Defult_Resources.maxImageSamples = 0;
		Defult_Resources.maxVertexImageUniforms = 0;
		Defult_Resources.maxTessControlImageUniforms = 0;
		Defult_Resources.maxTessEvaluationImageUniforms = 0;
		Defult_Resources.maxGeometryImageUniforms = 0;
		Defult_Resources.maxFragmentImageUniforms = 8;
		Defult_Resources.maxCombinedImageUniforms = 8;
		Defult_Resources.maxGeometryTextureImageUnits = 16;
		Defult_Resources.maxGeometryOutputVertices = 256;
		Defult_Resources.maxGeometryTotalOutputComponents = 1024;
		Defult_Resources.maxGeometryUniformComponents = 1024;
		Defult_Resources.maxGeometryVaryingComponents = 64;
		Defult_Resources.maxTessControlInputComponents = 128;
		Defult_Resources.maxTessControlOutputComponents = 128;
		Defult_Resources.maxTessControlTextureImageUnits = 16;
		Defult_Resources.maxTessControlUniformComponents = 1024;
		Defult_Resources.maxTessControlTotalOutputComponents = 4096;
		Defult_Resources.maxTessEvaluationInputComponents = 128;
		Defult_Resources.maxTessEvaluationOutputComponents = 128;
		Defult_Resources.maxTessEvaluationTextureImageUnits = 16;
		Defult_Resources.maxVertexAtomicCounters = 0;
		Defult_Resources.maxTessControlAtomicCounters = 0;
		Defult_Resources.maxTessEvaluationAtomicCounters = 0;
		Defult_Resources.maxGeometryAtomicCounters = 0;
		Defult_Resources.maxFragmentAtomicCounters = 8;
		Defult_Resources.maxCombinedAtomicCounters = 8;
		Defult_Resources.maxAtomicCounterBindings = 1;
		Defult_Resources.maxVertexAtomicCounterBuffers = 0;
		Defult_Resources.maxTessControlAtomicCounterBuffers = 0;
		Defult_Resources.maxTessEvaluationAtomicCounterBuffers = 0;
		Defult_Resources.maxGeometryAtomicCounterBuffers = 0;
		Defult_Resources.maxFragmentAtomicCounterBuffers = 1;
		Defult_Resources.maxCombinedAtomicCounterBuffers = 1;
		Defult_Resources.maxAtomicCounterBufferSize = 16384;
		Defult_Resources.maxTransformFeedbackBuffers = 4;
		Defult_Resources.maxTransformFeedbackInterleavedComponents = 64;
		Defult_Resources.maxCullDistances = 8;
		Defult_Resources.maxCombinedClipAndCullDistances = 8;
		Defult_Resources.maxSamples = 4;
		Defult_Resources.maxMeshOutputVerticesNV = 256;
		Defult_Resources.maxMeshOutputPrimitivesNV = 512;
		Defult_Resources.maxMeshWorkGroupSizeX_NV = 32;
		Defult_Resources.maxMeshWorkGroupSizeY_NV = 1;
		Defult_Resources.maxMeshWorkGroupSizeZ_NV = 1;
		Defult_Resources.maxTaskWorkGroupSizeX_NV = 32;
		Defult_Resources.maxTaskWorkGroupSizeY_NV = 1;
		Defult_Resources.maxTaskWorkGroupSizeZ_NV = 1;
		Defult_Resources.maxMeshViewCountNV = 4;
		Defult_Resources.limits.nonInductiveForLoops = 12;
		Defult_Resources.limits.whileLoops = 12;
		Defult_Resources.limits.doWhileLoops = 12;
		Defult_Resources.limits.generalUniformIndexing = 12;
		Defult_Resources.limits.generalAttributeMatrixVectorIndexing = 12;
		Defult_Resources.limits.generalVaryingIndexing = 12;
		Defult_Resources.limits.generalSamplerIndexing = 12;
		Defult_Resources.limits.generalVariableIndexing = 12;
		Defult_Resources.limits.generalConstantMatrixVectorIndexing = 12;
        Defult_Resources.maxPatchVertices = 32;
		Defult_Resources.maxTessGenLevel = 64;
		Defult_Resources.maxViewports = 16;
		Defult_Resources.maxVertexAtomicCounters = 0;
		Defult_Resources.maxTessControlAtomicCounters = 0;
		Defult_Resources.maxTessEvaluationAtomicCounters = 0;
		Defult_Resources.maxGeometryAtomicCounters = 0;
		Defult_Resources.maxFragmentAtomicCounters = 8;
		Defult_Resources.maxCombinedAtomicCounters = 8;
		Defult_Resources.maxAtomicCounterBindings = 1;
		Defult_Resources.maxVertexAtomicCounterBuffers = 0;
		Defult_Resources.maxTessControlAtomicCounterBuffers = 0;
		Defult_Resources.maxTessEvaluationAtomicCounterBuffers = 0;
		Defult_Resources.maxGeometryAtomicCounterBuffers = 0;
		Defult_Resources.maxFragmentAtomicCounterBuffers = 1;
		Defult_Resources.maxCombinedAtomicCounterBuffers = 1;
		Defult_Resources.maxAtomicCounterBufferSize = 16384;
		Defult_Resources.maxTransformFeedbackBuffers = 4;
		Defult_Resources.maxTransformFeedbackInterleavedComponents = 64;
		Defult_Resources.maxCullDistances = 8;
		Defult_Resources.maxCombinedClipAndCullDistances = 8;
		Defult_Resources.maxSamples = 4;
		Defult_Resources.maxMeshOutputVerticesNV = 256;
		Defult_Resources.maxMeshOutputPrimitivesNV = 512;
		Defult_Resources.maxMeshWorkGroupSizeX_NV = 32;
		Defult_Resources.maxMeshWorkGroupSizeY_NV = 1;
		Defult_Resources.maxMeshWorkGroupSizeZ_NV = 1;
		Defult_Resources.maxTaskWorkGroupSizeX_NV = 32;
		Defult_Resources.maxTaskWorkGroupSizeY_NV = 1;
		Defult_Resources.maxTaskWorkGroupSizeZ_NV = 1;
		Defult_Resources.maxMeshViewCountNV = 4;
		Defult_Resources.limits.nonInductiveForLoops = 12;
		Defult_Resources.limits.whileLoops = 12;
		Defult_Resources.limits.doWhileLoops = 12;
		Defult_Resources.limits.generalUniformIndexing = 12;
		Defult_Resources.limits.generalAttributeMatrixVectorIndexing = 12;
		Defult_Resources.limits.generalVaryingIndexing = 12;
		Defult_Resources.limits.generalSamplerIndexing = 12;
		Defult_Resources.limits.generalVariableIndexing = 12;
		Defult_Resources.limits.generalConstantMatrixVectorIndexing = 12;
  }
#endif