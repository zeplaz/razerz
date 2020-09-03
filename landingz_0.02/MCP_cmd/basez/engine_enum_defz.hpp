
#ifndef LANDINGZ_ENGINE_ENUM_DEFZ_HPP
#define LANDINGZ_ENGINE_ENUM_DEFZ_HPP


#include <random>
#include <functional>
#include  <bitset>
#include "flag_templatez.hpp"

/*
::::Example:::::
 ( place theze in another file or at end of this one  will enable flag ablitys via oprators!)

NOTE:: that has logic opratores DEFINED!

      enum class classname : sometype {};
      template<>
      struct EnableBitMaskOperators<classname>
      {
          static const bool enable = true;
      };
*/


template<int SIZE_INT>
  class flag_hasher
  {
    std::hash<std::bitset<SIZE_INT>> hash_fn;

    size_t hashed_val(std::bitset& in_bitset)
    {
     return  hash_fn(in_bitset);
    }
  };

class bithandler
{
 int deligate(const std::bitset& in_bitset) const
  {
    if(in_bitset.all())
    {

      return -in_bitset.size();
    }
    if(in_bitset.none)
    {
      return 0;
    }
    switch(in_bitset)




  }
};
if()


template<typename type,typename distro= int>
class randomizer
{
    std::default_random_engine e;



  std::uniform_int_distribution<> d(0, 10);
  auto rnd = std::bind(d, e); /
};



  / a copy of e is stored in rnd

    for(int n=0; n<10; ++n)
        std::cout << rnd() << ' ';
    std::cout << '\n';

#endif
