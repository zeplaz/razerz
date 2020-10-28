#version 450
//layout (location = 0) in vec4 vertex_pos_tex; //two vec2z

in vec2 texture_uv;

out vec4 frag_colour;

uniform sampler2D utext_samp;
uniform vec4 ucolour;


void main (){
  vec4 text_samp =vec4(1.0,1.0,1.0,texture(utext_samp,texture_uv).r);
  frag_colour = (ucolour)*text_samp;
}
//layout(location = 0)  attr_text_texture;
