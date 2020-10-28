
#ifndef FLAGZ_TEMPLATEZ_03_HPP
#define FLAGZ_TEMPLATEZ_03_HPP

#include <type_traits>


//macros
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

/*
Template CONSTEXPER FUNCTIONS...enum class shader_type : uint32_t {
     SHADER_NULL         = 0x00,
     COMPUTE_SHADER      = 0x02,
     VERTEX_SHADER       = 0x04,
     FRAGMENT_SHADER     = 0x08,
     TESS_CONTROL_SHADER = 0x10,
     TESS_EVAL_SHADER    = 0x20,
     GEOMETRY_SHADER     = 0x40,
     ALL_PIPE            = 0x80
};
template<>
struct EnableBitMaskOperators<shader_type>
{
    static const bool enable = true;
};
*/


template<typename E>
constexpr auto underlying_type(E e) -> typename std::underlying_type<E>::type
{
   return static_cast<typename std::underlying_type<E>::type>(e);
}
/*
template <typename Enumeration>
auto underlying_type(Enumeration const value)-> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}*/

/* TODO::
//setup bitmaskable veratic Enums
//note check better veratdic template oprator sharing
*/


/*
* BITMASK ENUMZ template work
*/

/*
USAGE::: place this header in include.. ether apend or and others to another hpp. example given bellow.

*ENUMZ  USILTZEING BITMASKz functionality
*NOTE: require the template<> to activate bitmask
*/

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


template<typename Enum>
struct EnableBitMaskOperators
{
      static const bool enable = false;
};

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator |(Enum lhs, Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<Enum> (
        static_cast<underlying>(lhs) |
        static_cast<underlying>(rhs)
    );
};

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type&
operator |=(Enum &org,Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return org =static_cast<Enum> (static_cast<underlying>(org) |  static_cast<underlying>(rhs));

};

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator ~(Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return  static_cast<Enum> (~static_cast<underlying>(rhs));
};

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator &(Enum lhs,Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return  static_cast<Enum> (static_cast<underlying>(lhs)& static_cast<underlying>(rhs));
};

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator &=(Enum &lhs, Enum rhs)
{
   using underlying = typename std::underlying_type<Enum>::type;

    lhs = static_cast<Enum> (
        static_cast<underlying>(lhs) &
        static_cast<underlying>(rhs)
    );
    return lhs;
};

#endif
