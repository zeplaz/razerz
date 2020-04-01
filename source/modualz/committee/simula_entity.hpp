

#ifndef RA_SIMULA_ENTITY_HPP
#define RA_SIMULA_ENTITY_HPP

#include "../phyziz/collision_AI.hpp"
#include "../phyziz/bullet_collision.hpp"
#include "../geometry/geometry.hpp"

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

enum contact_type
{CONTACT_ENTER,CONTACT_EXIT,CONTACT_STAY};

struct Object_pair{
  simula_entity* _a;
  simula_entity* _b;

  Object_pair(simula_entity* objA, simula_entity* objB)
  {
    _a = objA;
    _b = objB;
  }

  bool operator < (const object_pair& pair) const
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
  return (total_frames_in_contact ==1)
  }

   bool is_contact_stale()
   {
     return last_frame_in_contact !=current_frame;
   }

};

typedef std::map<Object_pair,Contact_info> contact_map_type;
//call post simstef


#endif
