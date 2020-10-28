#ifndef common_tuple_hash_h
#define common_tuple_hash_h


// from  nsuke/tuple_hash.h 
 //std::hash specialization for std::tuple from StackOverflow.com 
 //https://gist.github.com/nsuke/5990643#file-tuple_hash-h
#include <tuple>
namespace std{
  namespace
  {
    template <class t>
    inline void hash_combine(std::size_t& seed, t const& v)
    {
      seed ^= hash<t>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    }

    template <class tuple,
             size_t index = std::tuple_size<tuple>::value - 1>
    struct hashvalueimpl
    {
      static void apply(size_t& seed, tuple const& tuple)
      {
        hashvalueimpl<tuple, index-1>::apply(seed, tuple);
        hash_combine(seed, get<index>(tuple));
      }
    };

    template <class tuple>
    struct hashvalueimpl<tuple,0>
    {
      static void apply(size_t& seed, tuple const& tuple)
      {
        hash_combine(seed, get<0>(tuple));
      }
    };
  }

  template <typename ... tt>
  struct hash<std::tuple<tt...>> 
  {
    size_t
      operator()(std::tuple<tt...> const& tt) const
      {                                              
        size_t seed = 0;                             
        hashvalueimpl<std::tuple<tt...> >::apply(seed, tt);    
        return seed;                                 
      }                                              

  };
}
#endif
