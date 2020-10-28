 
#pragma once
#include <array>
#include "../basez/lib_lib_z.hpp"
enum class Phys_Mesh_Type
{
NONE,
CONVEX,
CUBE,
SPHERE,
CONE,
CYLINDER
}

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


struct material_phys
{
Interaction_Method im_type =  Interaction_Method::DYNAMIC;
float mass 1.00f;
float restitution =0.5f;
float linear_damping =0.1f;
float angular_damping = 0.1f;
float friction= 0.2f;
float rolling_friction =0.2f;
float margin =0.01f;

set_paramz(Interaction_Method in_type,std::array<float,7> in_valz)
{ im_type = in_type;
  mass  = in_valz[0];
  restitution= in_valz[1];
  linear_damping  = in_valz[2];
  angular_damping= in_valz[3];
  friction  = in_valz[4];
  rolling_friction  = in_valz[5];
  margin  = in_valz[6];
}
};


struct collision_mesh
{
unsigned int num_trianglez = 0;
unsigned int num_vertices =0
const uint32_t* indices = nullptr;
size_t index_stride_triangles =0;
const float *positionz = nullptr;
size_t position_stride = 0;

float margin =0.1f;


};
