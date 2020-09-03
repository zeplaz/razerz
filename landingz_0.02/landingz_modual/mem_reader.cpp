

// /PAGE_READWRITE

#include "mem_reader.hpp"
#include <iostream>
#include <memory.h>


void mem_reader::create_shard_memory()
{
  memoryName_BUILDZ_DES = L"Buildz_Des_Name";
  m_shmHandler_BD = OpenFileMapping(FILE_MAP_READ, FALSE, memoryName_BUILDZ_DES.c_str());
  if (!m_shmHandler_BD) {
   m_shmHandler_BD = CreateFileMapping(
     INVALID_HANDLE_VALUE,
     NULL,
     PAGE_READONLY,
     0,
     MAX_BUFF_SIZE,
     memoryName_BUILDZ_DES.c_str());
  }
  
  memoryName_NOTICE = L"Notice_Name";
  m_shmHandler_NOTE = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, memoryName_NOTICE.c_str());
  if (!m_shmHandler_NOTE) {
   m_shmHandler_NOTE = CreateFileMapping(
     INVALID_HANDLE_VALUE,
     NULL,
     PAGE_READONLY,
     0,
     MAX_BUFF_SIZE,
     memoryName_NOTICE.c_str());

 }


}

void mem_reader::close(Named_Mem_Stream in_name)
{
    switch(in_name)
    {
      case Named_Mem_Stream::NOTICE_FILESTREAM :
      {
        CloseHandle(m_shmHandler_NOTE);
        break;
      } 

      case Named_Mem_Stream::BUILDINGZ_DEZ_FILESTREAM:
      {
        CloseHandle(m_shmHandler_BD);
        break;
      }

      default :
      {
        std::cerr <<"##ERROR:: named mem stream name not regozied...\n";
      }

    }
  
}


int mem_reader::read_test()
{
        /*if(!m_shmHandler)
        {
          m_shmHandler = OpenFileMapping(,FALSE,memoryName_BUILDZ_DES);
        }*/
        errno_t err;
        auto mview_buffer = MapViewOfFile(m_shmHandler_BD, FILE_MAP_READ, 0, 0,0);

        std::string data[7];
        char datac[70];
        //CopyMemory(data, mview_buffer, mview_buffer.size());
        err =memcpy_s(datac,sizeof(datac), mview_buffer,70);
        UnmapViewOfFile(mview_buffer);  
        if(err)
        {
          std::cerr << "#ERRROR::memcpy_s faild hurray::<" << err << '\n';
          return err;
        }
        else 
        {
          std::cout << "dataread:::" << datac <<'\n';
        }
        return -1;
        
}
/*/try
  //  {
        //m_shmHandler = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, PAGE_READONLY, 0, MAX_BUFF_SIZE, L"Buildz_Des_Name");
        //

    //}
    /*catch(...)
    {
        return false;
    }*
    /
    UnmapViewOfFile();
    CloseHandle(m_shmHandler);
*/