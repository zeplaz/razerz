//utiltiy_header.hpp

#ifndef UTILITY_HEADER_LANDINGZ_HPP
#define UTILITY_HEADER_LANDINGZ_HPP

#include <string>
#include <chrono>
#include <utility>
#include <type_traits>
#include <tuple>

namespace landingz
{ 
using namespace std::chrono;

 const int POLFILE_READ_SIZE = 200;
 typedef std::pair<int,int> Off_Lng_Pair;

  constexpr  Off_Lng_Pair DEF_OFFLNTH = std::make_pair(0,POLFILE_READ_SIZE);

  constexpr size_t MAX_UPDATE_FILES = 5;
  typedef std::pair<bool,high_resolution_clock::time_point> notice_data_pair;


const std::string DB_CTRLER = "mainland_db01";



enum MODE {
     READ_MODE,WRITE_MODE
};

enum class Handler_Modual {
DB_HANDLE,
MMF_HANDLE,
OPENGL_HANDLE
};


enum ERRORZ{
     FILE_OPEN_FAIL = 3,
     FILE_MAP_FAIL = 4,
     OUT_OF_RANGE = 5,
     DB_FAIL_OPEN_HANDLE = 6,
     DB_TABLE_UNKNOWN =7
};

enum Polling_Filez
{
  DB_NOTICE,
  SYM_NOTICE,
  OTHER_NOTICE
};

enum buffer_partz{
FILE_NAME,
HEADER,
DATA_BODY
};

enum bufz_size {
     HEADER_LINE_LENGTH =3,
     HEADER_OBJ_COUNT = 6
};

enum class Db_Tablez{
  BUILDINGZ_DESTOYED_TABLE,
  ZONEZ_SECTORZ_TABLE
};

enum Db_buildingz_destoryed_collumz{
  DB_BD_ID,
  DB_BD_NAME,
  DB_BD_POS_X,
  DB_BD_POS_Y,
  DB_BD_POS_Z,
  DB_BD_DATE,
  DB_BD_FK_ZONE
};

enum Db_zonez_sectorz_collumz{
  DB_ZS_ID,
  DB_ZS_NAME,
  DB_ZS_START_X,
  DB_ZS_START_Y,
  DB_ZS_HEIGHT,
  DB_ZS_WIDTH
};

constexpr const char* DB_UPDATE_NOTICE  = "mmfRO_in_db_notice";
constexpr const char* DB_IN_DATA = "mmfRO_in_data_notice";
//#define  DB_IN_MEMEORY = NULL;
constexpr const char* DB_IN_MEMEORY = nullptr;
constexpr const char* SYM_UPDATE_NOTICE = "mmfRO_in_sym_notice";
//char* OTHER_UPDATE_NOTICE =
constexpr const char* DB_UPDATE_SYM_DATA  = "mmfRO_out_data";
constexpr const char* LOG_LANDINGZCPP_FILE = "log_cpp_file.txt";

constexpr const char* HEADER_DATE_KEY = "Date::";
constexpr const char* HEADER_TITLE_KEY="##landingz_mod##";
constexpr const char* HEADER_VER_KEY = "V::";
constexpr const char* HEADER_LINE_NUM_KEY = "Lnum::";

constexpr const char* db_landingz_win = "C:\\Program Files (x86)\\Steam/steamapps\\common\\IL-2 Sturmovik Cliffs of Dover Blitz\\parts\\external\\landingz_db.db";
constexpr const char* db_landingz_linux  ="/media/ogb_zo/08A2715EA2715164/Program Files (x86)/Steam/steamapps/common/IL-2 Sturmovik Cliffs of Dover Blitz/parts/external/landingz_db.db";


constexpr const char* IN_UPDATE_NOTICE_WIN = "C:\\Program Files (x86)\\Steam/steamapps\\common\\IL-2 Sturmovik Cliffs of Dover Blitz\\parts\\external\\script_update_notice.dat";
constexpr const char* IN_UPDATE_NOTICE_LINUX  ="/media/ogb_zo/08A2715EA2715164/Program Files (x86)/Steam/steamapps/common/IL-2 Sturmovik Cliffs of Dover Blitz/parts/external/script_update_notice.dat";



}

#endif
