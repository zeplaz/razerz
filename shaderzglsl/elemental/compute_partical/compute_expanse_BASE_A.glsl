#version 450 core
//#extension GL_ARB_separate_shader_objects : enable

#define WORKGROUP_SIZE 512
const int  PARTCL_UNI_BIDN_INDX = 3;
//const int  PARTCL_U_VELOC_INDEX =4;
const int  PARTCL_POS_VOLOCITY_INDX = 4;
const int  PARTCL_U_POS_INDEX =5;
const int  PARTCL_U_ORGIN_INDEX =6;
//orginze intow two subrunties thus can batch commute calls.

const int MAX_PARTC_ATTACTOR = 24;



layout(local_size_x =WORKGROUP_SIZE, local_size_y = WORKGROUP_SIZE) in;   //


layout(std140,binding =PARTCL_UNI_BIDN_INDX) uniform attached_bock
{
  vec4 partc_attractor[MAX_PARTC_ATTACTOR];//xyz and w used as mass? why 64?
};

layout (set = 0, binding = PARTCL_POS_VOLOCITY_INDX,rgba32f) uniform imageBuffer velocity_buffer;

layout (set = 0, binding = PARTCL_U_VELOC_INDEX,rgba32f) uniform imageBuffer velocity_buffer;
layout (set = 0, binding = PARTCL_U_POS_INDEX, rgba32f)  uniform imageBuffer pos_buffer;

layout(binding =0) uniform uniform_object
{
  float dt;
}ubo;

layout( push_constant ) uniform TimeState {
  float DeltaTime;
} PushConstant;

//location = PARTCL_U_ORGIN_INDEX,
layout(binding = PARTCL_U_ORGIN_INDEX) uniform uniform_object_2 {
  vec4 orgin;
} ubo2;

void main(void)
{
  vec4 val = imageLoad(velocity_buffer,int(gl_GlobalInvocationID.x));
  vec4 pos = imageLoad(pos_buffer,int(gl_GlobalInvocationID.x));

  int i;

  pos.xyz -= val.xyz*ubo.dt;
  pos.w   -= 0.0016*ubo.dt;

  if(pos.w<=0.0)
  {
    pos.xyz  = ubo2.orgin.xyz;
    val.xyz *= 0.9;
    pos.w   += 3.0f;
  }

  for(i=0;i<24;i++)
  {
    vec3 dist = (partc_attractor[i].xyz-pos.xyz);
    //val.xyz =(ubo.dt*ubo.dt)*partc_attractor[i].w*normalize(dist)/(dot(dist,dist)*100.10);
    val.xyz +=(((ubo.dt*ubo.dt)*partc_attractor[i].w*10)*normalize(dist))/(dot(dist,dist)*500.0);
  }

  imageStore(pos_buffer,     int(gl_GlobalInvocationID.x), pos);
  imageStore(velocity_buffer,int(gl_GlobalInvocationID.x), val);
}
