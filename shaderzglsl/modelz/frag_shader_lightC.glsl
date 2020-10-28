#version 450 core

struct Phong_reflection
{
  //ambient light
  vec4 ambient;
  vec4 spot_cone_drection;

//directiona light
  float drectional_srength;

//Point light
float const_attenuation;
float quadr_attenuation;
float linear_attenuation;

//spot light

  float spot_cos_cutoff;
  float spot_exponent;

  //
  float gamma_c;
};

struct light_propertyz
{
  vec4 intensity;
  vec4 position;


  bool is_enabled;
  Phong_reflection phong_light;
  int  Light_type;
};

struct Meterialz
{
  vec3 emission;
  vec3 ambient_reflect;
  vec3 diffuse_reflect;
  vec3 specular_reflect;
  float shininess;
  float alpha;

  bool is_normalmap;
  bool is_hightmap;

  float hight_scale;
  //sampler2D diffuse_texture;
  //sampler2D spekular_texture;

};

const int MAX_Lightz = 5;

out vec4 Frag_colour;

in VERTEX_SHADR_OUT
{
   vec2 frag_uv;
   vec3 frag_normal;
   vec4 frag_pos;
   vec3 vertx_lenz_VM;

   vec3 frag_pos_TBN;
   vec3 frag_view_TBN;
   mat3 frag_TBN_matrix;
} in_frag;


uniform Meterialz meterial;

uniform sampler2D active_texture_sampler;
uniform sampler2D normal_mapSampler;
uniform sampler2D parallax_mapSample;

layout (binding = 0,std430) buffer light_blockz2
{
  light_propertyz light;
};

struct stoge_buf_test
{
  bool is_enabled;
  vec3 ambent_test;
};
layout (binding = 1,std430) buffer test_storage
{
  stoge_buf_test test_amb;
};

vec3 calculate_specular(vec3 vk_normz,vec4 vk_pos,light_propertyz light ,Meterialz material)
{
  vec3 light_to_loc   = normalize(vk_pos.xyz-light.position.xyz);
  vec3 reflect_drect  = normalize(reflect(light_to_loc,normalize(vk_normz)));
  vec3 pos_toview_dirc= normalize(in_frag.vertx_lenz_VM-vk_pos.xyz);
  float spek_angle    = max(0.0,dot(pos_toview_dirc,reflect_drect));
  vec3 spk_final      = material.specular_reflect*pow(spek_angle,material.shininess);
  return spk_final;
}

//parlaxstuff


vec2 parallex_mapping(vec2 texcoords, vec3 view_drec,Meterialz meterz)
{
  const float pmin_layer = 8;
  const float pmax_layer = 32;
  float num_layers = mix(pmax_layer,pmin_layer,abs(dot(vec3(0.0,0.0,1.0),view_drec)));

  float layer_depth = 1.0/num_layers;
  float current_layer_depth = 0.0;

  vec2 p = view_drec.xy/view_drec.z*meterz.hight_scale;
  vec2 delta_texcord = p/num_layers;

  vec2  curr_textcoods = texcoords;
  float curr_depth_map_val = texture(parallax_mapSample,curr_textcoods).r;

//  while(current_layer_depth<curr_depth_map_val)
//  {
    curr_textcoods -=delta_texcord;
    curr_depth_map_val = texture(parallax_mapSample,curr_textcoods).r;
    current_layer_depth +=layer_depth;
//  }

  return curr_textcoods;
}


