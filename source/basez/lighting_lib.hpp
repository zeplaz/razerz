

#ifndef LIGHTING_LIB_HPP
#define LIGHTING_LIB_HPP

#include "gl_lib_z.hpp"
enum Emission_Parmz_pos
{
  EM_TYPE,
  BOOL_FLAGZ,
  COLOUR_ARRAYZ,
  EMODZ
};
//const GLenum draw_buffers[] = {GL_COLOR_ATTACHMENT4,GL_COLOR_ATTACHMENT2}
//layout(location = 1) out int materialID;//
glDrawBuffers(num_db,draw_buffers);

enum class  light_channelz{
  SPEKULAR,
  DIFFUSE,
  NORMAL,
  PARLAX,
  AMBIENT,
  SPOT,
  POINT,
  LAMPZ,
  OBIT_EMZ
};

 enum class Emission_structre{
  STATIC_SPOTLIGHT,
  ETOILE_EMISSION,
  LAMP,
  FLASH_LIGHT
};

class enum Defined_lamp_z
{
  SHORT_TABLE_A,
  LAMPPOST_A,
  LAMPOST_B,
  OFFIC_BANK,
  OFFICE_STANUP,
  SALT_LAMP_A,
  FLORESSENT,
  COLOUR_INCONDENET,
  CHRIZ_MASS_CHAIN
};

class enum Defined_buildingz_{
  ADMINSTRATIVE_OFFIC_COMPLEX,
  RESTAUNT,
  COLAPSED_RUNEZ,
  COMMITTEE_BANCH_LOWER_MAINLAND,
  COMMITTEE_BANCH_HILL,
  COMMITTEE_BANCH_ROAD_SIDE,
  COMMITTEE_BANCH_PATH_BEACH_SIDE,
  PATHWAY_OUTLANDING
};

class enum Defined_solestialz{
  UNREGISATRED,
  LUNA_1,
  IOE,
  AMDRMADA,
  EUROBA,
  SATDERN,
  NEBTURN,
  JUBITUR,
  SOL,
  VENUZ,
  MARZ,
  CENTAURI_A,
  CENTAURI_B,
  PROXIMA_CENTAURI_C,
  MEDITOTE,
  SHOOTING_STAR,
  ASSTRIOD,
  SUPERNOVA
};

constexpr int ESTLZ_MAX_BANDZ = 17;
constexpr size_t DFEFINED_EMISSIONS_MAX = 37;
constexpr int NUM_COLOUR_CHANNEL = 3;
constexpr int NUM_EMISSION_BOOLZ = 5;

typedef std::touple<Emission_meterialz_type,std::array<bool,NUM_EMISSION_BOOLZ>,std::array<glm::vec4,NUM_COLOUR_CHANNEL>,e_modiferz> emission_parmz_touple;

//typedef std::array<emission_parmz_touple,DFEFINED_EMISSIONS_MAX> Predefined_emissions_array;
//typedef std::array<emission_attrabutez,DFEFINED_EMISSIONS_MAX> Predefined_em_atrbute_arry;
//typedef std::unordered_map<std::string,emission_parmz_touple>

typedef std::multi_map<Defined_lamp_z,lampz*> def_lampz_multimap;
typedef std::multi_map<Defined_solestialz,orbital_emitter*> def_selestial_map;

//template<class map_type,class out_obj>
void* genreate_light_from_subtype(emission_parmz_touple in_pamz_tuple)
{

  switch(std::get<EM_TYPE>(in_pamz_tuple))
  {
    case Emission_structre::ETOILE_EMISSION :
    {
      etoilez* temp_obj = new etoilez();
    //  in_map.insert(temp_obj);
    return temp_obj;
      break;
    }

    case Emission_structre::STATIC_SPOTLIGHT :
    {
     orbital_emitter* temp_obj = new orbital_emitter();
    //  in_map.insert(temp_obj);
    return temp_obj;
      break;
    }

    case Emission_structre::LAMP :
    {
      lampz* temp_obj = new lampz();
    //  in_map.insert(temp_obj);
    return temp_obj;
      break;
    }
  }

}


struct e_modiferz{
  float a_constant;
  float a_linear;
  float a_quadratic;
  glm::vec4 cos_cut;
};

struct emission_attrabutez
{
  //imission flagz
  bool in_shadow_cal;
  bool has_pos;
  bool has_drection;
  bool has_b_physiz;
  bool is_static;
  bool is_spot;
  bool cos_double_ring;
  bool has_partical;
//emmisionc olour properties
  glm::vec4 c_ambiant;
  glm::vec4 c_deffuz;
  glm::vec4 c_spektral;

//emission anntuation,modiferz,pramz
  e_modiferz modiferz;

