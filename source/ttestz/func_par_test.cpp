
#include "../basez/gl_lib_z.hpp"
#include "../parserz/parserlib.hpp"

#include <valarray>

std::valarray<bool>* bool_flag_retrval(std::string& in_substring)
{
        size_t em_size = in_substring.size()-2;
        int even  = em_size%2;
        int commaz =  (em_size/2)-even;// (em_size-2-even)/2;
        std::valarray<bool>* temp_boolarray = new std::valarray<bool>(em_size-commaz);

  for(size_t k = 0; k< in_substring.size(); k++)
  {
    if(in_substring[k]=='{')
    {
      commaz = 0;
      for(int ki = 0; ki <em_size; ki++)
      {
        if(in_substring[k+ki+1] =='}')
      {
        k+=ki;
        break;
      }
      else if(in_substring[k+ki+1] ==',')
      {
        commaz++;
        continue;
      }
      else
      {
       temp_boolarray[ki-commaz] = static_cast<bool>(in_substring[k+ki+1]);
      }
    }
  }
  return temp_boolarray;
}




int main(int argc, char* argv[])
{

  std::cout <<"\n #####compleate\n \n  \a";


  return 0;
}
