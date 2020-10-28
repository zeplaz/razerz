#version 450 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 anormal;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 atangent;

out gl_PerVertex{
    vec4 gl_Position;
};

out VERTEX_SHADR_OUT
{
 vec2 frag_uv;
 vec3 frag_normal;
 vec4 frag_pos;
 vec3 vertx_lenz_VM;

//normalmapoutzz
 vec3 frag_pos_TBN;
 vec3 frag_view_TBN;
 mat3 frag_TBN_matrix;

 //vec4 cotrl_;
} out_vrx;


uniform mat4 model;
uniform mat4 model_view;
uniform mat4 model_proj_View;
uniform mat3 normal_matrix;

//uniform vec3 a_tangent;
//uniform vec3 a_bitangent;

void main()
{
   out_vrx.vertx_lenz_VM   = vec3(model_view*vec4(aPos,1.0f));
   out_vrx.frag_uv         = aUV;
   out_vrx.frag_normal     = normalize(normal_matrix*anormal);
   out_vrx.frag_pos        = model_view*vec4(aPos,1.0);

   //normalmapstuff
   mat3 model_vector = transpose(inverse(mat3(model)));
   vec3 Tange = normalize(model_vector*atangent);
   //ormalize(model_vector*abitanget);
   vec3 Norma = normalize(model_vector*anormal);
   vec3 Bitan = cross(Tange,Norma);
   mat3 TBN_matrix = transpose(mat3(Tange,Bitan,Norma));

    out_vrx.frag_pos_TBN = vec3(model*vec4(aPos,1.0));
    out_vrx.frag_pos_TBN=TBN_matrix*out_vrx.frag_pos_TBN;
    out_vrx.frag_view_TBN=TBN_matrix*out_vrx.vertx_lenz_VM;
    out_vrx.frag_TBN_matrix= TBN_matrix;
    gl_Position =model_proj_View*vec4(aPos,1.0);
   //out_vrx.cotrl_;
  }
