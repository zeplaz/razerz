#ifndef MEMORY_READER_H
#define MEMORY_READER_H

#include <tchar.h>
#include <windows.h>
#include <string>
#include <array>
constexpr size_t MAX_BUFF_SIZE = 20000;

enum class Named_Mem_Stream{
NOTICE_FILESTREAM,
BUILDINGZ_DEZ_FILESTREAM
};


enum Head_Pos{
  H_POS_NAME_KEY,
  H_POS_NAME_DATA,
  H_POS_LINE_NUM_KEY,
  H_POS_LINE_NUM_DATA,
  H_POS_DATE_KEY,
  H_POS_DATE_DATA,
  H_POS_HDATA_SIZE

};
class mem_reader
{

protected :
  std::wstring memoryName_BUILDZ_DES;
  std::wstring memoryName_NOTICE;

  size_t m_memorySize = 0;
  HANDLE m_shmHandler_BD = 0;
  HANDLE m_shmHandler_NOTE = 0;

  LPCTSTR pBuf;

public :
  void create_shard_memory();
  int read_test();
  void close(Named_Mem_Stream);

};

class header_mmf{
    protected :

    std::string title_key;
    int title_data;
    std::string lnum_key;
    int lnum_data;
    std::string date_key;
    int64_t date_data;
    int head_size; 

    public : 
   inline  void populate(std::array<std::string,6> in_str_array)
    {
       title_key = in_str_array.at(H_POS_NAME_KEY);
       title_data= std::stoi(in_str_array.at(H_POS_NAME_DATA)); 
       lnum_key = in_str_array.at(H_POS_LINE_NUM_KEY);
       lnum_data= std::stoi(in_str_array.at(H_POS_LINE_NUM_DATA));
       date_key= in_str_array.at(H_POS_DATE_KEY);
       date_data= std::stoll(in_str_array.at(H_POS_DATE_DATA));
       head_size=std::stoi(in_str_array.at(H_POS_HDATA_SIZE));

    }
};


#endif