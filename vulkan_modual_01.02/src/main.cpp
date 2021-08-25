#include "../headers/vulkan_api_02.hpp"
#include <iostream>


int main(int arg, char* argv[])
{
    vulkan_app vk_app;

    try{
        vk_app.run();
       }

catch (const std::exception& e) {
    std::cerr<<"###ERRRPRPRPRPRPRP::::EXEPCTIONZ" << e.what() <<'\n';
 }

 return 0;
}
