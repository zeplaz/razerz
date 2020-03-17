

#include "io_utilityz.hpp"
void pathz::output_display()
{
  std::cout << "filename IZ::" << file_name<< '\n';
  std::cout << "drectory IZ::" << drectory_path <<'\n';
std::cout << "full IZ::" << full_path <<'\n';
  switch(extention)
  {
    case File_Extention::FE_XML :
    {
      std::cout << "XMLextention\n";
      break;
    }
    case File_Extention::FE_PNG :
    {
        std::cout << "PNGextention\n";
      break;
    }

    case File_Extention::FE_BMP :
    {
        std::cout << "BMPextention\n";
      break;
    }

    case File_Extention::FE_OJB :
    {
        std::cout << "OJBextention\n";
      break;
    }

    case File_Extention::FE_PLY :
    {
        std::cout << "PLYextention\n";
      break;
    }
  }
}

void  pathz::set_file_name(const char* in_path)
  {
    size_t path_size = strlen(in_path);
    char* temp_path =  const_cast<char*> (strrchr(in_path,'/'));
    size_t pos = temp_path-in_path+1;
    std::cout << "tepos::" << pos << '\n';
    std::cout << "tempath::" << temp_path << '\n';
    int j = 0;
    int i =pos;
  //  std::cout << "size::" << path_size-pos;
    file_name= new char [path_size-pos];
    drectory_path = new char[path_size];
    for(j; j< pos; j++)
    { //std::cout <<  in_path[j];
      drectory_path[j] += in_path[j];
    }
    j=0;

    for(i; i< path_size; i++)
    { std::cout <<  in_path[i];
      file_name[j] += in_path[i];
      j++;
    }
    std::cout << "##->filenameset\n";
  }
void  pathz::set_extention(const char* in_path)
{
    size_t path_size = strlen(in_path);
    char* tempext =  const_cast<char*> (strrchr(in_path,'.'));
    int pos = tempext-in_path+1;

    int j = 0;
    char temp_ext[255] ={NULL} ;
    for(size_t i =pos; i< path_size; i++)
    {
      temp_ext[j] += in_path[i];
      j++;
    }
  //  std::cout << "temp_ext::" << temp_ext << '\n';
      if(0==strcmp(temp_ext,ch_xml))
    {
      extention = File_Extention::FE_XML;
      return;
    }
    else if (0==strcmp(temp_ext,ch_png))
    {
      extention = File_Extention::FE_PNG;
      return;
    }
    else if (0==strcmp(temp_ext,ch_bmp))
    {
      extention = File_Extention::FE_BMP;
      return;
    }

    else if (0==strcmp(temp_ext,ch_ojb))
    {
      extention = File_Extention::FE_OJB;
      return;
    }

    else if (0==strcmp(temp_ext,ch_ply))
    {
      extention = File_Extention::FE_PLY;
      return;
    }
    delete [] temp_ext;
 }
