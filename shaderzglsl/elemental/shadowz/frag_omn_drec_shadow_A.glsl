
#version 430 core
//frag shadoww..
in vec4 frag_pos;

layout (depth_any) out float gl_FragDepth;

uniform vec3 omn_depth_light
{
  _pos[];
}
uniform float far_plane;



void main()
{

  float  lightz_distace = length(frag_pos.xyz-omn_depth_light._pos[])

  lightz_distace =lightz_distace/far_plane;
  gl_FragDepth = lightz_distace;

}
