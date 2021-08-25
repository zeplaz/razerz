

#include <glm/glm.hpp>
struct rigid_body{
    glm::vec3 position;
    glm::vec3 size;;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    doube mass;
};



template<typename DERIVED_ENTITY>
struct Base_entity{

    typedef DERIVED_ENTITY entity_type;
    DERIVED_ENTITY& true_this()
    {
        return static_cast<DERIVED_ENTITY&>(*this);
    }

    const DERIVED_ENTITY& true_this()const
    {
        return static_cast<const DERIVED_ENTITY&>(*this);
    }
    

    protected : 
    ~Base_entity(){}
    Base_entity(const Base_entity&)

    public :
   
    
};

template<typename... Mixins>
struct objects : public Base_entity<objects>, public Mixins...
{
    int id;
};







template<typename T>
class game_object
{
public : 
void update_postion();

protected :

private:
std::vector<ridge_body> m_bodies;

};


class peripheral_device
{

};

template<typename Entity>
class Input_component
{


    public : 
    void update(Entity& ent)
    {
        switch()
    }
}

class Physiscs_component
{

};