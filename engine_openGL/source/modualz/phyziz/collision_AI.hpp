
#ifndef RA_PYS_COLLISION_AI_HPP
#define RA_PYS_COLLISION_AI_HPP

#include "bullet_collision.hpp"

/*void set_ray_callbac(view_lenz& in_lenz, bool all)
{
//  btCollisionWorld::ClosestRayResultCallback(btVector3(lenz.z,lenz.pos.x,lenz.pos.y),btVector3(drectionetc*nummber));
//  btCollisionWorld::AllHitsRayResultCallback();
}*/

/*
struct ray_result_callback
{
  btScalar closest_hit_fraction;
  btCollisionObject* collision_obj;
  short int collision_filter_group;
  short int collision_filter_mask;

  unsigned int flagz;

  virtual ~ray_result_callback()
  {}
  bool has_hit() const
  {
    return (collision_obj!=0);
  }

    ray_result_callback():
     closest_hit_fraction{btScalar(1.0)},
     collision_obj{0},
     collision_filter_group,
     collision_filter_mask

};*/


class collision_avoidance{
kinematic agent;
float max_acceleration;
//a vector or linked list?
//std::vector<kinmatic> target_vec;
std::list<kinematic> target_list;
float radius;

public :
steering_output get_steering();

};

class collisition_detector
{//this has to use a physic engere or somthing?were bullet comes in?
  public :
  collision_enity get_collision(glm::vec3 pos,glm::vec3 move_ammount);

};


class obstacle_avodance : public kinematic_variable_behav{ //: public seek{

  collisition_detector detector;
//min dis to wall must be greater that chactor ratius
  float avoid_distance;
  float look_ahead;
  //rest of seek stuff... if no inheart
public :
steering_output get_steering()
{
  steering_output result;
  glm::vec3 ray = agent.velocity;
  ray = glm::normalize(ray);
  ray *=look_ahead;
  collision_enity collision = detector.get_collision(agent.staticz.pos,ray);
  if(collision.is_null == true)
  {
    result.linear = glm::vec3(0.0);
    result.angular = 0;

    return result;
  }
  glm::vec3 target = collision.pos+collision.normal * avoid_distance;
//  return get_steering_seek(....);

}
  //void?//
};
/*
std::for_each(target_list.begin(),target_list.end(), somefucntion()
{

}*/
#endif
