
#include "../headers/vk_shaderz.hpp"

#include <stddef.h>

#include <glslang/SPIRV/Logger.h>
#include <algorithm>
#include <iterator>
#include <sstream>


const std::vector<VkVertexInputAttributeDescription> parser_vulkan_modual::get_vertex_input_attr_desc(std::string name)
{
  std::unordered_map<std::string,shader_pipe_raw>::const_iterator got = shader_raw_pipez.find (name);
    if ( got == shader_raw_pipez.end() )
    std::cerr << "\n ERROR::###THE PIPELINE WAS NOT FOUUND::" << name <<  '\n';
  else
  {
    return  got->second.vinput_attr_des;
  }
}

  
std::unordered_map<std::string,shader_pipe_raw> parser_vulkan_modual::shader_raw_pipez;
//std::unordered_map<std::string, std::pair<Shader_Stagez,std::vector<std::vector<unsigned int>>>> parser_vulkan_modual::compled_pipe_code;
std::unordered_map<std::string, std::pair<Shader_Stagez,std::array<std::vector<unsigned int>,6>>> parser_vulkan_modual::compled_pipe_code;

inline std::string trim(const std::string& str,  std::vector<char> toremove )
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

inline int stage_pos( const Shader_Stagez& in_stage)
 {
     switch(in_stage)
     {
         case Shader_Stagez::VERTEX_SHADER :
         {
             return VERTEX_ARRAY_POS;
             break;
         }
         case Shader_Stagez::TESS_CONTROL_SHADER :
         {
             return TESS_CTL_ARRAY_POS;
             break;
         }
         case Shader_Stagez::TESS_EVAL_SHADER :
         {
             return TESS_EVAL_ARRAY_POS;
             break;
         }
         case Shader_Stagez::GEOMETRY_SHADER :
         {
             return GEO_ARRAY_POS;
             break;
         }
         case Shader_Stagez::COMPUTE_SHADER :
         {
             return COMPUTE_ARRAY_POS;
             break;
         }
         case Shader_Stagez::FRAGMENT_SHADER :
         {
             return FRAG_ARRAY_POS;
             break;
         }
         default :
         {
             std::cerr << "\nERRORRR stage not deifned bad class enum..no postionretunred faital!\n";
             exit(12);
         }
     }
 }

 /******************
 *parser_vulkan_modual
 ********************/
 bool parser_vulkan_modual::glslangInitialized = false;

 void parser_vulkan_modual::init_glslang()
   {
     if (!glslangInitialized)
   {
    glslangInitialized=   glslang::InitializeProcess();
   }
  }

std::vector<unsigned int> parser_vulkan_modual::return_raw_SPIRV(std::string name, Shader_Stagez stage)
{
    std::unordered_map<std::string, std::pair<Shader_Stagez,std::array<std::vector<unsigned int>,6>>>::const_iterator got = compled_pipe_code.find (name);
    if ( got == compled_pipe_code.end() )
    std::cerr << "\n ERROR::###THE PIPELINE WAS NOT FOUUND::" << name <<  '\n';
  else
  {
      if((got->second.first & stage) == stage)
      {   if(got->second.second.at(stage_pos(stage)).size()==0)
          {
            std::cerr<<"\n##there clear a problem with the shader loading prebuilt\n";
           /// auto readFile();
          }
          //else 
          return  got->second.second.at(stage_pos(stage));
      }
      else
      {
          std::cerr<<"\n ############ ERRORRR THIS PIPE DOES NOT CONTAIN THIS FLAG::" << stage << '\n';
      }
  }

}

