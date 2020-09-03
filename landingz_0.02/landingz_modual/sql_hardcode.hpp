
#ifndef SQL_HARDCODE_LANDINGZ_HPP
#define SQL_HARDCODE_LANDINGZ_HPP

namespace landingz {
//hardcode sql move to like regual text file and have loader ddryz
        constexpr const char* CREATE_ZONEZ_TABLE
            = "CREATE TABLE IF NOT EXISTS Zonez_sectorz("\
              "ID      INTEGER NOT NULL PRIMARY KEY,"\
              "Name    TEXT NOT NULL,"\
              "Start_x DECIMAL(18,9) NULL,"\
              "Start_y DECIMAL(18,9) NULL,"\
              "Height  DECIMAL(18,9) NULL,"\
              "Width   DECIMAL(18,9) NULL);";

        constexpr const char* CREATE_BUILDIN_D_TABLE
            = "CREATE TABLE IF NOT EXISTS Building_destoryed("\
              "ID INTEGER NOT NULL PRIMARY KEY,"\
              "Name  TEXT NOT NULL,"\
              "Pos_x DECIMAL(18,9) NULL,"\
              "Pos_y DECIMAL(18,9) NULL,"\
              "Pos_z DECIMAL(18,9) NULL,"\
              "Date INTEGER NULL,"\
              "Fk_zonez_id INTEGER NULL,"\
              "FOREIGN KEY(Fk_zonez_id) REFERENCES Zonez_sectorz(ID));";


        constexpr const char* INSERT_BUILDIGN_D_ROW
         = "INSERT INTO Building_destoryed (ID, Name, Pos_x, Pos_y,"\
           "Pos_z, Date,Fk_zonez_id) VALUES (@ID, @Name, @Pos_x, @Pos_y, @Pos_z, @Date,@Fk_zonez_id);";

         constexpr const char* INSERT_ZONE_SECTOR_ROW
         = "INSERT INTO Zonez_sectorz (ID, Name, Start_x, Start_y,"\
           "Hieght, Width) VALUES (?, ?, ?, ?, ?,?);";

      constexpr const char* TEST_DB_DB_DATA = 
         R"(England\ Urban House 22, 214958.600006104, 235530.104000092, 44.0816955566406, (SELECT strftime('%s','now'));)";
    


    ///stl template models..
//make a key class.... better then using just string..can check for maxsize..hell fix array 14.
constexpr int MAX_KEY_SIZE = 14;

// ref key must be no more then 4 chars its a string.. that may just be the id, 

template<typename KIN,int  N= MAX_KEY_SIZE>
class ref_key{
std:: array<KIN,N>[0] = {};

std::string key;

public : 
ref_key()
{
  key.resize(MAX_KEY_SIZE);  
}

template<typename KIN>
void set_key(KIN key_in);

template<typename T,typename KIN>
KIN oprator()(T settype)
{
         using alais_kin =   decltype(settype);
         alais_kin
         for //

  return 
};

};

template<typename gtyp,typename returntype>
class 

    template<typename T, template<int,typename N>class row,typename ... tuplepak> 
    class sql_data_contaner
    {
     
      using tp_row = std::touple<tuplepak>;
      std::unorded_map<ref_key,tp_row> key_row_map;
      T get_row(int i);


    };
    
    }
      #endif