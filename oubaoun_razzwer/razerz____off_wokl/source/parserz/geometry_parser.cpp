
#include "geometry_parser.hpp"

std::ostream & operator << (std::ostream &out, const mesh_vertex &c)
{
    out << "posxyz::" <<c.v_position.x  <<':' << c.v_position.y << ':' << c.v_position.z <<'\n'
        << "normzxyz::" << c.v_normal.x <<':'<< c.v_normal.y     <<':' << c.v_normal.z <<'\n'
        << "textcodez::"<< c.v_textcord.x << ':' << c.v_textcord.y << '\n' << '\n';

    return out;
  }
