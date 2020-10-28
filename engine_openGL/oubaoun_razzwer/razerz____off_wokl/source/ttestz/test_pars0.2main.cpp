
#include "../basez/opengl_utilityz.hpp"
//#include "../parserz/parserlib.hpp"
#include "../parserz/texture_parser.hpp"
//#include "../basez/io_utilityz.hpp"
#include "../MCP_cmd/écouterions_resourcer_CMD.hpp"
#include "../basez/3rdparty/subprocess.hpp"
//#include "../parserz/texture_parser.hpp"

//swtup
float delta_time = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//callbayckfunz
void process_input_glfw(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//callbackglbalvars
float lastX = MAIN_SCREEN_WIDTH / 2.0f;
float lastY = MAIN_SCREEN_HIGHT / 2.0f;
bool firstMouse = true;
bool is_cursor_captured = false;

//opencv capture to AVI globals
bool take_frame_video = false;
void (*vid_cap_callback)(GLFWwindow*,int,std::string);

//lenZ_screan
GLint frame_buf_width,frame_buf_hight;
//view_lenz* prim_lenz =nullptr;
//auto prt_set_pramz = std::mem_fn(&multiframe_capturer::set_paramz); (multiframe_capturer::set_paramz)



/*
* MAIN!
*/





//int gen_xmlparz(float in_verson,int utf);

int main(int argc, char* argv[])
{

  pathz def_texturelist_XML("../data_extrn/DEFUL_file_list_texture.png");
  def_texturelist_XML.output_display();
  texture_xml_parser txml_parz;
  std::string deful_text = "../data_extrn/DEFUL_file_list_texture.xml";
  txml_parz.header_read(deful_text);
//texture_xml_parser txml_pars;

  //std::string test="<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
  subprocess::popen ls_cmd("ls", {"-r"});
    //subprocess::popen bash_test_cmd("bash tesb.sh", {});
//  subprocess::popen cat_cmd("cat", {}, sort_cmd.stdin());
  std::vector<std::string> test_cmd;
  std::vector<std::string> test_cmd2;
  std::string line;
while (std::getline(ls_cmd.stdout(), line))
{
  test_cmd.push_back(line);
    //std::cout << line << std::endl;
}
 ls_cmd.close();
subprocess::popen bash_test_cmd("bash tesb.sh", {"-r"});
std::cout << "###bashline::";
//std::cout << bash_test_cmd.stdout().rdbuf() <<'\n';;
// << bash_test_cmd.stdout().rdbuf() <<'\n';

while (std::getline(bash_test_cmd.stdout(), line))
{
  test_cmd2.push_back(line);
    //std::cout << line << std::endl;
}

for(size_t i = 0; i<test_cmd2.size();i++)
{
  std::cout << "test_cmd2:" <<i << " line::" << test_cmd2.at(i) <<'\n';
}

for(size_t i = 0; i<test_cmd.size();i++)
{
  std::cout << "itemznum:" <<i << " line::" << test_cmd.at(i) <<'\n';
}



  //cat_cmd.stdin() << "a" << std::endl;
  //cat_cmd.stdin() << "b" << std::endl;
  //cat_cmd.stdin() << "c" << std::endl;
  //cat_cmd.close();

  //std::cout << sort_cmd.stdout().rdbuf();
/*

  std::regex razer_resource_header_pat{R"((?:<(Header_razar)>)(?:\n\s*)(?:<\?)(\w*)(?:\?>\n\s*)(\w*)(?:\n\s*<)(\w*)>(?:\n\s*)(\d))"};
  std::smatch string_matcher;
  //std::smatch submatch = matches.matches(samplefileheader,first_line_pat);
  std::regex sub_catrogy_pat{R"((?:<)(\w+)>\n\s+(\w+))"};

  std::cout <<"stuff::" << samplefileheader<<'\n';


  std::regex_search(samplefileheader,string_matcher,xml_header_pat);
  std::cout << "\n :::XMLLINE INFO::: \n numMatch::"<<string_matcher.size()<<'\n';

  //  for(size_t k=0;k<3;k++)




    std::regex_search(samplefileheader,string_matcher,razer_resource_header_pat);
    std::cout << "\n :::HEADER:::\n numMatch::"<<string_matcher.size()<<'\n';


        for(size_t i=0;i<string_matcher.size();i++)
        {

          std::cout << "headerinfo:"<<i <<"::" << string_matcher[i] <<'\n';
        }


      /*std::regex_search(samplefileheader,string_matcher,sub_catrogy_pat);
      std::cout << "numMatch::"<<string_matcher.size()<<'\n';

          for(size_t i=0;i<string_matcher.size();i++)
          {

            std::cout << "catgorpy:"<<i <<"::" << string_matcher[i] <<'\n';
          }

}

*/

//std::cout << samplefileheader << '\n';

/*std::cout << "machez1::"<< sub_match[1] <<'\n';
std::cout << "machez2::"<< sub_match[2] <<'\n';
std::cout << "machez3::"<< sub_match[3] <<'\n';
std::cout << "machez4::"<< sub_match[4] <<'\n';
std::cout << "machez5::"<< sub_match[5] <<'\n';

std::vector<std::string> temp_string_subcat;
std::cout <<"\n SUBcatogrystuff..\n";
std::copy(std::sregex_token_iterator(samplefileheader.begin(), samplefileheader.end(), sub_catrogy_pat, 1),
               std::sregex_token_iterator(),
               std::ostream_iterator<std::string>(std::cout, "\n"));

*/


    //std::cout <<  (*ri_h)[2]<<'\n';

//  if(!)
//  {std::cerr <<"**ERROR HEADER READ\n";}



std::cout <<"\n FINi sucessz\n";
//"<< errocode << "\n";
return 0;
}
//if((*ri_h)[1]=="xml") std::cout << "xml file found\n";


std::string samplefileheader= {R"(<?xml version="1.0" encoding="UTF-8"?>

<Header_razar>
  <?Resource?>
  SINGULAR
  <Artifact_count>
  1
  </Artifact_count>
<Header_razar/>

<texture_itemz>
  <SUB_TYPE>
  texture2d
  </SUB_TYPE>
  <NAME>
  anim01_texture0
  </NAME>
  <file_root>
  ../media/texturez/anim_texturez/
  </file_root>

  <gl_colour_components>
  inf_rgba
  </gl_colour_components>
  <gl_formate_pix>
  form_grba
  </gl_formate_pix>
  <gl_pixdata_type>
  datat_ubyte
  </gl_pixdata_type>

  <flagz>
    0b0000'0000
  </flagz>
</texture_itemz>)"};