void main()
{
  vec3 active_normal;

  vec3 viewDir = normalize(in_frag.frag_view_TBN-in_frag.frag_pos_TBN);
  vec2 active_texcords =  in_frag.frag_uv;
  if(meterial.is_hightmap)
  {
    active_texcords = parallex_mapping(active_texcords,viewDir,meterial);
    if(active_texcords.x>1.0 ||active_texcords.y>1.0 || active_texcords.x<0.0 || active_texcords.y<0.0)
    discard;
  }

  if(meterial.is_normalmap)
  {
    active_normal = texture(normal_mapSampler,active_texcords).rgb;
    active_normal= normalize(active_normal*2.0-1.0);

  }
  else {
  active_normal =  in_frag.frag_normal;
}
  //vec3 ambient= vec3(0.13);
  vec3 scatterd = vec3(0.0);
  vec3 spektral_reflect = vec3(0.0);
  vec3 ambient= vec3(0.0);

  light_propertyz l_test;
  l_test.is_enabled= true;
  l_test.position=vec4 (10.1,1.1,10.1,0.0);
  l_test.intensity=vec4(0.9,0.9,0.9,1.0);

  l_test.Light_type=1;

  l_test.phong_light.ambient=vec4(0.2,0.2,0.3,1.0);
  l_test.phong_light.spot_cone_drection=vec4(1.0,10.1,0.5,1.0);

  //directiona light
  l_test.phong_light. drectional_srength=12;

  //Point light
  l_test.phong_light.const_attenuation=20;
  l_test.phong_light.quadr_attenuation=20;
  l_test.phong_light.linear_attenuation=20;

  //spot light

  l_test.phong_light.spot_cos_cutoff=0.91;
  l_test.phong_light.spot_exponent=0;



vec3 light_drection =   in_frag.frag_TBN_matrix*l_test.position.xyz;
light_drection = light_drection - in_frag.frag_pos.xyz;
float light_distance = length(light_drection);
light_drection = light_drection/light_distance;
vec3 ambent_test = light.phong_light.ambient.rgb;

float total_attenuation = 1.0/(l_test.phong_light.const_attenuation+
                               l_test.phong_light.linear_attenuation*light_distance+
                               l_test.phong_light.quadr_attenuation*light_distance*light_distance);
vec3 half_vec    = normalize(light_drection+in_frag.vertx_lenz_VM);

float diffz = max(0.0,dot(active_normal,light_drection));

float skplr;
if(diffz !=0.0)
{
 float skplr = max(0.0,dot(active_normal,half_vec));
 skplr = pow(skplr,meterial.shininess)*l_test.phong_light.drectional_srength;

 spektral_reflect += meterial.specular_reflect*skplr*l_test.intensity.xyz*total_attenuation;
 scatterd         += meterial.diffuse_reflect*diffz*l_test.intensity.xyz*total_attenuation;
}

//spot
float followspot_cos = dot(light_drection,-l_test.phong_light.spot_cone_drection.xyz);


if(followspot_cos<l_test.phong_light.spot_cos_cutoff)
{
  total_attenuation = 0.0;
}
total_attenuation =pow(followspot_cos,l_test.phong_light.spot_exponent);
total_attenuation =1/total_attenuation;
float defuziz = max(0.0,dot(active_normal,light_drection));

if(defuziz!=0)
{
  vec3 skklr = calculate_specular(active_normal,in_frag.frag_pos,l_test,meterial)*
               l_test.phong_light.drectional_srength;


  spektral_reflect += skklr*l_test.intensity.rgb*total_attenuation;
  scatterd         += meterial.diffuse_reflect*defuziz*l_test.intensity.rgb*total_attenuation;

}
  vec3 spek_cal  = calculate_specular(active_normal,in_frag.frag_pos,l_test,meterial);

  vec4  texture_colour = texture(active_texture_sampler, active_texcords);
  vec3  surface_to_light2 = normalize(l_test.position.xyz-in_frag.frag_pos.xyz);
  float diffuseCoefficient2 =max(0.0,dot(active_normal,surface_to_light2));

  scatterd += diffuseCoefficient2*l_test.intensity.rgb*meterial.diffuse_reflect;

  scatterd +=meterial.ambient_reflect*l_test.phong_light.ambient.rgb;
  spektral_reflect = spektral_reflect+spek_cal;
  vec3 result = min((texture_colour.rgb*scatterd)+spektral_reflect,vec3(1.0f));
//vec3 result = vec3(0.2,0.8,0.5);
  //vec3 result = min(texture_colour.rgb*scatterd,vec3(1.0f));//+spektral_reflect,vec3(1.0f));
  //Frag_colour = vec4(result,1.0f);
  Frag_colour = vec4(result,meterial.alpha);
}
