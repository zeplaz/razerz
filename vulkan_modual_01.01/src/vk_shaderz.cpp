
#include "../headers/vk_shaderz.hpp"

#include <stddef.h> 

std::unordered_map<std::string,shader_pipe_raw> parser_vulkan_modual::shader_raw_pipez;
std::unordered_map<std::string, std::pair<Shader_Stagez,std::vector<std::vector<unsigned int>>>> parser_vulkan_modual::compled_pipe_code;

bool parser_vulkan_modual::glslangInitialized = false;

std::string trim(const std::string& str,  std::vector<char> toremove )
{
   for(auto it = toremove.begin(); it < toremove.end();)
   {

    size_t first = str.find_first_not_of(*it);
    if (std::string::npos == first)
    {
        return str; 
    }
    size_t last = str.find_last_not_of(*it);
    return str.substr(first, (last - first + 1));
   }
} 

void parser_vulkan_modual::init_glslang()
{
    if (!glslangInitialized)
{   
   glslangInitialized=   glslang::InitializeProcess();
}

}

Shader_Stagez parser_vulkan_modual::shader_stages_active(std::stringstream& in_sstream)
{
 char ch =' ';
 Shader_Stagez present_stages = Shader_Stagez::SHADER_NULL; 
 std::string stage_n; 
 in_sstream.ignore(1,':');
 //ch = in_sstream.get();
 std:: cout << "#####DEBIUG::ch" << ch << '\n';
 while(ch !='\n')
 {    
     ch = in_sstream.get();
   
    if(ch == ',' || ch == ':')
     {
      std::cout << "###.ch->" << ch << '\n' << "#->stage_n::" << stage_n << '\n';

         if(stage_n == "VERTEX")
         {
             stage_n.erase();
             std::cout << "=> CONTAINS VERTEX SHADER>>\n";
             present_stages |= Shader_Stagez::VERTEX_SHADER;
         }
         if(stage_n == "COMPUTE")
         {  
              std::cout << "=> CONTAINS COMPUTE SHADER>>\n";
             present_stages |= Shader_Stagez::COMPUTE_SHADER;
             stage_n.erase();
         }
         if(stage_n == "FRAG")
         { 
            std::cout << "=> CONTAINS FRAG SHADER>>\n";   
           present_stages |= Shader_Stagez::FRAGMENT_SHADER;
           stage_n.erase();
         }

          if(stage_n == "TESS_CTRL")
         { 
            std::cout << "=> CONTAINS TESS_CONTROL_SHADER>>\n";   
           present_stages |= Shader_Stagez::TESS_CONTROL_SHADER;
           stage_n.erase();
         }

          if(stage_n == "TESS_EVAL")
         { 
            std::cout << "=> CONTAINS TESS_EVAL_SHADER>>\n";   
           present_stages |= Shader_Stagez::TESS_EVAL_SHADER;
           stage_n.erase();
         }


          if(stage_n == "GEOM")
         { 
            std::cout << "=> CONTAINS GEOMETRY_SHADER>>\n";   
           present_stages |= Shader_Stagez::GEOMETRY_SHADER;
           stage_n.erase();
         }
     }
     else
      {
        stage_n+=ch;     
      }  
    //  std::cerr << "\n###ERRROR> PARSE ERROR\n";
  }
   return present_stages;
 }

inline EShLanguage operator|(EShLanguage a, EShLanguage b)
{
    return static_cast<EShLanguage>(static_cast<int>(a) | static_cast<int>(b));
}

inline EShLanguage operator|= ( EShLanguage& a, EShLanguage b )
 { a = static_cast<EShLanguage>(static_cast<EShLanguage>(a) | static_cast<EShLanguage>(b) ); return a; }

EShLanguage parser_vulkan_modual::shader_stage_SPIRV(std::stringstream& in_sstream)
{
  char ch =' ';
 EShLanguage present_stages;
 std::string stage_n; 
 in_sstream.ignore(1,':');
 //ch = in_sstream.get();
 std:: cout << "#####DEBIUG::ch" << ch << '\n';
 while(ch !='\n')
 {    
     ch = in_sstream.get();
   
    if(ch == ',' || ch == ':')
     {
      std::cout << "###.ch->" << ch << '\n' << "#->stage_n::" << stage_n << '\n';

         if(stage_n == "VERTEX")
         {
             stage_n.erase();
             std::cout << "=> CONTAINS VERTEX SHADER>>\n";
             present_stages |=EShLangVertex;
         }
         if(stage_n == "COMPUTE")
         {  
              std::cout << "=> CONTAINS COMPUTE SHADER>>\n";
             present_stages |= EShLangCompute;
             stage_n.erase();
         }
         if(stage_n == "FRAG")
         { 
            std::cout << "=> CONTAINS FRAG SHADER>>\n";   
           present_stages |= EShLangFragment;
           stage_n.erase();
         }

          if(stage_n == "TESS_CTRL")
         { 
            std::cout << "=> CONTAINS TESS_CONTROL_SHADER>>\n";   
           present_stages |=EShLangTessControl;
           stage_n.erase();
         }

          if(stage_n == "TESS_EVAL")
         { 
            std::cout << "=> CONTAINS TESS_EVAL_SHADER>>\n";   
           present_stages |= EShLangTessEvaluation;
           stage_n.erase();
         }


          if(stage_n == "GEOM")
         { 
            std::cout << "=> CONTAINS GEOMETRY_SHADER>>\n";   
           present_stages |= EShLangGeometry;
           stage_n.erase();
         }
     }
     else
      {
        stage_n+=ch;     
      }  
    //  std::cerr << "\n###ERRROR> PARSE ERROR\n";
  }
   return present_stages;
}

