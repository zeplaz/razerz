
#version 430

layout (location = 0) in vec3 pos;

out gl_PerVertex{
    vec4 gl_Position;
};

uniform mat4 model;



void main()
{
  gl_Position = model*vec4(pos,1.0);
}
