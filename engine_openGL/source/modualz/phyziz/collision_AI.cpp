
#include "collision_AI.hpp"

steering_output collision_avoidance::get_steering()
{//somethingabout checking the closts one...

  steering_output result;
  float shortest_time=FLT_MAX;
  kinematic first_target;
  bool found_target = false;
  float first_min_separation;
  float first_distance;
  glm::vec3 first_relative_pos;
  glm::vec3 first_relative_velocity;


  glm::vec3 relative_pos;
  glm::vec3 relative_velocity;
  float relative_speed;
  float time_to_collision;
  float distance;
  float min_separation;

  for (std::list<kinematic>::iterator iterator = target_list.begin(), end = target_list.end(); iterator != end; ++iterator)
   {
     relative_pos = iterator->staticz.pos-agent.staticz.pos;
     relative_velocity=iterator->velocity- agent.velocity;
     relative_speed = relative_velocity.length();
     time_to_collision = glm::dot(relative_pos,relative_velocity)/(relative_speed*relative_speed);
     distance = relative_pos.length();
     min_separation = distance - relative_speed*time_to_collision;
    if(min_separation>(2*radius))
    continue;

    if(time_to_collision>0&&time_to_collision<shortest_time)
    {
      shortest_time = time_to_collision;
      first_target = *iterator;
      first_min_separation = min_separation;
      first_distance= distance;
      first_relative_pos= relative_pos;
      first_relative_velocity=relative_velocity;
      found_target = true;
    }
  }
  if(found_target == false)
  {
    //make reuslt zeroz
    result.linear = glm::vec3(0.0f);
    result.angular = 0;
    return result;
  }

  if(first_min_separation<=0 || first_distance <2*radius)
  {
    relative_pos = first_target.staticz.pos - agent.staticz.pos;
  }
else{
  relative_pos = first_relative_pos+first_relative_velocity*shortest_time;
}
relative_pos= glm::normalize(relative_pos);
result.linear = relative_pos*max_acceleration;
result.angular =0;
return result;
}
