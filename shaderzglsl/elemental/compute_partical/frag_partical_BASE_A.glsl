#version 450 core

layout(location = 0) out vec4 frag_colour;

const int MAX_CHANNELZ = 5;
layout(location = 1) in float age_intensity;
layout(location = 2) in vec2 pos_intensity;

 layout(binding = 1) uniform colour_plus
{
vec4  colour_channelz[MAX_CHANNELZ];
} colourplus;


layout(binding = 1) uniform unifrom_bool_block
{
    bool has_channelz;
} ubbo;


/*
float sin_intzx =  sin(pos_intensity.x);
float sin_intzy =  cos(pos_intensity.y)/pow(tan(pos_intensity.y),tan(pos_intensity.x));
vec4 col_age = mix(vec4(0.112,0.115,0.12,0.8),vec4(0.902,0.27,0.0,0.8),age_intensity);
//vec4 col_posx = mix(vec4(0.902,0.515,0.082,0.8),vec4(0.900,0.17,0.0,0.5),pos_intensity.x);
vec4 col_posy = mix(vec4(0.952,0.115,0.082,0.8),vec4(0.900,0.17,0.0,0.5),sin_intzx);
//vec4 col_pos =mix(col_posx,col_posy,0.5);
frag_colour = mix(col_age,col_posy,sin_intzy);
*/

float rub_indizy_cal(vec2 in_pos_intenzity)
{
float out_intz =  in_pos_intenzity.x*in_pos_intenzity.y;
return out_intz;

}

void main (void)
{

float sin_intzx =  sin(pos_intensity.x);
float sin_intzy =  cos(pos_intensity.y)/pow(tan(pos_intensity.y),tan(pos_intensity.x));
vec4 col_age = mix(vec4(0.112,0.115,0.12,0.8),vec4(0.902,0.27,0.0,0.8),age_intensity);
vec4 col_posx = mix(vec4(0.902,0.515,0.082,0.8),vec4(0.900,0.17,0.0,0.5),sin_intzy);
vec4 col_posy = mix(vec4(0.952,0.115,0.082,0.8),vec4(0.900,0.47,0.0,0.5),sin_intzy);
vec4 col_pos =mix(col_posx,col_posy,0.5);
frag_colour = mix(col_age,col_pos,0.5);

}
