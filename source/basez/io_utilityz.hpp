
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

static unsigned char* stbi_image_loader(const  char* inpath,int*width, int* height, int * nrComponents, int in_n=0);
static void free_stbi_data(unsigned char* in_data);
static unsigned char* stbi_image_from_memory(const unsigned char *buffer, int len, int *x, int *y, int *channels_in_file, int desired_channels);

struct pathz {

  File_Extention extention;
  char* drectory_path;
  char* file_name;
  char* full_path;

  pathz() = default;

  /*pathz(const std::string& in_path)
  {
  //
    char* raw_path= new char [in_path.length()+1];
    std::strcpy (raw_path, in_path.c_str());
    set_file_name(raw_path);
    set_extention(raw_path);
    set_full_path();
    delete raw_path;
  }*/

   pathz(const std::string& in_path)
  {
  //
    char* raw_path= new char [in_path.length()+1];
    //constexpr auto raw_path =  {in_path.c_str()};//= new char [in_path.length()+1];
    std::strcpy (raw_path, in_path.c_str());
    set_file_name(raw_path);
    set_extention(raw_path);
    set_full_path();
  //  delete raw_path;
  }

   pathz(const char* in_path)
  {
    set_file_name(in_path);
    set_extention(in_path);
    set_full_path();
  }

  ~pathz()// = default
  {
    delete drectory_path;
    delete file_name;
    free(full_path);
}

  void output_display();


  void set_path(const std::string& in_path)
  {
  char* raw_path= new char [in_path.length()+1];

  //  std::strcpy (raw_path, in_path.c_str());
    set_file_name(raw_path);
    set_extention(raw_path);
    set_full_path();
    delete raw_path;
  }

  void set_path(const char* in_string)
  {
    set_file_name(in_string);
    set_extention(in_string);
    set_full_path();
  }

  private :
  void set_file_name(const char* in_path);
  void set_extention(const char* in_path);

   void set_full_path()
  {
    size_t sz =  strlen(drectory_path) + strlen(file_name);
    full_path = static_cast<char*>(calloc(sz,sizeof(char)));
    size_t i =0;

    for(i; i<strlen(drectory_path) ;i++)
    {
      full_path[i] =drectory_path[i];
        }
  size_t j=0;
    for(j; j<strlen(file_name) ;j++)
    {
      full_path[i] =file_name[j];
      i++;
    }
  }

};

#endif
