#version 450
//layout (location = 0) in vec4 vertex_pos_tex; //two vec2z

layout (location = 1) in vec2 texture_uv;

layout (location = 0) out vec4 frag_colour;

layout(binding=1)  uniform sampler2D utext_samp;
layout(binding=1)  uniform uniform_object 
{
  vec4 ucolour;
} ubo;

void main (){
  vec4 text_samp =vec4(1.0,1.0,1.0,texture(utext_samp,texture_uv).r);
  frag_colour = (ubo.ucolour)*text_samp;
}
//layout(location = 0)  attr_text_texture;
