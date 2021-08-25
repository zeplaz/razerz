#ifndef LOC_VULKAN_APP_02
#define LOC_VULKAN_APP_02

/*
//*********************************************

#########******class vulkan_app{*****#########

***********************************************
*/
//forward declationz
struct vulkan_api;

class vulkan_app{

    vulkan_api* vk_api;

    public :

    vulkan_app();
    void run()
    {
        vulkan_inialz();
        loop();
        shutdown();
    }
    private :
    void loop();
    bool vulkan_inialz();
    void shutdown();
};


#endif