Shader_Stagez parser_vulkan_modual::shader_stages_active(std::stringstream& in_sstream)
{
 char ch =' ';
 Shader_Stagez present_stages = Shader_Stagez::SHADER_NULL;
 std::string stage_n;
 in_sstream.ignore(1,':');
 //ch = in_sstream.get();
 //std:: cout << "#####DEBIUG::ch" << ch << '\n';
 while(ch !='\n')
 {
     ch = in_sstream.get();

    if(ch == ',' || ch == ':')
     {
      //std::cout << "###.ch->" << ch << '\n' << "#->stage_n::" << stage_n << '\n';

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
iss.ignore(255,'\n');

  std::getline(iss, inval, '\n');
std::cout << inval; 
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
      std::cout << "#######->offsetof(compute_vertex_A,vert)" << offsetof(compute_vertex_A,vert) <<'\n'; 
      return offsetof(compute_vertex_A,vert);
    
    }
  }

  if(struct_name == "base_vertex")
  {
          std::cout << "#######->offsetof(base_vertex)\n" ;//<< offsetof(compute_vertex_A,vert) <<'\n'; 

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

  if(struct_name == "glyph_vertex")
  {
     std::cout << "#######->offsetof(glyph_vertex, vertex_pos_texcord)" << offsetof(glyph_vertex, vertex_pos_texcord) <<'\n'; 
    return offsetof(glyph_vertex, vertex_pos_texcord);
  }
 //exit(1); 

 std::cerr << "####ERROR YOU SHOULD NOT BE HERE OR FORMATE IS NOT VAILED HWAT IS IT???>>>" << struct_name << '\n'; 
  throw std::runtime_error("ERROR parser_vulkan_modual:::shader_offset UNKNOWN FORMATE");

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
         std::string data; iss >> data;
         std::cout << "data:::" <<data  <<'\n';
         new_discrptor.location = static_cast<uint32_t> (std::stoi(data));
         iss >> data;
         new_discrptor.binding= static_cast<uint32_t> (std::stoi(data));
       //  iss.ignore(255,'\n');
         //new_discrptor.binding = static_cast<uint32_t> (stoi(iss.get()));
         std::cout << " new_discrptor.binding:: " <<  new_discrptor.binding << '\n'
         << "new_discrptor.location::" << new_discrptor.location << '\n';
        //exit(1);
        // iss.ignore(255,'\n');
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
}

#ifdef DEBUG_01
std::cout << "\n#################shader_info_reader compleate\n";
//exit(6);
//std::for_each(raw_linevector.begin(), raw_linevector.end(), [] (std::string& s){ std::cout << s << "\n"; });
#endif // DEBUG

}

void parser_vulkan_modual::gen_complie_from_pipe(shader_pipe_raw& in_raw_pipe)
{
    std::array<std::vector<unsigned int>,6> compled_stages;
    std::vector<std::vector<unsigned int>> compled_stg;
    Shader_Stagez contained_flags;
   for (int i =0; i< in_raw_pipe.stage_pair.size(); i++ )
    {
        switch(in_raw_pipe.stage_pair[i].first)
        {
            case EShLangVertex :
            {   std::string path = in_raw_pipe.folder_path;
                path += in_raw_pipe.stage_pair[i].second;
                contained_flags |= Shader_Stagez::VERTEX_SHADER;
                std::vector<unsigned int> tempcode = gen_SPIRV(EShLangVertex,path);
                compled_stages.at(VERTEX_ARRAY_POS).resize(tempcode.size());
                compled_stages.at(VERTEX_ARRAY_POS) = tempcode;
                break;
            }
            case  EShLangTessControl:
            {   std::string path = in_raw_pipe.folder_path;
                path += in_raw_pipe.stage_pair[i].second;
                contained_flags |= Shader_Stagez::TESS_CONTROL_SHADER;
                compled_stages.at(TESS_CTL_ARRAY_POS)= gen_SPIRV(EShLangTessControl,path);

                break;
            }

              case EShLangTessEvaluation :
            {   std::string path = in_raw_pipe.folder_path;
                path += in_raw_pipe.stage_pair[i].second;
                contained_flags |= Shader_Stagez::TESS_EVAL_SHADER;
                compled_stages.at(TESS_EVAL_ARRAY_POS)=gen_SPIRV(EShLangTessEvaluation,path);

                break;
            }

            case EShLangGeometry:
            {   std::string path = in_raw_pipe.folder_path;
                path += in_raw_pipe.stage_pair[i].second;
                contained_flags |= Shader_Stagez::GEOMETRY_SHADER;
                compled_stages.at(GEO_ARRAY_POS)= gen_SPIRV(EShLangGeometry,path);

                break;
            }
            case EShLangCompute :
            {   std::string path = in_raw_pipe.folder_path;
                path += in_raw_pipe.stage_pair[i].second;
                contained_flags |= Shader_Stagez::COMPUTE_SHADER;
                compled_stages.at(COMPUTE_ARRAY_POS) = gen_SPIRV(EShLangCompute,path);
                std::cout << "DEBGU###########EShLangCompute:::" << '\n';
                break;
            }

            case EShLangFragment :
            {
                std::string path = in_raw_pipe.folder_path;
                path += in_raw_pipe.stage_pair[i].second;
                contained_flags |= Shader_Stagez::FRAGMENT_SHADER;
                compled_stages.at(FRAG_ARRAY_POS) = gen_SPIRV(EShLangFragment,path);

                break;
            }
        }
    }
  compled_pipe_code.insert(std::make_pair(in_raw_pipe.pipe_name,std::make_pair(contained_flags,compled_stages)));
}

