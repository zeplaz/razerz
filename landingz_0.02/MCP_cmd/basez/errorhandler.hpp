

//#ifndef DEBUG_01
#define DEBUG_01

#ifndef LANDINGZ_ERROR_HANDLER_HPP
#define LANDINGZ_ERROR_HANDLER_HPP


 enum Exit_Error_Code : int{

   PARSER_FAIL = -11,
   TEXTURE_FAIL = -12,
   SHADER_FAIL = -13,
   MAIN_FAIL = -14,
   ENGINE_FAILURE = -15,
   OPENGL_FAILCAUGHT = -16,
   FILE_FORMATE_ERROR = -17,
   MAPLOOKUP_FAIL = -18,
   SHADER_LINK_FAIL = -19,
   STBI_LOAD_FAIL = -20,
   OI_UTILITYZ_FAIL =-31
 };


 static std::string error_to_string(int in_error)
 {
   switch(in_error)
   {
     case PARSER_FAIL :
     return "PARSER_FAIL";

     case TEXTURE_FAIL:
     return "TEXTURE_FAIL";

     case SHADER_FAIL :
     return "SHADER_FAIL";

     case MAIN_FAIL :
     return "MAIN_FAIL";

     case ENGINE_FAILURE:
     return "ENGINE_FAILURE";

     case OPENGL_FAILCAUGHT:
     return "OPENGL_FAILCAUGHT";

     case FILE_FORMATE_ERROR:
     return "FILE_FORMATE_ERROR" ;

     case MAPLOOKUP_FAIL:
     return "MAPLOOKUP_FAIL";

     case SHADER_LINK_FAIL:
     return "SHADER_LINK_FAIL";

     case STBI_LOAD_FAIL:
     return "STBI_LOAD_FAIL";

     case OI_UTILITYZ_FAIL:
     return "OI_UTILITYZ_FAIL";

     default :
     return "UNKNOWN_ERROR";
   }
 }

 #endif
