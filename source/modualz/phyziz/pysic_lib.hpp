

#ifndef RA_PYSIC_LIB_HPP
#define RA_PYSIC_LIB_HPP

#include "../basez/gl_lib_z.hpp"
#define GLM_ENABLE_EXPERIMENTAL

#include  <glm/gtx/norm.hpp>
enum class Phys_Mesh_Type
{
NONE,
CONVEX,
CUBE,
SPHERE,
CONE,
CYLINDER
};

enum class Interaction_Method
{
GHOST,
AREA,
STATIC,
DYNAMIC,
KINEMATIC
};

enum VAP_index :GLint
{
POS_AB,
VELO_AB,
CONNECTERZ
};

enum Buffer_type{
  POS_A,
  POS_B,
  VELOCITY_A,
  VELOCITY_B,
  CONNECTIONS
};


/*struct collision_shape
{

};*/

struct collision_enity{
glm::vec3 pos;
glm::vec3 normal;
bool is_null;
};



static inline  glm::vec3 prediction_fire_solution_at_t(float t, glm::vec3 start,float muzzle, glm::vec3 gravity)
{
 return gravity*(0.5f* t*t)+muzzle*t*start;
}

static glm::vec3 calc_fire_solution(glm::vec3 start, glm::vec3 end, float muzzle, glm::vec3 gravity)
{

  glm::vec3 final;
  glm::vec3 delta =  start -end;
  float a = glm::length2(gravity);
  float b = -4.f*(glm::dot(gravity,delta)+(muzzle*muzzle));
  float c = 4.f*glm::length2(delta);

  std::cout << "a::" << a<< "b::"<< b<< "c::"<<c <<'\n';

  float b2minus4ac = (b*b)-(4.f*a*c);

  std::cout<< "b2minu4ac::"<<b2minus4ac <<'\n';

    if(b2minus4ac<0)
      return final = glm::vec3(0.0f);

  float time0 = std::sqrt((-b+std::sqrt(b2minus4ac))/(2.f*a));
  float time1 = std::sqrt((-b-std::sqrt(b2minus4ac))/(2.f*a));

  float ttt;
  if(time0<0)
  {
    if(time1<0)
    return final = glm::vec3(0.0f);
    else {
      std::cout << "time1::"<<time1 <<'\n';
      ttt= time1;
    }
  }
  else if(time1<0)
  {
      std::cout << "time1::"<<time0 <<'\n';
      ttt=time0;
  }
  else {
    ttt= std::min(time0,time1);
    std::cout << "ttt::"<<ttt <<'\n';
  }
  final= (delta*2.f-(gravity*(ttt*ttt)))/(2.f*muzzle*ttt);
  return final;
}

static inline float random_binomial()
{
  return rand()%1-rand()%1;
}

struct goalz{

bool has_pos;
bool has_orientation;
bool has_velocity;
bool has_rotation;

glm::vec3 pos;
float orientation;
glm::vec3 velocity;
float rotation;

void update_channels(const goalz& other);
};


struct movement_statics
{
  glm::vec3 pos;
  float orientation;
};

struct steering_output {
  glm::vec3 linear;
  float angular;
};

struct kinematic {
movement_statics staticz;
glm::vec3 velocity;
float rotation;

float fix_new_orientation(float current, glm::vec3 velocity);
void update(steering_output in_streer, const float& time);
void update(steering_output in_streer, float max_speed, const float& time);

};

struct kinematic_steering_output
{
  glm::vec3 velocity;
  float rotation;
};

constexpr float TIMETO_TARGET_BASE = 0.25f;
constexpr float TIMETO_TARGET_VAR  = 0.1f;
constexpr float BASE_MAX_ACCEL = 7.f;
constexpr float BASE_MAX_SPEED = 7.f;
constexpr float BASE_TAREGET_RADIUS = 4.f;
constexpr float BASE_SLOWDOWN_RADIUS = 12.f;

struct kinematic_variable_behav
{
  kinematic agent;
  kinematic target;
  float max_acceleration;
  float max_speed;
  float target_radius;
  float slowdown_radius;

  kinematic_variable_behav (const kinematic& in_self) : max_acceleration{BASE_MAX_ACCEL},max_speed{BASE_MAX_SPEED},target_radius{BASE_TAREGET_RADIUS}, slowdown_radius{BASE_SLOWDOWN_RADIUS}
{
  agent = in_self;
}
  inline void set_target(const kinematic& in_target)
  {
    target= in_target;
  }

  steering_output get_steering_align(float acceleration = 0);
  steering_output get_steering_seek(float acceleration = 0);
  steering_output get_steering_flee(float acceleration = 0);
  steering_output get_steering_arrive(float speed = 0);

};


struct kinematic_base_behav{
  movement_statics agent;
  movement_statics target;
  float maxspeed;
  float arrival_radius;
  float max_rotation;

  float fix_new_orientation(float current, glm::vec3 velocity);
  kinematic_steering_output get_steering_flee(float speed = 0);
  kinematic_steering_output get_steering_seek(float speed = 0);
  kinematic_steering_output get_steering_arrive(float speed = 0);
  kinematic_steering_output get_steering_wonder(float speed = 0);


};




struct material_phys
{
Interaction_Method im_type =  Interaction_Method::DYNAMIC;
float mass =1.00f;
float restitution =0.5f;
float linear_damping =0.1f;
float angular_damping = 0.1f;
float friction= 0.2f;
float rolling_friction =0.2f;
float margin =0.01f;

void set_paramz(Interaction_Method in_type,std::array<float,7> in_valz);
};


struct collision_mesh
{
unsigned int num_trianglez = 0;
unsigned int num_vertices =0;
const uint32_t* indices = nullptr;
size_t index_stride_triangles =0;
const float *positionz = nullptr;
size_t position_stride = 0;
float margin =0.1f;

};



/*

void check_angle(float angle, glm::vec3& out_direction,float& out_distance)
{
  glm::vec3 delta_pos = target- source;
  out_direction = convert_to_direction(delta_pos,angle);
  out_distance = distance_to_target(out_direction,source,target,muzzle);
}


glm::vec3 refine_targeting(glm::vec3 start, glm::vec3 end, float muzzle,glm::vec3 gravity, float margin)
{

}



#endif
float angle = asin(direction.y/direction.length());
if(distance>0)
{
maxBound = angle;
minBound = -M_PI/2;

}
*/
#endif
