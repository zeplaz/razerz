

#include "parserlib.hpp"
using namespace parser;
unsigned int parser::str2int_run(const char* str, int h = 0)
{
return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

unsigned int parser::index_pars(std::string& in_substring)
{
  std::string parsindx;
  std::string index_num = in_substring;
  for(size_t k = 0; k< index_num.size(); k++)
  {
    if(index_num[k]=='[')
    {

      for(int ki = 0; ki <index_num.size()-1; ki++)
      {
        if(index_num[k+ki+1] ==']')
        break;

        parsindx += index_num[k+ki+1];
      }
    }
  }

   unsigned int out_index = stoul(parsindx);
   return out_index;
}

void parser::parser_base::header_read(const pathz&  in_path)
  {
    std::cout << "\n ###PARSING::setup;\n";

    std::ifstream file(in_path.full_path);
    std::string line;

    std::getline(file,line);

    std::regex xml_line1_pat{R"((xml)\s(?:\w+)(?:=")+(\d+.\d+)(?:"\s)(\w+)(?:=")(\w{3})(?:-)(\d+))"};
    std::smatch string_matcher;
    std::regex_search(line,string_matcher,xml_line1_pat);

    size_t i=0;
    for(i=0;i<string_matcher.size();i++)
    {
      std::cout << "xmlinfo:"<<i <<"::" << string_matcher[i] <<'\n';
    }

    if(string_matcher[XML_POS]=="xml")
    {
      std::cout <<"\n|->xml file found!\n\n";

      parsed_file new_file;
      new_file.version = stof(string_matcher[XML_VERSION]);
      new_file.encodeing = stoi(string_matcher[XML_UTF]);

      std:: cout << "new xml verson::" << new_file.version << '\n'
                 <<"encodeing::" << new_file.encodeing << '\n';

      std::getline(file,line);

      std::size_t  dlmit_pos = line.find(',');

      if(dlmit_pos==std::string::npos)
      {
        std::cerr<< "ERROR second line does not cotain header lenght or termator\n";
        exit(FILE_FORMATE_ERROR);
      }
        std::cout << "->header line size is::" << line <<'\n'
                 <<  line.substr(0,dlmit_pos) << '\n';
      //  <<  line_two.substr(dlmit_pos+1)   << '\n';
      int header_size = stoi(line.substr(0,dlmit_pos));
      std::string filename = line.substr(dlmit_pos+1,std::string::npos);

        std::cout  << "->filename is::" << filename <<'\n' ;
        std::cout << "->header line size is::" << header_size << '\n' <<'\n';


        //.seekg(std::ios::cur,std::ios::end);
        std::string header_raw;
        for(i =0; i< header_size;i++)
        {
          std::getline(file,line);
          header_raw+=line;
        }
        std::cout << "-<>rawheader:::" << header_raw <<'\n';

        //std::regex razer_resource_header_pat{R"((?:<(Header_razar)>)(?:\n\s*)(?:<\?)(\w*)(?:\?>\n\s*)(\w*)(?:\n\s*<)(\w*)>(?:\n\s*)(\d))"};
        std::regex razer_resource_header_pat{R"((?:<Header_razar>)(?:\s*)(?:<\?)(\w*)(?:\?>\s*)(\w*)(?:\s*<\w*>)\s*(\d))"};

        std::regex_search(header_raw,string_matcher,razer_resource_header_pat);
        std::cout << "\n :::HEADER:::\n numMatch::"<<string_matcher.size()<<'\n';

        for(size_t i=0;i<string_matcher.size();i++)
        {
          std::cout << "headerinfo:"<<i <<"::" << string_matcher[i] <<'\n';
        }

        if(string_matcher[REZ_TYPE]== "TEXTURE_LIST")
        {
          std::cout << "TextureList detected!\n";
         new_file.pf_type    =Parse_File_Type::TEXTURE_LIST;
        }

        else if(string_matcher[REZ_TYPE]== "SHADER_LIST")
        {
         std::cout << "TextureList detected!\n";
         new_file.pf_type   =Parse_File_Type::SHADER_LIST;
        }

        file_map.insert(std::make_pair(in_path.file_name,new_file));
    }
  }


  std::vector<std::string> parser::run_xmlobj_parse(const pathz& in_xml_path)
  {
    //std::cout <<"\n#->running textture parser func\n";
    std::ifstream file_config(in_xml_path.full_path);
    std::string file_in_string;
    file_config.seekg(0, std::ios::end);
    file_in_string.reserve(file_config.tellg());
    file_config.seekg(0, std::ios::beg);
    file_in_string.assign((std::istreambuf_iterator<char>(file_config)),
                std::istreambuf_iterator<char>());

  //  std::regex rexal( R"#(\s*<\s*(\S+)\s*>\s*(\S+)\s*<\s*///\1\s*>\s*)#");
/*
    std::vector<std::string> substingz;
    const std::sregex_token_iterator end;
    std::vector<int> indexzr{1,2};

    for(std::sregex_token_iterator reg_iter (file_in_string.begin(), file_in_string.end(), rexal, indexzr);
        reg_iter!=end; ++reg_iter)
        {
          substingz.push_back(*reg_iter);
        }
    for(std::sregex_token_iterator reg_iter (substingz.at(1).begin(), substingz.at(1).end(), rexal, indexzr);
        reg_iter!=end; ++reg_iter)
        {
          substingz.push_back(*reg_iter);
        }
        return substingz;*/
  }


  int parser::parser_base::load_run(const pathz& in_pathxml)
  {

     std::vector<std::string> substingz = parser::run_xmlobj_parse(in_pathxml.full_path);

     std::cout <<"->###begin sort\n";
     unsigned int current_0jk_index;
      int i;
     for( i =0; i<substingz.size(); i++)
       {
        switch(str2int_run(substingz.at(i).c_str()))
         {
             case item_type :
             {
               i = item_selection(substingz,i);
             break;
             }
         }//endswitch
       }//endfor
       return i;
  }


/*extra*/
/*
case index :
  {
    current_0jk_index = index_pars(substingz.at(i),i);
    std::cout << "ttrawindex::"<< substingz.at(i+1) <<'\n';
    std::cout << "ttindexnum::"<< current_0jk_index <<'\n';
  break;
   }

std::vector<shader_tuple_type*>* return_ptr_shader_TV()
{
  return &shader_tuple_vec;
}*/
