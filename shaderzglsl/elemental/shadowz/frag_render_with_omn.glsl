#version 430 core


out frag_colour;

in VS_OUT{
  vec3 frag_pos;
  vec3 normal;
  vec2 t_cord;

} fs_in;

//uniform sampler2D diffuse_tex;

uniform samplerCube cube_depthmap;

uniform vec3 light_pos[];

uniform vec3 view_pos;

uniform float far_plane;

const int DISK_SAMPZ =20;

// array of offset direction for sampling
vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1),
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float  shadow_cal(vec3 frag_pos)
{
  vec3 frag_tolight = frag_pos -light_pos;
  float current_depth = length(frag_tolight);
  float bais = 0.05;

  //diskmethod#define
  float shadow =0.0;
  int d_samples = DISK_SAMPZ;
  float viewDistance = length(view_pos - frag_pos);
  float disk_rad = (1.0+(viewDistance/far_plane))/25.0;
  for(int i =0 i< d_samples; ++i)
  {

  }
  shadow /= float(d_samples);

//PCF#define
float pcf_samplez = 2.0;
float offset =0.1;

 for(float x = -offset; x < offset; x += offset / (pcf_samplez))
   {
     for(float y = -offset; y < offset; y += offset / (pcf_samplez))
      {
       for(float z = -offset; z < offset; z += offset / (pcf_samplez))
           {
            float closestDepth = texture(cube_depthmap, frag_tolight + vec3(x, y, z)).r; // use lightdir to lookup cubemap
             closestDepth *= far_plane;   // Undo mapping [0;1]
             if(current_depth - bias > closestDepth)
                shadow += 1.0;
           }
           }
    }
    pcf_samplez *=2.0;
shadow /=pcf_samplez*pcf_samplez*pcf_samplez;
  //float closest_depth = texture(cube_depthmap,frag_tolight),r;
//  closest_depth *= far_plane;
//  float shadow = current_depth - bais> closest_depth? 1.0 : 0.0;

  // if debug#define#define
  //frag_colour=vec4(vec3(closest_depth / far_plane), 1.0);
  return shadow;
}
