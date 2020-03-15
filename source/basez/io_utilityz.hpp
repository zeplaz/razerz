
#ifndef RAZER_IO_UTILITYZ_HPP
#define RAZER_IO_UTILITYZ_HPP

#include "cpp_libz_base.hpp"
#include "mathII.hpp"

enum class File_Extention{

  FE_XML,
  FE_PNG,
  FE_BMP,
  FE_OJB,
  FE_PLY,
};

constexpr char ch_xml[] = "xml";
constexpr char ch_png[] = "png";
constexpr char ch_bmp[] = "bmp";
constexpr char ch_ojb[] = "ojb";
constexpr char ch_ply[] = "ply";

struct pathz {

  File_Extention extention;
  char* raw_path;
  char file_name[255] = {NULL};

  pathz(std::string& in_path)
  {
    raw_path= new char [in_path.length()+1];
    std::strcpy (raw_path, in_path.c_str());
    set_file_name(raw_path);
    set_extention(raw_path);
  }

  pathz(std::string in_path)
  {
    raw_path= new char [in_path.length()+1];
    std::strcpy (raw_path, in_path.c_str());
    set_file_name(raw_path);
    set_extention(raw_path);
  }

  ~pathz()
  {
    delete[] raw_path;
  }

  void output_display();
  private :
  void set_file_name(const char* in_path);
  void set_extention(const char* in_path);

};

#endif
