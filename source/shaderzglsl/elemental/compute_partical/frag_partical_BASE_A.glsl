#version 450 core

layout(location = 0) out vec4 frag_colour;

in float age_intensity;
in vec2 pos_intensity;


/*
float sin_intzx =  sin(pos_intensity.x);
float sin_intzy =  cos(pos_intensity.y)/pow(tan(pos_intensity.y),tan(pos_intensity.x));
vec4 col_age = mix(vec4(0.112,0.115,0.12,0.8),vec4(0.902,0.27,0.0,0.8),age_intensity);
//vec4 col_posx = mix(vec4(0.902,0.515,0.082,0.8),vec4(0.900,0.17,0.0,0.5),pos_intensity.x);
vec4 col_posy = mix(vec4(0.952,0.115,0.082,0.8),vec4(0.900,0.17,0.0,0.5),sin_intzx);
//vec4 col_pos =mix(col_posx,col_posy,0.5);
frag_colour = mix(col_age,col_posy,sin_intzy);
*/
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
