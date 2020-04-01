
#pragma once

//inlcuded openglfilez
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp> // glm::mat4
#include <glm/ext.hpp> // perspective, translate, rotate

//local headerz

#include "mathII.hpp"
#include  "errorhandler.hpp"
#include "cpp_libz_base.hpp"
#include "io_utilityz.hpp"
//#include "rez_utility_lib.hpp"

/*
* file contains the headers need for opengl and glfw
* as well as most of the defines, enums, and other fixed consts.
*/

namespace globalz {
static float delta_time = 0.0f;	// time between current frame and last frame
static float lastFrame = 0.0f;
}

//macros
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

/*
*definez
*/

#define L_AMBIENT 1
#define L_DIFFUSE 2
#define L_SPEKLER 3
#define L_DRECTION 4
#define L_POINT 5
#define L_SPOT 6

/*
* BITMASK ENUMZ template work
*/
//setup bitmaskable veratic Enums
//note check better veratdic template oprator sharing
template<typename E>
constexpr auto to_integral(E e) -> typename std::underlying_type<E>::type
{
   return static_cast<typename std::underlying_type<E>::type>(e);
}


template<typename Enum>
struct EnableBitMaskOperators
{
      static const bool enable = false;
};

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator |(Enum lhs, Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<Enum> (
        static_cast<underlying>(lhs) |
        static_cast<underlying>(rhs)
    );
};

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type&
operator |=(Enum &org,Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return org =static_cast<Enum> (static_cast<underlying>(org) |  static_cast<underlying>(rhs));

};

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator ~(Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return  static_cast<Enum> (~static_cast<underlying>(rhs));
};

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator &(Enum lhs,Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return  static_cast<Enum> (static_cast<underlying>(lhs)& static_cast<underlying>(rhs));
};

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator &=(Enum &lhs, Enum rhs)
{
   using underlying = typename std::underlying_type<Enum>::type;

    lhs = static_cast<Enum> (
        static_cast<underlying>(lhs) &
        static_cast<underlying>(rhs)
    );
    return lhs;
};

/*
*ENUMZ  USILTZEING BITMASKz functionality
*NOTE: require the template<> to activate bitmask
*/


enum class shader_type : unsigned char {
     SHADER_NULL         = 0x00,
     COMPUTE_SHADER      = 0x02,
     VERTEX_SHADER       = 0x04,
     FRAGMENT_SHADER     = 0x08,
     TESS_CONTROL_SHADER = 0x10,
     TESS_EVAL_SHADER    = 0x20,
     GEOMETRY_SHADER     = 0x40,
     ALL_PIPE            = 0x80
};
template<>
struct EnableBitMaskOperators<shader_type>
{
    static const bool enable = true;
};


enum class M_Tex_Flag : unsigned char
{
  TEXTYR_NULL     = 0x00,
  TEXTYR_DEFFUSE  = 0x02,
  TEXTYR_NORMAL   = 0x04,
  TEXTYR_PARALLAX = 0x08
};


template<>
struct EnableBitMaskOperators<M_Tex_Flag>
{
    static const bool enable = true;
};

enum class M_Model_Flag : unsigned char
{
  MODEL_NULL      = 0x00,
  MODEL_UNIFORM   = 0x02,
  MODEL_V_BUFF    = 0x04,
  MODEL_USE_INDIC = 0x20,
  MODEL_HAS_NORM  = 0x40

};
template<>
struct EnableBitMaskOperators<M_Model_Flag>
{
    static const bool enable = true;
};



template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}


enum class Text_Update_Mask :unsigned char {
  UP_TEXT   = 0x02,
  UP_POS    = 0x04,
  UP_COLOUR = 0x08,
  UP_ALL    = 0x20,
  UP_SCALE  = 0x40,
  UP_NONE   = 0x80
};
template<>
struct EnableBitMaskOperators<Text_Update_Mask>
{
    static const bool enable = true;
};

/*
* class enum  and normal enumz listings.
*/

enum class Scene_Mesh_RDR{
  LIGHT_PROG01_SCENE01,
  BASIC_SHADER_SCENE01
};

enum class Scene_LIST
{
  SCENE_01
};

enum BindingIndex{
  VERTEX_BINDING =0,
  METIERAL_BINDING = 1
};


