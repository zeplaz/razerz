

#ifndef RA_SIMULA_ENTITY_HPP
#define RA_SIMULA_ENTITY_HPP

#include "../phyziz/collision_AI.hpp"
#include "../phyziz/bullet_collision.hpp"
#include "../geometry/geometry.hpp"


enum class Contact_type
{CONTACT_ENTER,CONTACT_EXIT,CONTACT_STAY};

struct bullet_object;
class simula_entity : public sym_object
{
  private :
  collision_enity internal_collison_enity;
  btAlignedObjectArray<mesh> mesh_array;
  bullet_object* bullet_container;

  public :
    bool is_ghost = true;
    bool has_physiz = false;

 void add_bullet_obj( void* in_body)
 {
    // bullet_container = bullet_obj;
  //  bullet_object new_object(in_body,this);
    bullet_container = new bullet_object(in_body, this);
    bool has_physiz = true;
 }

 void add_mesh(mesh in_mesh)
 {
    mesh_array.push_back(in_mesh);
    bool is_ghost = false;
  }

  void make_ghost()
  {
    is_ghost = true;
  }

  void disable_physiz()
  {
    has_physiz = false;
  }

  void on_contact_event(simula_entity* in_other_entity, Contact_type in_type_contact)
  {
    switch(in_type_contact)
    {

      case Contact_type::CONTACT_ENTER :
      {
        std::cout <<"objectID::" <<this->get_id()  << ", has made a collison with objectID::" << in_other_entity->get_id() <<'\n';
        break;
      }

      case Contact_type::CONTACT_EXIT :
      {
          std::cout <<"objectID::" <<this->get_id()  << ",  has exited a collison with objectID::" << in_other_entity->get_id() <<'\n';
        break;
      }

      case Contact_type::CONTACT_STAY :
      {
        std::cout << "stillcontacts....dooom resolve call?\n";
        break;
      }
    }
  }


  void update()
  {
    if(has_physiz)
    {
      btTransform tranz;
        switch(bullet_container->bp_body.body_type)
        {
          case Body_type::B_RIGID_BODY :
          {
          auto b_body  = static_cast<btRigidBody*>(bullet_container->bp_body.get_body());
          b_body->getMotionState()->getWorldTransform(tranz);
          break;
          }
        }
      float mat[16];
      tranz.getOpenGLMatrix(mat);
      glm::mat4 gmmat4 = glm::make_mat4(mat);
      for(size_t i =0; i< mesh_array.size(); i++)
      {
        mesh_array[i].update_motion_matrix(gmmat4);
      }
    }
  }

  void render(){
    if(!is_ghost)
    {
     for(size_t i = 0; i< mesh_array.size(); i++)
     {
       mesh_array[i].draw_via_cache();
     }
    }
  }

};



struct Object_pair{
  simula_entity* _a;
  simula_entity* _b;

  Object_pair(simula_entity* objA, simula_entity* objB)
  {
    _a = objA;
    _b = objB;
  }

  bool operator < (const Object_pair& pair) const
   {
    unsigned int ourlow =std::min(_a->get_id(),_b->get_id());
    unsigned int ourhigh= std::max(_a->get_id(),_b->get_id());

    unsigned int theirlow =std::min(pair._a->get_id(),pair._b->get_id());
    unsigned int theirhigh =std::max(pair._a->get_id(),pair._b->get_id());

    if(ourlow < theirlow)
    return true;
    if(ourlow==theirlow)
    {
      return ourhigh < theirhigh;
    }

    return false;
  }
};

struct Contact_info{
  int last_frame_in_contact;
  int total_frames_in_contact;
  Contact_info()
  {
    last_frame_in_contact = 0;
    total_frames_in_contact = 0;
  }
  void update(const int current_frame)
  {
    last_frame_in_contact = current_frame;
    ++total_frames_in_contact;
  }

  bool is_new_contact()
  {
  return (total_frames_in_contact ==1);
  }

   bool is_contact_stale(const int current_frame)
   {
     return last_frame_in_contact !=current_frame;
   }

};

typedef std::map<Object_pair,Contact_info> contact_map_type;


//call post simstef
void check_collision_simula_obj(bullet_collision_detector* in_detector,contact_map_type& in_contact_map)
{
  static int this_frame = 0;
  ++this_frame;
  int num_manifolds = in_detector->dynamicsWorld->getDispatcher()->getNumManifolds();

  for(int i =0; i< num_manifolds; i++)
  {
    btPersistentManifold* contact_manfold = in_detector->dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
    const btCollisionObject* objA = static_cast<const btCollisionObject*>(contact_manfold->getBody0());
    const btCollisionObject* objB = static_cast<const btCollisionObject*>(contact_manfold->getBody1());

    int num_contacts = contact_manfold->getNumContacts();

    if(num_contacts >0)
    {
      simula_entity* a = static_cast<simula_entity*>(objA->getUserPointer());
      simula_entity* b = static_cast<simula_entity*>(objB->getUserPointer());

      if(a&&b)
      {
        in_contact_map[Object_pair(a,b)].update(this_frame);
      }
    }
  }

contact_map_type::iterator iter= in_contact_map.begin();

while(iter!=in_contact_map.end())
{
  if(iter->second.is_new_contact())
  {
    iter->first._a->on_contact_event(iter->first._b,Contact_type::CONTACT_ENTER);
    iter->first._b->on_contact_event(iter->first._a,Contact_type::CONTACT_ENTER);
    ++iter;
  }
  else if(iter->second.is_contact_stale(this_frame))
  {
    iter->first._a->on_contact_event(iter->first._b,Contact_type::CONTACT_EXIT);
    iter->first._b->on_contact_event(iter->first._a,Contact_type::CONTACT_EXIT);
    contact_map_type::iterator iter_to_delete = iter;
    ++iter;
    in_contact_map.erase(iter_to_delete);
  }

  else {
    iter->first._a->on_contact_event(iter->first._b,Contact_type::CONTACT_STAY);
    iter->first._b->on_contact_event(iter->first._a,Contact_type::CONTACT_STAY);
    ++iter;
  }
}
}

#endif
