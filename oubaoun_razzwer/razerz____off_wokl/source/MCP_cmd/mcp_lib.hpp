
#pragma once
#include "../basez/gl_lib_z.hpp"
#include <memory>

static int next_cu_ID = 0;

enum class FBO_type  : GLint
{
VIRTUAL,
TEXTURAL_BASE,
FLOATING,
INTEGER,
LAYERED,
MULTI_DRAW,
MULTI_TEXTURE,
MULTI_ATTACHMENT
};


template<>
struct EnableBitMaskOperators<FBO_type>
{
    static const bool enable = true;
};
/*
template<typename Inher_type>
class singleton_exd
{
  protected :

  static std::weak_ptr<Inher_type> _singleton;

  public :
  int cmd_unit_ID;
  singleton_exd(const singleton_exd&) = delete;
  singleton_exd(singleton_exd&&) = delete;
  singleton_exd& operator=(const singleton_exd&) = delete;
  singleton_exd& operator=(singleton_exd&&) = delete;

  static std::shared_ptr<Inher_type> singleton_exd()
  {
    std::shared_ptr<Inher_type> singleton = _singleton.lock();
    if(!singleton)
    {
      singleton.reset(new Inher_type());
      _singleton =singleton;
    }
    init();
    return singleton;
  }

  inline void init()
  {
    cmd_unit_ID =next_cu_ID;
    next_cu_ID++;
  }
};
template<typename Inher_type>
std::weak_ptr<Inher_type> singleton_exd<Inher_type>::_singleton;
*/


template<typename Inher_type>
class singleton
{
  protected :
  singleton()
  {
    init();
  };

  public :
  int cmd_unit_ID;
  singleton(const singleton&) = delete;
  singleton &operator = (const singleton&)=delete;

  inline void init()
  {
    cmd_unit_ID =next_cu_ID;
    next_cu_ID++;
  }

  static Inher_type& get_instance()
  {
    static Inher_type instance;
    return instance;
  }
};
