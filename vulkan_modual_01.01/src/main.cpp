
/*
OCT15
g++ -std=c++17  main.cpp vulkan_api.cpp vk_abstracionz.cpp vk_shaderz.cpp   glad/src/vulkan.c exrtn_vulkan.cpp -o vlkantest.out  -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi -lxcb -lglslang -lSPIRV
*/


#include "../headers/vulkan_api.hpp"
#include <iostream>

#include "../headers/vk_shaderz.hpp"

constexpr const char* SHADER_INFO_PATHNAME = "shader_build_info.info";
void parserun(){


   parser_vulkan_modual vm_parser; 
   vm_parser.shader_info_reader(SHADER_INFO_PATHNAME);
   //glslang::TShader shader(EShLangVertex);
}


/*
if cmake is having issues with linking can use 
g++ -std=c++17  main.cpp vulkan_api.cpp  exrtn_vulkan.cpp -o vlkantest.out  -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
*/ 

int main(int arg, char* argv[])
{
 
    //vulkan_api vk_api; 
    vulkan_app vk_app;
    
    try{
        parserun();
        vk_app.run();  
       }

catch (const std::exception& e) {
    std::cerr<<"###ERRRPRPRPRPRPRP::::EXEPCTIONZ" << e.what() <<'\n';
 }
 



    //vk_api.inaltize_vulkan_instance();   
    //vk_api.setup_debug();
    
   
 return 0;   
}