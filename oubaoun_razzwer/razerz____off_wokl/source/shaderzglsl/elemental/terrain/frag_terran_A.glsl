
#version 450 core

out vec4 out_colour;

layout (binding = 1) uniform sampler2D tex_colour;
//lighting?!?
uniform bool enable_fog = true;

uniform vec4 fog_colour = vec4(0.7, 0.8, 0.9, 0.0);
in TES_out{
vec2 texcord;
vec3 world_coord;
vec3 lenz_cordz;
} fs_in;

vec4 fog(vec4 c)
{
    float z = length(fs_in.lenz_cordz);

    float de = 0.025 * smoothstep(0.0, 6.0, 10.0 - fs_in.world_coord.y);
    float di = 0.045 * (smoothstep(0.0, 40.0, 20.0 - fs_in.world_coord.y));

    float extinction   = exp(-z * de);
    float inscattering = exp(-z * di);

    return c * extinction + fog_colour * (1.0 - inscattering);
}

void main(void)
{
  bool local_fog = false;
  vec4 landscape = texture(tex_colour, fs_in.texcord);
  //enable_fog = true;
  if (local_fog)
  {
      out_colour = fog(landscape);
  }
  else
  {
      out_colour = landscape;
  }
//out_colour = texture(tex_colour,fs_in.texcord); //*lighting

}