VkFormat parser_vulkan_modual::parse_vk_formate(std::stringstream& iss)
{ 
  std::string inval;

  std::getline(iss, inval, '\n');

   if(inval == "VK_FORMAT_R32G32B32A32_SFLOAT")
  {
    std::cout << "->VK_FORMAT_R32G32B32A32_SFLOAT\n;";
    return VK_FORMAT_R32G32B32A32_SFLOAT;
  }

  else if(inval == "VK_FORMAT_R32G32_SFLOAT")
  {
    std::cout << "->VK_FORMAT_R32G32_SFLOAT\n;";
    return VK_FORMAT_R32G32_SFLOAT;
  }

    else if(inval == "VK_FORMAT_R32G32B32_SFLOAT")
  {
    std::cout << "->VK_FORMAT_R32G32B32_SFLOAT\n";
    return VK_FORMAT_R32G32B32_SFLOAT;
  }

  else 
  {
    std::cerr <<"##ERRROR:: parse_vk_formate is just nott added (so many) go to vk_shaderz.cpp and add it!\n or invaled formate so check the file .info to makeure ireal.\n https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkFormat.html\n"; 
  return VK_FORMAT_UNDEFINED;
  }
  
}

uint32_t parser_vulkan_modual::shader_offset(std::stringstream& iss)
{
  std::string token; 
  std::getline(iss,token,'\n');

  int delim = token.find(',');

  std::string struct_name;
  std::string struct_part;
  int i = 0;
  for( i = 0 ; i < delim; i++)
  {
    struct_name += token[i];
  }

  for(i = delim+1; i < token.length(); i++)
  {
    struct_part += token[i];
  }

  #ifdef DEBUG_01
  std::cout <<"#DEBUG++struct_name::" << struct_name << "   Struct_part::" << struct_part << '\n';
  #endif


  if(struct_name == "compute_vertex_A")
  {
    if(struct_part == "vert")
    {
      return offsetof(compute_vertex_A,vert);
    }
  }

  if(struct_name == "base_vertex")
  {

    if(struct_part == "pos")
    {
      return offsetof(base_vertex,pos);
    }

      if(struct_part == "base_colour")
    {
          return offsetof(base_vertex,base_colour);
    }

      if(struct_part == "textel_uv")
    {
      return offsetof(base_vertex,textel_uv);
    }
  }

  if(struct_name == "vertex_vulkan_glyph")
  {
    return offsetof(glyph_vertex, vertex_pos_texcord);
  }

}

