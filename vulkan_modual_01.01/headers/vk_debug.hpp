


//#include <vulkan/vulkan.h>

#include <fstream>


 #include <ctime>           
#include <iostream>

class logger
{
   
    public : 
    void operator()(void* data) 
    {   
         std::fstream logstream("debuglogfile.logtx",std::fstream::out|std::fstream::app); 
        time_t rawtime;
        time (&rawtime);
        std::string stingtime = ctime(&rawtime);
       // std::cout <<stingtime;
        stingtime.erase(stingtime.end()-1);
       // logstream.open();
        logstream << stingtime<< ":->##::" << reinterpret_cast<const char*>(data) << '\n';
        logstream.close();

    }; 

     
   // friend std::ostream& operator << (std::ostream& os, const logger& loging); 
};

