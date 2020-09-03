
#ifndef LANDINGZ_BASE_H
#define LANDINGZ_BASE_H


#include <sqlite3.h>

#include <iosfwd>
#include <variant>
#include <memory>
#include <unordered_map>

#include "utilityz_header_ldingz.hpp"

 ////lass path;

//using namespace landingz;

namespace landingz {


using db_row_variant = std::variant<building_db_data,zone_db_data,null_val>;
template<class> inline constexpr bool always_false_v = false;

class handler_base
{
  public: 
  std::string name_key;
  Handler_Modual hm_type; 
  virtual ~handler_base();
};

class handle_driver
{
  protected : 
  std::unordered_map<std::string,std::shared_ptr<handler_base>> halde_map;

public : 
int cycle();
void return_handle_ptr(std::string handl_key);
void registar_handle(std::string key_name, std::shared_ptr<handler_base> in_hanlder);

};

static int db_default_callback(void *data, int argc, char **argv, char **azColName);



/*struct base_db_tabe_data{
  int data_id; 
  Db_Tablez db_table;
  virtual ~base_db_tabe_data(){}
};*/

struct building_db_data 
{ 
  Db_Tablez db_table;

  int id;
  std::string name;
  double pos_x;
  double pos_y;
  double pos_z;
  int time;
  int fk_zone;

  building_db_data() : db_table(Db_Tablez::BUILDINGZ_DESTOYED_TABLE) {}

  bool operator == (building_db_data &rhs)
{
  return std::tie(id,name,pos_x,pos_y,pos_z,time,fk_zone) ==
         std::tie(rhs.id,rhs.name,rhs.pos_x,rhs.pos_y,rhs.pos_z,rhs.time,rhs.fk_zone);
}

  void swap(building_db_data& other)
  {
    std::swap(id,other.id);
    std::swap(name,other.name);
    std::swap(pos_x,other.pos_x);
    std::swap(pos_y,other.pos_y);
    std::swap(pos_x,other.pos_x);
    std::swap(pos_z,other.pos_z);
    std::swap(time,other.time);
    std::swap(fk_zone,other.fk_zone);
  }

  bool operator < (const building_db_data &rhs)
  {
    return std::tie(id,name,pos_x,pos_y,pos_z,time,fk_zone) <
          std::tie(rhs.id,rhs.name,rhs.pos_x,rhs.pos_y,rhs.pos_z,rhs.time,rhs.fk_zone);
  }
};

struct zone_db_data
{
  int id;
  std::string name;
  double start_x;
  double start_y;
  double height;
  double width; 

  bool operator == (zone_db_data &rhs)
  {
    return std::tie(id,name,start_x,start_y,height,width) ==
           std::tie(rhs.id,rhs.name,rhs.start_x, rhs.start_y,rhs.height,rhs.width);
  }

  void swap(zone_db_data& other)
  {
    std::swap(id,other.id);
    std::swap(name,other.name);
    std::swap(start_x,other.start_x);
    std::swap(start_y,other.start_y);
    std::swap(height,other.height);
    std::swap(width,other.width);
    //std::swap(fk_zone,other.fk_zone);
  }

  bool operator < (const zone_db_data &rhs)
  {
    return std::tie(id,name,start_x,start_y,height,width) ==
           std::tie(rhs.id,rhs.name,rhs.start_x, rhs.start_y,rhs.height,rhs.width);
  }
  
};

template <typename Func> struct scope_exit {
    explicit scope_exit(Func f) : f_{f} {}
    ~scope_exit() { f_(); }
private:
    Func f_;
};


struct sqlite3_deleter {
    void operator () (sqlite3* db) const { sqlite3_close(db); }
};

using sqlite3_handle = std::unique_ptr<sqlite3, sqlite3_deleter>;

struct null_val
  {
    void* null = nullptr;
  };

class db_handler : public handler_base
{
  protected :
  char *zErrMsg = 0;
  sqlite3* db_current;
 // sqlite3_handle sql_db_hande;
  int db_rc_status;
  
  public :

  auto open_sql_handle(char const* db_name)
{
    db_rc_status = sqlite3_open(db_name, &db_current);
    sqlite3_handle h{db_current};
    if (db_rc_status) h.reset();
    //sql_db_hande = std::move(h);
  return h;
   
}

  inline void update_db_table()
  {
     std::string TIME_SLECT = "SELECT strftime('%s','now')";
  }
 
  void gen_tablez(Db_Tablez table);

  bool open_db(const char* db_file);

  auto dump_table_data(Db_Tablez in_table) -> db_row_variant;

  bool insert_data_to_table(db_row_variant in_row);

};

}

/*
struct db_out_value
{
  template<typename T>
  operator T() const 
  {
    T converted_val;
    return 
  }
}*/

/*template<typename T>
T retieve_db_table(auto table)
{
  T out_type = table;
  return out_type;
}*/
#endif