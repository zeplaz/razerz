
#ifndef RZ2_STATIC_INTERFACEE_HPP
#define RZ2_STATIC_INTERFACEE_HPP

template<typename T, bool SMALL_OBJECT = (sizeof(T)<sizeof(void*))>
struct clone_of;

    template<typename T>
    struct clone_of<T,true>
    {
         typedef T type;
    };

    template<typename T>
    struct clone_of<T,false>
    {
        typedef const T& type;
    };
   

template<typename static_type, typename aux_t = void>
class static_interface
{
    public : 
    typedef static_type type;

    typedef clone_of<static_type>::type clone()const;

    protected : 
    static_interface(){}
    ~static_interface(){}

    static_type& true_this()
    {
        return static_cast<static_type&>(*this);
    }

    const static_type& true_this() const
    {
        return static_cast<const static_type&>(*this);
    }
};   


#define MAC_STATIC_INTERFACE(NAME)   \
                                              \
template<typename static_type>                \
class NAME : public static_interface<static_type>

#define MAC_STATIC_TEMPLATE_INTERFACE(NAME,T)   \
                                                \
template<typename static_type,typename T>       \
class NAME : public static_interface<static_type, NAME<static_type,T> >

#define MAC_SPECIALIZED this->true_this()

#endif


MAC_STATIC_INTERFACE(entity)
{
  protected : 
  ~entity(){}
  public : 
  typedef int value_type;
  value_type operator()() const 
  {
    return MAC_SPECIALIZED();
  }
};

#define MAC_SPECIALIZATION(S,I) \
                                \
class S : public I<S>


MAC_SPECIALIZATION(rigid_body_entity,entity)
{
  public : 
  double get_max_speed() const
  {
    return max_speed;
  }

  void set_max_speed(double in_d)
  {
    max_speed = in_d;
  }
  protected : 
  double max_speed;
};