void parser_vulkan_modual::pipe_define_data(std::stringstream& iss)
{
      
       std::string token; 
      // std::vector<std::string> shader_pipe_stringdata;
       std::string shd_name;   
       std::cout << "-->shader_pipefound reading data//\n";
       shader_pipe_raw s_pipe; 
       int linecount= 0;
      // while(std::getline(iss,token,'\n'))
      do
      {       
       //  std::cout << "TOKEN::" << token << '\n';
       if(token =="/shader_pipe/>")
         {           
            std::cout << "\n####END OF SHADERPIPE\n\n";
            break;
         }
        
         switch(linecount)
         {
            case RAW_SHADER_NAME_POS :
            {
                 shd_name = token; 
                 std::cout << "#->>SHD_NAME::" << token << '\n';
                break;
            } 
            case RAW_SHADER_PATH_FLAGZ_POS :
            {
             std::string path = DEFUALT_ROOT_SHDER_PATH;
             path += token;
             s_pipe.folder_path = path; 
             std::cout << "#->>s_pipe.folder_path::" << path << '\n';
             s_pipe.stage_flags = shader_stages_active(iss);
             std::cout << "#-->s_pipe.stage_flags \n";
            break;
            }
         //   case RAW_S
            
         }
         linecount++;        


        if(token == "<|shader_DATA_layout>")
        { 
          token.erase();
          bool typefound = false;
          EShLanguage curr_type;
          while(iss.peek()!= '<')
         {
           
          char ch = iss.get();

          if(ch == '_' && !typefound)
          {
            typefound = true;
            if(token == "vertex")
            {
              curr_type=EShLangVertex; 
            }

         else if(token == "geom")
            {
              curr_type=EShLangGeometry;    
            }


           else if(token == "compute")
            {
              curr_type =EShLangCompute;
            }

           else if(token == "tessctrl")
            {
              curr_type=EShLangTessControl;
            }

            else if(token == "tesseval")
            {
              curr_type=EShLangTessEvaluation;
            }
           else if(token == "frag")
            {
              curr_type=EShLangFragment;
            }

            else {
              std::cerr<< "#####ERRRRRORRRRRRR unrecogied shader via filename..correct the type it is a prefix!**********************\n\n";
            }
 
          }
          if(ch == '\n' && iss.peek() !='\n')
          {
          typefound= false;
          std::vector<char> car_remove{'\n',' '};
          token = trim(token,car_remove);
          s_pipe.stage_filenames.push_back(token);
          s_pipe.stage_pair.push_back(std::make_pair(curr_type,token));
          std::cout <<"#-> ADD FILE NAME::" << token << "   srage:::" << curr_type << '\n';
          token.erase();
          continue;
          }
          token +=ch;
       
          //std::iss,token,'\n');

         } 
        
         }

        if(token == "<|VertexInputAttributeDescription>")
        {

         while(iss.peek()!= '|')
         {
         if(iss.peek()== '\n')
         {
             iss.ignore(254,'\n');
         }
         std::cout << "\n###ewdescrpor::\n";

         VkVertexInputAttributeDescription new_discrptor;
         new_discrptor.location = static_cast<uint32_t> (iss.get());
         iss.ignore(255,'\n');
         new_discrptor.binding = static_cast<uint32_t> (iss.get());
         iss.ignore(255,'\n');
         new_discrptor.format= parse_vk_formate(iss);
         new_discrptor.offset = shader_offset(iss);
         s_pipe.vinput_attr_des.push_back(new_discrptor);
         } 
        

          //(std::stoi((std::getline(iss,token,'\n')));
        }

        }while(std::getline(iss,token,'\n'));
    s_pipe.pipe_name = shd_name;

    shader_raw_pipez.insert(std::make_pair(shd_name,s_pipe));

    gen_complie_from_pipe(s_pipe);

}

void parser_vulkan_modual::shader_info_reader(const char* in_path)
{
    
FILE* info_stream;

if (fopen_s(&info_stream, in_path,"rb") != NULL) {
throw std::runtime_error("failed to open file!");
}

fseek(info_stream, 0, SEEK_END);
size_t length = ftell(info_stream);
fseek(info_stream, 0, SEEK_SET);
char* info_code = (char*)malloc(length);
fread(info_code, sizeof(char), length, info_stream);
fclose(info_stream);

std::string info_stirng(info_code);
std::stringstream iss(info_stirng);

std::string token;

while(std::getline(iss, token, '\n'))
 {
   if(token == "<|shader_pipe>")
   {    
     pipe_define_data(iss);
   }
   // std::cout << token << '\n';
}

#ifdef DEBUG_01
//std::for_each(raw_linevector.begin(), raw_linevector.end(), [] (std::string& s){ std::cout << s << "\n"; });
#endif // DEBUG

}


void parser_vulkan_modual::gen_complie_from_pipe(shader_pipe_raw& in_raw_pipe)
{   
    std::vector<std::vector<unsigned int>> compled_stages;
    Shader_Stagez contained_flags; 
   for (int i =0; i< in_raw_pipe.stage_pair.size(); i++ )
    {
        switch(in_raw_pipe.stage_pair[i].first)
        {
            case EShLangVertex :
            {   std::string path = in_raw_pipe.folder_path;
                path += in_raw_pipe.stage_pair[i].second;
                contained_flags |= Shader_Stagez::VERTEX_SHADER;
                compled_stages.push_back(gen_SPIRV(EShLangVertex,path));
                break;
            }
            case  EShLangTessControl:
            {   std::string path = in_raw_pipe.folder_path;
                path += in_raw_pipe.stage_pair[i].second;
                contained_flags |= Shader_Stagez::TESS_CONTROL_SHADER;
                compled_stages.push_back(gen_SPIRV(EShLangTessControl,path));
              
                break;
            }

              case EShLangTessEvaluation :
            {   std::string path = in_raw_pipe.folder_path;
                path += in_raw_pipe.stage_pair[i].second;
                contained_flags |= Shader_Stagez::TESS_EVAL_SHADER;
                compled_stages.push_back(gen_SPIRV(EShLangTessEvaluation,path));

                break;
            }          

            case EShLangGeometry:
            {   std::string path = in_raw_pipe.folder_path;
                path += in_raw_pipe.stage_pair[i].second;
                contained_flags |= Shader_Stagez::GEOMETRY_SHADER;
                compled_stages.push_back(gen_SPIRV(EShLangGeometry,path));

                break;
            }
            case EShLangCompute :
            {   std::string path = in_raw_pipe.folder_path;
                path += in_raw_pipe.stage_pair[i].second;
                contained_flags |= Shader_Stagez::COMPUTE_SHADER;
                compled_stages.push_back(gen_SPIRV(EShLangCompute,path));                
                std::cout << "DEBGU###########EShLangCompute:::" << '\n';
                break;
            }

            case EShLangFragment : 
            {
                std::string path = in_raw_pipe.folder_path;
                path += in_raw_pipe.stage_pair[i].second;
                contained_flags |= Shader_Stagez::FRAGMENT_SHADER;
                compled_stages.push_back(gen_SPIRV(EShLangFragment,path));                

                break;
            }
        }
    }
  compled_pipe_code.insert(std::make_pair(in_raw_pipe.pipe_name,std::make_pair(contained_flags,compled_stages)));
}


