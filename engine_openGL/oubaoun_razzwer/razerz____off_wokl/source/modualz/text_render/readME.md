### to compile:

if your on linux, you can run the cmake file! to its likely ABIT specific at the moment particularity
 around freetype soo, you MAY have to change it manually if you have it in a different location.

NOTE its recommended you use cmake in Build folder. (make it if you dont get one.
  the EXECUTABLE final binary builds in the same directory as this README.
  the text_render folder. as it needs to find, the paths to shaders etc form there WILL fix this but as its a unit test.


g++ -std=c++17  -Wall -Wextra   p_test.cpp text_render.cpp ../basez/3rdparty/sb7ktx.cpp ../basez/opengl_utilityz.cpp  ../basez/shader_parser.cpp -lSDL2_image -lGL -lglut -lGLEW -lglfw3 -pthread -ldl -lGLU -lGL -lrt -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lassimp -I/usr/include/freetype2  -L/usr/local/lib -lfreetype


#### text_render_gui
utilizes and loads freetype fonts

#### text_overlay
uses ktx and the sb7 loader
note can use toktx to make ktx for the overlayfonter.