  emission_attrabutez(emission_parmz_touple in_ept)
  {
    std::vallarray<bool> emaboolz(std::get<BOOL_FLAGZ>(in_ept));
     in_shadow_cal=emaboolz[0];
     has_pos      =emaboolz[1];
     has_drection =emaboolz[2];
     has_b_physiz =emaboolz[3];
     is_static    =emaboolz[4];
     is_spot      =emaboolz[5];
  cos_double_ring =emaboolz[6];
     has_partical =emaboolz[7];

//     std::array<glm::vec3,NUM_COLOUR_CHANNEL>  =
     c_ambiant=std::get<COLOUR_ARRAYZ>(in_ept)[0];
     c_deffuz=std::get<COLOUR_ARRAYZ>(in_ept)[1];
     c_spektral=std::get<COLOUR_ARRAYZ>(in_ept)[2];
     modiferz =std::get<EMODZ>(in_ept);
  }
};
//spotlight gets drection front camra, pos camra possition... for "flashligth??"
struct orbital_emitter
{
    bool active;
    glm::vec3 pos;
    double rad;

    double AU_distance_orgin;
//note velocity is dertbed by relahsip betiween AU and pierod amd its own radius, centrod recomeded.
    double peirod;
    emission_attrabutez emissionz;

};

struct etoilez :public orbital_emitter{

  double mass_wave;
  double luminosity;
  double rotational_vel;
  std::array[float,ESTLZ_MAX_BANDZ] frqz_banndz;

};

struct planetz : public orbital_emitter{

  double mass;
  double reflectivity;
  double rotational_vel;
//double AU_distance_center_mass;

  std::map<orbital_emitter*,double> illuminatorz_AU;
};

struct satellite : public orbital_emitter{

  double reflectivity;
  std::array[float,ESTLZ_MAX_BANDZ] frqz_banndz;
  std::array[double,MAX_DATA_CARTRAGEZ] inbeded_data;
  void* tranz_mit();
};


constexpr int INDOOR  = 2;
constexpr int OUTDOOR  = 4;
constexpr int HIEGHT_LOW = 8;
constexpr int HIEGHT_HIGH = 278;
constexpr int HIEGHT_MID_LOW =31;
constexpr int HIEGHT_MID_MID = 100;
constexpr int HIEGHT_MID_HI = 200;

//INDOOR|OUTDOOR //HIEGHT//BULB_COUNT
typedef std::array<int,3>  lamp_desgin;
constexpr lamp_desgin tri_desklamp = {INDOOR,HIEGHT_MID_LOW,3};
constexpr lamp_desgin bank_lmp = {INDOOR,HIEGHT_LOW,1};
constexpr lamp_desgin st_lamp_doux_noir {OUTDOOR,HIEGHT_MID_HI,2};
constexpr lamp_design st_lamp_monument_white{OUTDOOR,HIEGHT_HIGH,1};

struct lampz{
  bool active;

  lamp_desgin lamp_mode;
  glm::vec3 pos;
  float rad;
  emission_attrabutez local_attr;
};

struct light_setz{
  //std::<bt>
  void return_active_set();

};
/*
struct binary_etiolez{
    double peirod;
    std::array<etoilez,2> ab_starz;
};*/

#endif
/*
/*glm::vec3 pointLightPositions[]{

}*/
/*
//α_CENTAURI_C::Proxima Centauri//Class M
//Proxima Centauri b
// common centre with an orbital period of 79.91 years.[
//35.6 AU -11.2 AU}
//.24 light-years (1.30 pc),
//AU::13,000
CENTAURI_A,
Mass	1.100[7] M☉
Radius	1.2234±0.0053[8] R☉
Luminosity	1.519[7] L☉
Surface gravity (log g)	4.30[9] cgs
Rotational velocity (v sin i)	2.7±0.7[10] km/s
// α_CENTAURI_A::Rigil Kentaurus//1.1mass/ 1.519 times the luminosity/Class G//Radius	1.2234±0.0053[8] R
/*

Alpha Centauri B
Mass	0.907[7] M☉
Radius	0.8632±0.0037[8] R☉
Luminosity	0.5002[7] L☉
Surface gravity (log g)	4.37[9] cgs
Rotational velocity (v sin i)	1.1±0.8[12] km/s
//α_CENTAURI_B::Toliman/K//0.907 / 0.445 times its luminosity./Period (P)79.91±0.011 y
//
Period (P)	79.91±0.011 yr
Inclination (i)	79.205±0.041°

colourzz
A
Spectral type 	G2V[3]
U−B colour index 	+0.24[2]
B−V colour index 	+0.71[2]
B
Spectral type 	K1V[3]
U−B colour index 	+0.68[2]
B−V colour index 	+0.88[2]
*/