const std::vector<unsigned int> parser_vulkan_modual::gen_SPIRV(EShLanguage in_shd_type, std::string path)
{

  std::cout << "####SHADER_FILE SPIRV begin FOR:: SHADERTYPE::" << in_shd_type << "  path::" << path <<'\n' <<'\n';
       /*
    glslang::TProgram program;

    const char *shaderStrings[1];
	TBuiltInResource Resources = {};
	InitResources(Resources);*/

    std::ifstream file(path);

    if (!file.is_open()) 
    {
        std::cout << "Failed to load shader: " << path << std::endl;
        throw std::runtime_error("failed to open file: " + path);
    }
    std::string InputGLSL((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());


    const char* InputCString = InputGLSL.c_str();
    
    glslang::TShader Shader(in_shd_type);
    #ifdef VULKAN 
    std::cout << "VULKAN:" VULKAN
    #endif
    Shader.setStrings(&InputCString, 1);

    int ClientInputSemanticsVersion = 120;
    glslang::EShTargetClientVersion VulkanClientVersion = glslang::EShTargetVulkan_1_2;
    glslang::EShTargetLanguageVersion TargetVersion = glslang::EShTargetSpv_1_5;

    Shader.setEnvInput(glslang::EShSourceGlsl, in_shd_type, glslang::EShClientVulkan, ClientInputSemanticsVersion);
    Shader.setEnvClient(glslang::EShClientVulkan, VulkanClientVersion);
    Shader.setEnvTarget(glslang::EShTargetSpv, TargetVersion);

    TBuiltInResource Resources;
    InitResources(Resources);
    EShMessages messages = (EShMessages) (EShMsgSpvRules | EShMsgVulkanRules);

   
    //glslang::TShader::Includer//;

    //Shader.Includer.pushExternalLocalDirectory(path);

    std::string PreprocessedGLSL;
    razar_vulkan_includer Includer;

  
    if (!Shader.preprocess(&Resources, GLSL_DEFULT_VER, ENoProfile, false, false, messages, &PreprocessedGLSL, Includer)) 
{
    std::cout << "GLSL Preprocessing Failed for: " << path << std::endl;
    std::cout << Shader.getInfoLog() << std::endl;
    std::cout << Shader.getInfoDebugLog() << std::endl;
  exit(5);
}

std::cout << "##->GLSL Preprocessing..compleate\n";

const char* PreprocessedCStr = PreprocessedGLSL.c_str();
Shader.setStrings(&PreprocessedCStr, 1);

if (!Shader.parse(&Resources, GLSL_DEFULT_VER, false, messages))
{
    std::cout << "GLSL Parsing Failed for: " << path << std::endl;
    std::cout << Shader.getInfoLog() << std::endl;
    std::cout << Shader.getInfoDebugLog() << std::endl;
  exit(5);
}

std:: cout << "##->GLSL Parsing..compleate\n";
glslang::TProgram Program;
Program.addShader(&Shader);

if(!Program.link(messages))
{
    std::cout << "GLSL Linking Failed for: " << path << std::endl;
    std::cout << Shader.getInfoLog() << std::endl;
    std::cout << Shader.getInfoDebugLog() << std::endl;
    exit(5);
}
std:: cout << "##->GLSL Linking..compleate\n";
std::vector<unsigned int> SpirV;
spv::SpvBuildLogger logger;
glslang::SpvOptions spvOptions;
glslang::GlslangToSpv(*Program.getIntermediate(in_shd_type), SpirV, &logger, &spvOptions);

std::cout << "####SHADER_FILE SPIRV GENRATED FOR:: SHADERTYPE::" << in_shd_type << "  path::" << path <<'\n' <<'\n';

return SpirV;
}