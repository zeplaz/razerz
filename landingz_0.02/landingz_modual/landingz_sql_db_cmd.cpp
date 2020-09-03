
   // using namespace memory_mapped_file;


#include <iostream>

#include <stdio.h>
#include <string.h>

#include "sql_hardcode.hpp"
#include "landingz_sql_db_cmd.hpp"

//std::map<std::string, functionPointerType>
//db_handler
//using var_table_list = std::variant<building_db_data,zone_db_data>;
using namespace landingz;


static int db_default_callback(void *data, int argc, char **argv, char **col_names) {

  std::cout << "\nDBDEFLTCALLBACK::\n";
  for(int i = 0; i < argc; ++i)
   {
    std::cout << col_names[i] << " = " << (argv[i] ? argv[i] : "NULL") << '\n';
    std::cout << std::endl;
   }
  return 0;
}

bool db_handler::insert_data_to_table(const db_row_variant& in_row) const
  {

    #if defined(_WIN32)
      sqlite3_handle active_db = open_sql_handle(db_landingz_win);
    #else
      sqlite3_handle active_db = open_sql_handle(db_landingz_linux);
    #endif


     sqlite3_exec(active_db.get(),TEST_DB_DB_DATA,db_default_callback,0,&zErrMsg);
     if( db_rc_status != SQLITE_OK )
      {
        std::cerr << "ERRROR::SQL_FALURE" << zErrMsg << '\n';
        //  fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return false;
      }


            std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T,building_db_data>)
            {
              sqlite3_stmt* sql_statement;
              sqlite3_prepare_v2(active_db.get(),INSERT_BUILDIGN_D_ROW,-1,&sql_statement,nullptr);
              db_rc_status = sqlite3_exec(active_db.get(), "BEGIN TRANSACTION", 0, 0, 0 );

              db_rc_status = sqlite3_bind_int(sql_statement,1,in_row.id);
              db_rc_status = sqlite3_bind_text(sql_statement,2,in_row.name);
              db_rc_status = sqlite3_bind_double(sql_statement,3,in_row.pos_x);
              db_rc_status = sqlite3_bind_double(sql_statement,4,in_row.pos_y);
              db_rc_status = sqlite3_bind_double(sql_statement,5,in_row.pos_z);
              db_rc_status = sqlite3_bind_int(sql_statement,6,in_row.time);
              //need to preform lookup for zone....
              db_rc_status = sqlite3_bind_int(sql_statement,7,in_row.fk_zone);

              db_rc_status = sqlite3_exec( active_db.get(), "END TRANSACTION", 0, 0, &zErrMsg );   //  End the transaction.
              db_rc_status = sqlite3_finalize(sql_statement);

            }
           else if constexpr (std::is_same_v<T, zone_db_data>)
           {
              sqlite3_stmt* sql_statement;
              sqlite3_prepare_v2(active_db.get(),INSERT_BUILDIGN_D_ROW,-1,&sql_statement,nullptr);
              db_rc_status = sqlite3_exec(active_db.get(), "BEGIN TRANSACTION", 0, 0, 0 );

              db_rc_status = sqlite3_bind_int(sql_statement,1,in_row.id);
              db_rc_status = sqlite3_bind_text(sql_statement,2,in_row.name);
              db_rc_status = sqlite3_bind_double(sql_statement,3,in_row.start_x);
              db_rc_status = sqlite3_bind_double(sql_statement,4,in_row.start_y);
              db_rc_status = sqlite3_bind_double(sql_statement,5,in_row.height);
              db_rc_status = sqlite3_bind_int(sql_statement,6,in_row.width);

              db_rc_status = sqlite3_exec( active_db.get(), "END TRANSACTION", 0, 0, &zErrMsg );   //  End the transaction.
              db_rc_status = sqlite3_finalize(sql_statement);
           }
           else
                static_assert(always_false_v<T>, "##ERROR visitor row not regoized\n!");
            },in_row);

      return true;

  }

