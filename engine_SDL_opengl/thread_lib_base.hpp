


//threadlib_base.


#include <thread>       
#include <atomic> 
#include <vector>
#include <semaphore>



struct thread_manger
{
    int hardware_thread_count;
    std::vector<std::jthread> main_thread_pool;
    std::vector<bool> avaliable;
    void detect_thread_count()
    {
        hardware_thread_count = std::jthread::hardware_concurrency();
    }
    
    void define_thread_pool
    {
     detect_thread_count();
     main_thread_pool.resize(hardware_thread_count);

     for(int i; i <hardware_thread_count;i++)
     {
      std::jthread jthrd;
      main_thread_pool.push_back(jthrd);
     }   
    }

};