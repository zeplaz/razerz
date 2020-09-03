#version 450 core

layout (location = 0) in vec3 aipos; // the position variable has attribute position 0
layout (location = 1) in vec3 ainormal;
layout (location = 2) in vec2 aiuv;
layout (location = 3) in vec3 aiTangent;
layout (location = 4) in vec3 aiBitangent;

const int NUMLIGHTZ = 1;

struct Cal_boolz
{
  bool is_normalmap;
  bool is_hightmap;
  bool us_paralax;
};

out gl_PerVertex{
    vec4 gl_Position;
};

struct lightz_normalz
{
  vec3 TangentLightPos;
  vec3 TangentViewPos;
  vec3 TangentFragPos;
};
out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 uv;
    lightz_normalz[NUMLIGHTZ]
} vs_out;

uniform Cal_boolz;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model_proj_View;
uniform mat4 model;

uniform vec3 lightPos;
uniform vec3 viewPos;


void cal_normal_map(mat3 in_normalMatrix)
{

  vec3 T = normalize(in_normalMatrix * aTangent);
  vec3 N = normalize(in_normalMatrix * aNormal);
  T = normalize(T - dot(T, N) * N);
  vec3 B = cross(N, T);

  mat3 TBN = transpose(mat3(T, B, N));
 for(int i = 0; i < NUMLIGHTZ; i++)
  vs_out.TangentLightPos = TBN * lightPos;
  vs_out.TangentViewPos  = TBN * viewPos;
  vs_out.TangentFragPos  = TBN * vs_out.FragPos;
  }

void main()
{
    vs_out.FragPos = vec3(model*vec4(aipos,1.0);
    mat3 normalMatrix = transpose(inverse(mat3(model)));
      if(has_normal_map)
      {
        cal_normal_map(normalMatrix);
      }

    vs_out.uv = aiuv;
    vs_out.Normal = normalize(ainormal*normalMatrix);
    gl_Position = model_proj_View*vec4(aipos, 1.0);
}
