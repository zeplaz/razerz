#version 450 core
//#extension GL_ARB_separate_shader_objects : enable

#define WORKGROUP_SIZE 512
const int  PARTCL_UNI_BIDN_INDX = 1;
const int  PARTCL_U_VELOC_INDEX =2;
const int  PARTCL_POS_VOLOCITY_INDX = 3;
const int  PARTCL_U_POS_INDEX =4;
const int  PARTCL_U_ORGIN_INDEX =5;
//orginze intow two subrunties thus can batch commute calls.

const int MAX_ATTRACTORS = 24;

layout(local_size_x =WORKGROUP_SIZE) in;   //


layout(std140, set = 0, binding =0) uniform uniform_object
{
  vec4 orgin;
}ubo;

layout(std140,set = 0, binding =1) uniform attached_bock
{
  vec4 partc_attractor[MAX_ATTRACTORS];//xyz and w used as mass? why 64?
};

layout (set = 1, binding = 2,rgba32f) uniform imageBuffer pos_buffer;
layout (set = 1, binding = 3,rgba32f) uniform imageBuffer velocity_buffer;

//layout (std140,set = 1, binding = 2) buffer pos_buffer
//{
//  vec4 posb[];
//};
//layout (std140,set = 1, binding = 3) buffer velocity_buffer
//{
//  vec4 velo[];
//};



layout( push_constant ) uniform TimeState {
  float DeltaTime;
} PushConstant;


void main(void)
{
  vec4 val = imageLoad(velocity_buffer,int(gl_GlobalInvocationID.x));
  vec4 pos = imageLoad(pos_buffer,int(gl_GlobalInvocationID.x));
uint index = gl_GlobalInvocationID.x;

  //  vec4 val = velo[index];
   // vec4 pos = posb[index];

  int i;

  pos.xyz -= val.xyz*PushConstant.DeltaTime;
  pos.w   -= 0.0016*PushConstant.DeltaTime;

  if(pos.w<=0.0)
  {
    pos.xyz  = ubo.orgin.xyz;
    val.xyz *= 0.9;
    pos.w   += 3.0f;
  }

  for(i=0;i<24;i++)
  {
    vec3 dist = (partc_attractor[i].xyz-pos.xyz);
    //val.xyz =(PushConstant.DeltaTime*PushConstant.DeltaTime)*partc_attractor[i].w*normalize(dist)/(dot(dist,dist)*100.10);
    val.xyz +=(((PushConstant.DeltaTime*PushConstant.DeltaTime)*partc_attractor[i].w*10)*normalize(dist))/(dot(dist,dist)*500.0);
  }

  imageStore(pos_buffer,     int(gl_GlobalInvocationID.x), pos);
  imageStore(velocity_buffer,int(gl_GlobalInvocationID.x), val);

 // posb[index] = pos;
 // velo[index] = val;

}
