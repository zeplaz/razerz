CC=g++
INCLUDES=-I/usr/local/include/opencv4 -I/usr/include/freetype2 
LDFLAGS=-lglfw -lGL -lglut -lGLEW -pthread -ldl -lGLU -lGL -lrt -lXrandr -lXi -lXinerama -lX11  -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_videoio -lfreetype -ldl -lGLESv2 -lassimp
CXXFLAGS=-Wall -Wextra -std=c++17 $(INCLUDES)

all: orgprogz

orgprogz: bui_tstz2.o basez_lib.a modualz_lib.a parserz_lib.a mcp_lib.a
	$(CC) bui_tstz2.o -L. basez_lib.a modualz_lib.a parserz_lib.a mcp_lib.a $(LDFLAGS) -o orgprogz


basez_lib.a:
	$(CC) $(CXXFLAGS) -c -o opengl_utilityz.o ../basez/opengl_utilityz.cpp 
	$(CC) $(CXXFLAGS) -c -o shader_lib.o ../basez/shader_lib.cpp 
	$(CC) $(CXXFLAGS) -c -o frame_to_video.o ../basez/3rdparty/frame_to_video.cpp
	$(CC) $(CXXFLAGS) -c -o texture.o ../basez/texture.cpp  
	$(CC) $(CXXFLAGS) -c -o geometry.o ../modualz/geometry/geometry.cpp 
	ar rc basez_lib.a opengl_utilityz.o shader_lib.o frame_to_video.o texture.o geometry.o

modualz_lib.a: 
	$(CC) $(CXXFLAGS) -c -o ./partical_env.o ../modualz/milieu/partical_env.cpp 
	$(CC) $(CXXFLAGS) -c -o ./text_render.o ../modualz/text_render/text_render.cpp	       
	ar rc ./modualz_lib.a ./partical_env.o ./text_render.o  

parserz_lib.a: 
	$(CC) $(CXXFLAGS) -c -o ./geometry_parser.o ../parserz/geometry_parser.cpp 
	ar rc ./parserz_lib.a ./geometry_parser.o

mcp_lib.a:
	$(CC) $(CXXFLAGS) -c -o ./shader_pipeline_CMD.o ../MCP_cmd/shader_pipeline_CMD.cpp 
	ar rc ./mcp_lib.a ./shader_pipeline_CMD.o

clean:
	-@rm -rvf $(TARGET) ./*.o ./*.a


