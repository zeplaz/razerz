#version 450 core
//VERTEX_TERRAIN
//flat

layout(location =0) in vec4 vertex_dis_cordantes;
layout (location = 1) in vec3 anormal;
//madeup a

out gl_PerVertex{
    vec4 gl_Position;
};

out VS_out{
  vec3 normalz;
  vec2 texcord;
}   vs_out;



/*layout(std140) uniform IN_uniform_block
{
  vec4 vertices[];
}*/

uniform mat3 normal_matrix;


void main(void)
{
  //IN_uniform_block.vertices;
  const int   inzta_divisor = 255;
  const int   half_inzta_divisor = 128;
  const float f_insta_divisor =256.0f;
  const int sqroot_divisor =16;
  const vec4 quad_vectices[] = vec4[](vec4(-0.5, 0.0, -0.5, 1.0),
                                      vec4( 0.5, 0.0, -0.5, 1.0),
                                      vec4(-0.5, 0.0, -0.5, 1.0),
                                      vec4( 0.5, 0.0,  0.5, 1.0));

  int x = gl_InstanceID & 63;
  int y = gl_InstanceID >>  6;

  vec2 offset = vec2(x,y)*vertex_dis_cordantes.a;

  vs_out.texcord=(quad_vectices[gl_VertexID].xz+ offset+ vec2(0.5)) / 64;
  gl_Position    = vertex_dis_cordantes.xyz*quad_vectices[gl_VertexID] + vec4(float(x-32), 0.0,
                                                   float(y-32), 0.0);

//////END OF NORMAL TERRIAN ADDIONSZ:

  vs_out.normalz     = normalize(normal_matrix*anormal);

}
