

#include "graphicz/gl_ctlr.hpp"
#include "graphicz/shader_base.hpp"


class driver_gl
{


std::unordered_map<SHDtype_index,shader_landingz_base*> shader_map;





void landingz_build_shaders( int shade_unittype)
{

  swtich(shade_unittype)
  {
    CASE GLYPH_BASE :
    {
      if(shader_landingz_base* temp_shad = new shader_landingz_base())
      {


        temp_shad->contained_shaders = VERTEX_SHADER;
        temp_shad->contained_shaders |= FRAGMENT_SHADER;

      }
    }


  }





  SHD_GLYPH1_FRAG

}


};
