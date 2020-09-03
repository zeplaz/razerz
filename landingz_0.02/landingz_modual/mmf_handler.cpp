//mmf_handler.cpp

 #include <fstream>
 #include <iostream>

#include <stdio.h>
#include <string.h>

 #include "3rd_party/tokenizer/tokenzer.h"
 #include "mmf_handler.hpp"

//mmf_handler
  int mmf_handler::checker(int mode)
   {
        if(mode = READ_MODE )
        {
             if (! read_file.is_open()) return FILE_OPEN_FAIL;
      // Check that the contents of the file has been mapped into memory.
              if (! read_file.data()) return FILE_MAP_FAIL;
        }

       else  if(mode = WRITE_MODE)
        {
              if (! write_file.is_open()) return FILE_OPEN_FAIL;
      // Check that the contents of the file has been mapped into memory.
              if (! write_file.data()) return FILE_MAP_FAIL;
        }
        return 0;
   }

  void mmf_handler::open_read(std::string in_path,Off_Lng_Pair in_olp)
   {
    int outcome;
    read_file.open(in_path.c_str(),false);
    map(in_olp.first, in_olp.second);

    outcome = checker(READ_MODE);
    if(outcome !=0)
      {
       std::cerr << "ERROR::: readmode fail to open or map" <<outcome;
      }
    }

  void mmf_handler::open_read(std::string in_path)
    {
     int outcome;
     read_file.open(in_path.c_str());

     outcome = checker(READ_MODE);
     if(outcome !=0)
       {
        std::cerr << "ERROR::: readmode fail to open or map" <<outcome;
       }
     }


     void mmf_handler::read_buildings_dez()
     {
       read_buildz_dez_file.open("");

     }





  void mmf_handler::poll_for_update(int pollfile, std::pair<int,int> offset_lenth_pair)
    {
          //size_t offset = 0;
          //  size_t  read_size =POLFILE_READ_SIZE;
            //char* in_raw_data = new char[offset_lenth_pair.second];
            if(pollfile==DB_NOTICE)
            {
                read_file.open(DB_UPDATE_NOTICE,false);
                read_file.map(offset_lenth_pair.first,offset_lenth_pair.second);
                std::string  in_raw_data(read_file.data());

               // polled_data poll_pars_data  = parse_update_data(in_raw_data);
            }

        }



  void mmf_handler::parse_update_data(std::string in_data)
{

  std::vector<std::string> tokens;

  for (auto i = strtok(data(str), "\n"); i != nullptr; i = strtok(nullptr, "\n"))
  {
    tokens.push_back(i);
  }
}



  void mmf_handler::parse_update_data(char* const in_data)
  {
    std::string header_parts[HEADER_OBJ_COUNT];
    std::string buffers_stringz[buffer_partz];

    std::string data_data;
    std::string title_data;
    std::string line_num_data;

    char* data_tokenz = strtok(in_data,"\n");

    std::vector<std::string> string_tokenz;

   while (data_tokenz != NULL)
    {
       string_tokenz.insert(data_tokenz);
       data_tokenz = strtok(NULL, "\n");
    }

     std::string temp_title;
     int data_date;
     int data_title;
     int data_nline;

     for(size_t i =0; i <HEADER_LINE_LENGTH; i++)
     {

       switch(string_tokenz.at(i).c_str())
       {
         case HEADER_TITLE_KEY :
         {
            temp_title  = (string_tokenz.at(i+1));
         break;
         }

          case  HEADER_DATE_KEY  :
         {
            data_date  =std::stoi(string_tokenz.at(i+1));
          break;
         }

          case HEADER_LINE_NUM_KEY :
         {
            data_nline = std::stoi(string_tokenz.at(i+1));
          break;
         }
       }//endswitch
     }//end for linelethed
    }


//polled data
  bool polled_data::return_flag_status(int file_to_check)
    {
        if(file_to_check>=MAX_UPDATE_FILES)
        {
          std::cerr << "ERROR FILE TO CHEK IS OUT OF RANGE!";
          exit(OUT_OF_RANGE);
        }

      notice_data_pair* temp_ndat = &update_noticez[file_to_check];

      if(temp_ndat->first = true)
      {
        return true;
      }
      return false;
    }

  high_resolution_clock::duration   polled_data::return_time_diffrental_for_flag(int file_to_check)
  {
      if(file_to_check>=MAX_UPDATE_FILES)
      {
        std::cerr << "ERROR FILE TO CHEK IS OUT OF RANGE!";
        exit(OUT_OF_RANGE);
      }
      notice_data_pair* temp_ndat = &update_noticez[file_to_check];
      return  temp_ndat->second- dispatch_time;

  }

  high_resolution_clock::time_point polled_data::return_flag_last_change(int file_to_check)
  {
    if(file_to_check>=MAX_UPDATE_FILES)
    {
      std::cerr << "ERROR FILE TO CHEK IS OUT OF RANGE!";
      exit(OUT_OF_RANGE);
    }
    notice_data_pair* temp_ndat = &update_noticez[file_to_check];

  }




 /* bool db_handler::open_db(const char* db_file)
  {
    if( nullptr= *db_file)
    {
        db_handle_status= sqlite3_open(&db_current);
    }
    else{
       db_handle_status= sqlite3_open(db_file,&db_current);
    }

    if( db_handle_status ) {
      std::cerr << "ERRROR::DB__db_id_handle_::" << sqlite3_errmsg(db_current)
                << "dbhandlezs::"<< db_handle_status << '\n';
    // fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
     return false;
  }
  else {
    std::cout << "DATABAZE_OPEND...\n";
    // fprintf(stdout, "Opened database successfully\n");
    return true;
  }

  std::cerr << "WEEERRRORRRO::SHOULD NOT BE HERE>>>DBHANDLER_OPEN\n\n";
  return false;
  }
*/