void db_handler::gen_tablez(Db_Tablez table)
  {

  #if defined(_WIN32)
    sqlite3_handle active_db = open_sql_handle(db_landingz_win);
  #else
    sqlite3_handle active_db = open_sql_handle(db_landingz_linux);
  #endif

    if(table == Db_Tablez::BUILDINGZ_DESTOYED_TABLE)
    {
     db_rc_status = sqlite3_exec(active_db.get(),CREATE_BUILDIN_D_TABLE,db_default_callback,0,&zErrMsg);

      if( db_rc_status != SQLITE_OK )
      {
        std::cerr << "ERRROR::SQL_FALURE" << zErrMsg << '\n';
        //  fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      }
    }

    if(table == Db_Tablez::ZONEZ_SECTORZ_TABLE)
    {


     db_rc_status = sqlite3_exec(active_db.get(),CREATE_ZONEZ_TABLE,db_default_callback,0,&zErrMsg);

      if( db_rc_status != SQLITE_OK )
      {
        std::cerr << "ERRROR::SQL_FALURE" << zErrMsg << '\n';
        //  fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      }
    }

}

auto db_handler::dump_table_data(Db_Tablez in_table) -> db_row_variant
{

  #if defined(_WIN32)
  sqlite3_handle active_db = open_sql_handle(db_landingz_win);
  #else
   sqlite3_handle active_db = open_sql_handle(db_landingz_linux);
  #endif

   if (!active_db)
        {
        std::cerr << "Can't open database: " << sqlite3_errmsg(active_db.get()) << '\n';
        exit(DB_FAIL_OPEN_HANDLE);
        }

    char* error_msg{};
    //scope_exit cleaner_upper{[&] { sqlite3_free(error_msg); }};
    sqlite3_free(error_msg);
    sqlite3_stmt* sql_prep_statment;
    char db_buffer[999];
    db_buffer[sizeof db_buffer - 1] = '\0';


    switch (in_table)
    {

    case Db_Tablez::BUILDINGZ_DESTOYED_TABLE :
    {
       building_db_data tem_out_bdat;
      std::cout << "\n#->Db_Tablez::BUILDINGZ_DESTOYED_TABLE SELECT *::\n";
      snprintf(
          db_buffer,
          sizeof db_buffer - 1,
          "SELECT * FROM Building_destoryed");

     //  std::cout << "#-->#DEBUBG::snprintf::" << "\n";
      sqlite3_prepare(active_db.get(), db_buffer, sizeof(db_buffer), &sql_prep_statment, NULL);
     // std::cout << "#-->#DEBUBG::sqlite3_prepare::" << "\n";

      bool done = false;

      int ret_code = 0;
      //std::cout << "#-->#DEBUBG::_prewhile::" << "\n";
      //ret_code = sqlite3_step(sql_prep_statment);
      //std::cout << "#-->#DEBUBG::prewhile::" << ret_code << " sql_row::"<< SQLITE_ROW <<'\n';
      while((ret_code = sqlite3_step(sql_prep_statment)) == SQLITE_ROW)
      {
        std::cout << "#-->#DEBUBG::inwile__read::" << ret_code << " sql_row::"<< SQLITE_ROW <<'\n';

        tem_out_bdat.id = sqlite3_column_int(sql_prep_statment,DB_BD_ID);
        tem_out_bdat.name =  reinterpret_cast<const char*>(sqlite3_column_text(sql_prep_statment,DB_BD_NAME));
        tem_out_bdat.pos_x = sqlite3_column_double(sql_prep_statment,DB_BD_POS_X);
        tem_out_bdat.pos_y = sqlite3_column_double(sql_prep_statment,DB_BD_POS_Y);
        tem_out_bdat.pos_z = sqlite3_column_double(sql_prep_statment,DB_BD_POS_Z);
        tem_out_bdat.time  = sqlite3_column_int(sql_prep_statment,DB_BD_DATE);
        tem_out_bdat.fk_zone  = sqlite3_column_int(sql_prep_statment,DB_BD_FK_ZONE);

         std::cout <<  sqlite3_column_int(sql_prep_statment,DB_BD_ID) << '\n';
         std::cout << reinterpret_cast<const char*>(sqlite3_column_text(sql_prep_statment,DB_BD_NAME))<< '\n';
         std::cout <<sqlite3_column_double(sql_prep_statment,DB_BD_POS_X)<< '\n';
         std::cout <<sqlite3_column_double(sql_prep_statment,DB_BD_POS_Y)<< '\n';
         std::cout << sqlite3_column_double(sql_prep_statment,DB_BD_POS_Z)<< '\n';
         std::cout << sqlite3_column_int(sql_prep_statment,DB_BD_DATE)<< '\n';
         std::cout << sqlite3_column_int(sql_prep_statment,DB_BD_FK_ZONE)<< '\n';
       }
       sqlite3_finalize(sql_prep_statment);
       return tem_out_bdat;
      break;
      }
      case Db_Tablez::ZONEZ_SECTORZ_TABLE :
      {
        zone_db_data temp_zone_data;

        std::cout << "\n#->Db_Tablez::Zonez_sectorz SELECT *::\n";
        snprintf(
            db_buffer,
            sizeof db_buffer - 1,
            "SELECT * FROM Zonez_sectorz");

        sqlite3_prepare(active_db.get(), db_buffer, sizeof(db_buffer), &sql_prep_statment, NULL);


        bool done = false;
        int ret_code = 0;
        while((ret_code = sqlite3_step(sql_prep_statment)) == SQLITE_ROW)
        {
          temp_zone_data.id = sqlite3_column_int(sql_prep_statment,DB_ZS_ID);
          temp_zone_data.name =  reinterpret_cast<const char*>(sqlite3_column_text(sql_prep_statment,DB_ZS_NAME));
          temp_zone_data.start_x = sqlite3_column_double(sql_prep_statment,DB_ZS_START_X);
          temp_zone_data.start_y = sqlite3_column_double(sql_prep_statment,DB_ZS_START_Y);
          temp_zone_data.height = sqlite3_column_double(sql_prep_statment,DB_ZS_HEIGHT);
          temp_zone_data.width  = sqlite3_column_int(sql_prep_statment,DB_ZS_WIDTH);
        }
        sqlite3_finalize(sql_prep_statment);
        return temp_zone_data;
      break;
      }
      default :
      {
        std::cerr << "ERROR table not found!::ECODE::"<< DB_TABLE_UNKNOWN <<'\n';
        exit(DB_TABLE_UNKNOWN);
        break;
      }

    }
   }
