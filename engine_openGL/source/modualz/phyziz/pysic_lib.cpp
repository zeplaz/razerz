
#include "pysic_lib.hpp"

void goalz::update_channels(const goalz& other)
{
  if(other.has_pos)
  {
    pos=other.pos;
    has_pos = true;
  }

  if(other.has_orientation)
  {
    orientation=other.orientation;
    has_orientation = true;
  }

  if(other.has_velocity)
  {
    velocity=other.velocity;
    has_velocity = true;
  }
  if(other.has_rotation)
  {
    rotation = other.rotation;
    has_rotation = true;
  }
}



float kinematic::fix_new_orientation(float current, glm::vec3 velocity)
{
  if(velocity.length()>0)
  {
    return std::atan2(-staticz.pos.x,staticz.pos.z);
  }
  else
  {
    return current;
  }
}

void kinematic::update(steering_output in_streer, const float& time)
{
  staticz.pos = velocity*time;
  staticz.orientation = rotation*time;

  velocity += in_streer.linear*time;
  rotation += in_streer.angular*time;
}


void kinematic::update(steering_output in_streer, float max_speed, const float& time)
{
  staticz.pos = velocity*time;
  staticz.orientation = rotation*time;

  velocity += in_streer.linear*time;
  rotation += in_streer.angular*time;

  if(velocity.length()>max_speed)
  {
    velocity = glm::normalize(velocity);

    velocity*=max_speed;
  }
}



  steering_output kinematic_variable_behav::get_steering_align(float acceleration)
  {
    steering_output result;
    float rotation = target.staticz.orientation-agent.staticz.orientation;

  }
  steering_output kinematic_variable_behav::get_steering_seek(float acceleration)
  {
    steering_output result;

    result.linear = target.staticz.pos-agent.staticz.pos;
    result.linear = glm::normalize(result.linear);
    if(acceleration ==0)
    {
    result.linear *=max_acceleration;
    }
    else
    {
      result.linear *=acceleration;
    }
    result.angular =0;
    return result;

  }

  steering_output kinematic_variable_behav::get_steering_flee(float acceleration)
  {
    steering_output result;

    result.linear = agent.staticz.pos-target.staticz.pos;
    result.linear = glm::normalize(result.linear);
    if(acceleration ==0)
    {
    result.linear *=max_acceleration;
    }
    else
    {
      result.linear *=acceleration;
    }
    result.angular =0;
    return result;

  }

    steering_output kinematic_variable_behav::get_steering_arrive(float speed)
    {
     steering_output result;
     float set_speed;
     if(speed ==0)
     {
       set_speed= max_speed;
     }
     else
     {
       set_speed = max_speed;
     }
    glm::vec3 direction = target.staticz.pos - agent.staticz.pos;
    float distance = direction.length();

    if(distance < target_radius)
    { result.linear =glm::vec3(0.0f);
      result.angular = 0.0f;

      return result;
    }
    if(distance < slowdown_radius)
    {
      set_speed = set_speed*distance/slowdown_radius;
    }
    direction = glm::normalize(direction);
    direction *=set_speed;
    result.linear = direction - agent.velocity;
    result.linear /= TIMETO_TARGET_VAR;

    if(result.linear.length()>max_acceleration)
    {
      result.linear = glm::normalize(result.linear);
      result.linear *=max_acceleration;
    }
    result.angular =0;
    return result;
    }



  float kinematic_base_behav::fix_new_orientation(float current, glm::vec3 velocity)
  {
    if(velocity.length()>0)
    {
      return std::atan2(-velocity.x,velocity.z);
    }
    else
    {
      return current;
    }
  }

  kinematic_steering_output kinematic_base_behav::get_steering_flee(float speed)
  {
    kinematic_steering_output result;

    result.velocity = agent.pos-target.pos;
    result.velocity= normalize(result.velocity);
    if(speed ==0)
    {
    result.velocity *=maxspeed;
    }
    else
    {
      result.velocity *=speed;
    }


    agent.orientation = fix_new_orientation(agent.orientation,result.velocity);
    result.rotation =0;
    return result;

  }

  kinematic_steering_output kinematic_base_behav::get_steering_seek(float speed)
  {
    kinematic_steering_output result;

    result.velocity = target.pos-agent.pos;
    result.velocity= normalize(result.velocity);
    if(speed ==0)
    {
    result.velocity *=maxspeed;
    }
    else
    {
      result.velocity *=speed;
    }


    agent.orientation = fix_new_orientation(agent.orientation,result.velocity);
    result.rotation =0;
    return result;

  }

  kinematic_steering_output kinematic_base_behav::get_steering_arrive(float speed)
  {
      float set_speed;
      if(speed!=0)
      {
        set_speed=speed;
      }
      else {
        set_speed = maxspeed;
      }
      kinematic_steering_output result;
      result.velocity = agent.pos-target.pos;

      if(result.velocity.length()<arrival_radius)
      {
        result.rotation =0;
        result.velocity = glm::vec3(0.0f);
        return result;
      }
      result.velocity /=TIMETO_TARGET_BASE;
      if(result.velocity.length()>set_speed)
      {
        result.velocity= glm::normalize(result.velocity);
        result.velocity *=set_speed;
      }
      agent.orientation =fix_new_orientation(agent.orientation,result.velocity);
      result.rotation =0;
      return result;
  }

    kinematic_steering_output kinematic_base_behav::get_steering_wonder(float speed)
    {
      float set_speed;
      if(speed!=0)
      {
        set_speed=speed;
      }
      else {
        set_speed = maxspeed;
      }
      kinematic_steering_output result;

      result.velocity = set_speed*glm::vec3(agent.orientation);
      result.rotation = max_rotation*random_binomial();
    }


void material_phys::set_paramz(Interaction_Method in_type,std::array<float,7> in_valz)
{ im_type = in_type;
  mass  = in_valz[0];
  restitution= in_valz[1];
  linear_damping  = in_valz[2];
  angular_damping= in_valz[3];
  friction  = in_valz[4];
  rolling_friction  = in_valz[5];
  margin  = in_valz[6];
}
