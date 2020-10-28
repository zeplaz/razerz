#version 450
layout (location = 0) in vec4 vertex_pos_tex; //two vec2z

layout (location = 1) out vec2 texture_uv;
out gl_PerVertex{
    vec4 gl_Position;

};
layout (binding = 0) uniform unform_object 
{
    mat4 proj;
} ubo;    
void main()
{
   gl_Position = ubo.proj * vec4(vertex_pos_tex.xy, 0.0, 1.0);
   texture_uv = vertex_pos_tex.zw;
}
//layout(location = 0)  attr_text_texture;
