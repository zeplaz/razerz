#version 450 core

const int  PARTCL_UNI_BIDN_INDX = 3;
const int  PARTCL_U_VELOC_INDEX =4;
const int  PARTCL_U_POS_INDEX =5;
const int  PARTCL_U_ORGIN_INDEX =6;
//orginze intow two subrunties thus can batch commute calls.

const int MAX_PARTC_ATTACTOR = 24;

layout(std140,binding =PARTCL_UNI_BIDN_INDX) uniform attached_bock
{
  vec4 partc_attractor[MAX_PARTC_ATTACTOR];//xyz and w used as mass? why 64?
};

layout (local_size_x = 512) in;

layout (rgba32f, binding = PARTCL_U_VELOC_INDEX) uniform imageBuffer velocity_buffer;
layout (rgba32f, binding = PARTCL_U_POS_INDEX) uniform imageBuffer pos_buffer;

uniform float dt;
layout(location = PARTCL_U_ORGIN_INDEX) uniform vec4 orgin;


void main(void)
{
  vec4 val = imageLoad(velocity_buffer,int(gl_GlobalInvocationID.x));
  vec4 pos = imageLoad(pos_buffer,int(gl_GlobalInvocationID.x));

  int i;

  pos.xyz -= val.xyz*dt;
  pos.w   -= 0.0016*dt;

  if(pos.w<=0.0)
  {
    pos.xyz  = orgin.xyz;
    val.xyz *= 0.9;
    pos.w   += 3.0f;
  }

  for(i=0;i<24;i++)
  {
    vec3 dist = (partc_attractor[i].xyz-pos.xyz);
    //val.xyz =(dt*dt)*partc_attractor[i].w*normalize(dist)/(dot(dist,dist)*100.10);
    val.xyz +=(((dt*dt)*partc_attractor[i].w*10)*normalize(dist))/(dot(dist,dist)*500.0);
  }

  imageStore(pos_buffer,     int(gl_GlobalInvocationID.x), pos);
  imageStore(velocity_buffer,int(gl_GlobalInvocationID.x), val);
}
