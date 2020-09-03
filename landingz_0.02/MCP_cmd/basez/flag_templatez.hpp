
#ifndef LANDINGZ_FLAGZ_TEMPLATEZ_HPP
#define LANDINGZ_FLAGZ_TEMPLATEZ_HPP


//macros
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

/*
Template CONSTEXPER FUNCTIONS...
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