const std::vector<unsigned int> parser_vulkan_modual::gen_SPIRV(EShLanguage in_shd_type, std::string path)
{

  std::cout << "####SHADER_FILE SPIRV begin FOR:: SHADERTYPE::" << in_shd_type << "  path::" << path <<'\n' <<'\n';
  if (!glslangInitialized)
  {
    std::cout << "\n##########NOTE::glslangInitialized was not inilazed starting now\n";
    glslangInitialized=   glslang::InitializeProcess();
    std::cout << "stauz:" << glslangInitialized <<'\n';
  }
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cout << "Failed to load shader: " << path << std::endl;
        throw std::runtime_error("failed to open file: " + path);
    }
    std::string InputGLSL((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());


    const char* InputCString = InputGLSL.c_str();

    EShMessages messages = (EShMessages) (EShMsgSpvRules | EShMsgVulkanRules | EShMsgDebugInfo);

    glslang::TProgram& program = *new glslang::TProgram;
    glslang::TShader* shader = new glslang::TShader(in_shd_type);
    razar_vulkan_includer Includer;

    shader->setStrings(&InputCString, 1);

    //glslang::TShader Shader(in_shd_type);

    glslang::EShTargetClientVersion VulkanClientVersion = glslang::EShTargetVulkan_1_2;
    glslang::EShTargetLanguageVersion TargetVersion = glslang::EShTargetSpv_1_5;

    shader->setEnvInput(glslang::EShSourceGlsl, in_shd_type, glslang::EShClientVulkan, VULKAN_CLIENT_VIERSON);
    shader->setEnvClient(glslang::EShClientVulkan, VulkanClientVersion);
    shader->setEnvTarget(glslang::EShTargetSpv, TargetVersion);

    TBuiltInResource Resources;
    InitResources(Resources);
     shader->setAutoMapBindings(true);
     shader->setAutoMapLocations(true);
     shader->setUniformLocationBase(0);
    //glslang::TShader::Includer//;
    std::string dir = "../shaderzglsl/elemental/compute_partical";
    Includer.pushExternalLocalDirectory(dir);
    //Shader.Includer.pushExternalLocalDirectory(path);

    std::string PreprocessedGLSL;


    if (!shader->preprocess(&Resources, GLSL_DEFULT_VER, ENoProfile, false, false, messages, &PreprocessedGLSL, Includer))
{
    std::cout << "GLSL Preprocessing Failed for: " << path << std::endl;
    std::cout << shader->getInfoLog() << std::endl;
    std::cout << shader->getInfoDebugLog() << std::endl;
  exit(5);
}
std::cout << shader->getInfoLog() << std::endl;
std::cout << shader->getInfoDebugLog() << std::endl;
std::cout << "##->GLSL Preprocessing..compleate\n";

const char* PreprocessedCStr = PreprocessedGLSL.c_str();
shader->setStrings(&PreprocessedCStr, 1);

if (!shader->parse(&Resources, VULKAN_CLIENT_VIERSON, false, messages))
{
    std::cout << "GLSL Parsing Failed for: " << path << std::endl;
    std::cout << shader->getInfoLog() << std::endl;
    std::cout << shader->getInfoDebugLog() << std::endl;
  exit(5);
}
std::cout << shader->getInfoLog() << std::endl;
std::cout << shader->getInfoDebugLog() << std::endl;
std:: cout << "##->GLSL Parsing..compleate\n";

program.addShader(shader);

if(!program.link(messages))
{
    std::cout << "GLSL Linking Failed for: " << path << std::endl;
    std::cout << shader->getInfoLog() << std::endl;
    std::cout << shader->getInfoDebugLog() << std::endl;
    exit(5);
}
std::cout << shader->getInfoLog() << std::endl;
std::cout << shader->getInfoDebugLog() << std::endl;
if (!program.mapIO())
    {
      std::cout << "GLSL mapIO Failed for: " << path << std::endl;
      std::cout << shader->getInfoLog() << std::endl;
      std::cout << shader->getInfoDebugLog() << std::endl;
      exit(5);
    }
    std::cout << shader->getInfoLog() << std::endl;
    std::cout << shader->getInfoDebugLog() << std::endl;
std:: cout << "##->GLSL Linking..compleate\n";
int ReflectOptions = EShReflectionDefault;
program.buildReflection(ReflectOptions);
 program.dumpReflection();

std::vector<unsigned int> SpirV;
spv::SpvBuildLogger logger;
glslang::SpvOptions spvOptions;
spvOptions.generateDebugInfo = true;
 spvOptions.stripDebugInfo = true;
bool SpvToolsValidate = true;
 //spvOptions.disassemble = SpvToolsDisassembler;
  spvOptions.validate = SpvToolsValidate;
//glslang::GlslangToSpv(*program.getIntermediate(in_shd_type), SpirV, &logger, &spvOptions);
std::cout<< "###program log info: \n"<< program.getInfoLog() << "\n#######\n";
//printf("%s", logger.getAllMessages().c_str());
//glslang::OutputSpvBin(SpirV, GetBinaryName((in_shd_type));

std::cout << "####SHADER_FILE SPIRV GENRATED FOR:: SHADERTYPE::" << in_shd_type << " path::" << path << '\n' << "size::" << SpirV.size() <<'\n';
if(SpirV.size() == 0)
{
  std::cerr << "###ERRROR SPIVRV IS ZERO....\n";
  //exit(5);
}
return SpirV;
}

namespace spv {

void SpvBuildLogger::tbdFunctionality(const std::string& f)
{
    if (std::find(std::begin(tbdFeatures), std::end(tbdFeatures), f) == std::end(tbdFeatures))
        tbdFeatures.push_back(f);
}

void SpvBuildLogger::missingFunctionality(const std::string& f)
{
    if (std::find(std::begin(missingFeatures), std::end(missingFeatures), f) == std::end(missingFeatures))
        missingFeatures.push_back(f);
}

std::string SpvBuildLogger::getAllMessages() const {
    std::ostringstream messages;
    messages << "\n#####getAllMessages###\n";
    for (auto it = tbdFeatures.cbegin(); it != tbdFeatures.cend(); ++it)
        messages << "TBD functionality: " << *it << "\n";
    for (auto it = missingFeatures.cbegin(); it != missingFeatures.cend(); ++it)
        messages << "Missing functionality: " << *it << "\n";
    for (auto it = warnings.cbegin(); it != warnings.cend(); ++it)
        messages << "warning: " << *it << "\n";
    for (auto it = errors.cbegin(); it != errors.cend(); ++it)
        messages << "error: " << *it << "\n";
    return messages.str();
}

} // end spv namespace