enum class Format {
    Format_Grayscale = 1, /**< one channel: grayscale */
    Format_GrayscaleAlpha = 2, /**< two channels: grayscale and alpha */
    Format_RGB = 3, /**< three channels: red, green, blue */
    Format_RGBA = 4, /**< four channels: red, green, blue, alpha */
    Format_RGBA8 = 5,
    Format_RGB8 =6
};

enum WP_obj_tuple_feture
{
  INDEX_NUM,PAIR_NAME,VERTEX_VEC_DATA, FACE_VEC_DATA
};

enum class Shader_Pipeline_Name : unsigned int
{
  PRIMARY_PIPELINE_A,
  TEXT_PIPELINE_A,
  GUI_PIPELINE_A,
  NON_TITLED

};
enum class Shader_Program : unsigned int
{
  RENDER_TEXT_GLYPH_A,
  RENDER_TEXT_OVERLAY_A,
  BASE_A,
  LIGHT_BASE_D,
  ANIMATION_BASE_A

};

enum SHDtype_index : uint8_t
{
  SHD_BASICA02_VERTEX     = 6,
  SHD_BASICA01_VERTEX     = 4,
  SHD_BASIC_FRAG          = 5,

  SHD_LIGHTA1_VERTEX      = 7,
  SHD_LIGHTA1_FRAG        = 8,

  SHD_ANIM_VERTEX         = 9,
  SHD_AMIN_FRAG           = 10,
  SHD_GLYPH1_VERTEX       = 11,
  SHD_GLYPH1_FRAG         = 12,

  SHD_PARTIC_A_COMPUTE    = 13,
  SHD_PARTIC_VIZ_VERTEX   = 14,
  SHD_PARTIC_VIZ_FRAG     = 15,

  SHD_PARTIC_B_SIM_VERTEX =16,
  SHD_PARTIC_B_SIM_FRAG   =17,
  SHD_PARTIC_B_GEO_VERTEX =18,
  SHD_PARTIC_B_GEO_FRAG   =19
};

enum Lighting : bool
{
  HAS_LIGHTS = true,
  NO_LIGHT = false
};

enum PLY_obj_tuple_feturez
{
  VERTEXZ3D,NORMALZ3D,TEXTUCORD2D
};

enum  WarpMode : GLint{
  CLAMP_E = GL_CLAMP_TO_EDGE,
  MIRROR = GL_MIRRORED_REPEAT,
  REPEAT = GL_REPEAT,
  CLAMP_B = GL_CLAMP_TO_BORDER
};

enum class Filter{
  LINEAR,
  NEAREST,
  MIPMAP

};

enum Poly_face : GLint {
  FRONT = GL_FRONT,
  FANDB = GL_FRONT_AND_BACK,
  BACK =  GL_BACK

};

enum class P_Render_STYZ : GLint  {
      WIREFRAME =GL_LINE,
      FILL = GL_FILL ,
      POINT = GL_POINTS
};


enum class Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

/*
##typedefz
*/
enum Shader_Touple_pos{
//  ST_INDEX = 0,
  ST_SHADER_TYPE=0,
  //ST_NAME=2,
  ST_FILEPATH=1
};

//target,internalformate,pixel data format,textture_type
typedef std::tuple<GLenum,GLint,GLenum,GLenum> teximage2d_parmz;
//,teximage2d_parmz,name,filepath,flagz
typedef std::tuple<teximage2d_parmz,std::string,std::string,unsigned char> texture_tupl;
//index,shader_type,name,filepath
typedef std::tuple<shader_type,pathz> shader_tupl;

//MAPS
typedef std::unordered_map<unsigned int,texture_tupl*> tt_map;
typedef std::unordered_map<unsigned int,shader_tupl*> st_map;

//other
typedef std::underlying_type<P_Render_STYZ>::type P_R_STYZ_utype;

typedef std::pair<int,std::string> diply_tx_pair;


/*
*CONSTANTZ
*/

const unsigned int MAX_JOINTZ = 100;

constexpr unsigned char ATTRBUT_DYNAMIC_DRAW{0b0000'0010};
constexpr unsigned char ATTRBUT_STATIC      {0b0000'0100};
constexpr unsigned char ATTRBUT_STREAM      {0b0000'1000};

constexpr unsigned char NULL_FLAG         {0b0000'0000};
constexpr unsigned char STATE_ACTIVE      {0b0000'0010};
constexpr unsigned char STATE_CULL        {0b0000'0100};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;
const float MAX_V_ANGLE = 88.0f;
