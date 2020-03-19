#version 450 core
//TESS_EVAL_TERRAIn
layout (quads, fractional_odd_spacing) in;

uniform sampler2D tex_displacement;

uniform mat4 model_view_matrix;
uniform mat4 proj_matrix;
uniform float displacemap_depth;

in gl_PerVertex
{
  vec4 gl_Position;


} gl_in[gl_MaxPatchVertices];

out gl_PerVertex {
  vec4 gl_Position;

};



in TCS_out
{
  vec2 texcord;
} tes_in[];

out TES_out
{
  vec2 texcord;
  vec3 world_coord;
  vec3 lenz_cordz;

}tes_out;


void main(void)
{
  vec2 texcord1 = mix(tes_in[0].texcord,tes_in[1].texcord,gl_TessCoord.x);
  vec2 texcord2 = mix(tes_in[2].texcord,tes_in[3].texcord,gl_TessCoord.x);

  vec2 texcord = mix(texcord2,texcord1,gl_TessCoord.y);

  vec4 p1 = mix(gl_in[0].gl_Position,gl_in[1].gl_Position,gl_TessCoord.x);
  vec4 p2 = mix(gl_in[2].gl_Position,gl_in[3].gl_Position,gl_TessCoord.x);
  vec4 p  = mix(p2,p1,gl_TessCoord.y);

  p.y += texture(tex_displacement,texcord).r * displacemap_depth;

  vec4 lenz_drec = model_view_matrix*p;

  tes_out.texcord = texcord;
  tes_out.world_coord = p.xyz;
  tes_out.lenz_cordz = lenz_drec.xyz;

  gl_Position = proj_matrix*lenz_drec;

}
