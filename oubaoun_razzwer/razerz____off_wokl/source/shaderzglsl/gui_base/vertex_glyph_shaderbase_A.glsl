#version 450
layout (location = 0) in vec4 vertex_pos_tex; //two vec2z

out vec2 texture_uv;
out gl_PerVertex{
    vec4 gl_Position;

};
uniform mat4 proj;
void main()
{
   gl_Position = proj * vec4(vertex_pos_tex.xy, 0.0, 1.0);
   texture_uv = vertex_pos_tex.zw;
}
//layout(location = 0)  attr_text_texture;
