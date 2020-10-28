##milieu

### particals
some partical sims, compute and working on gemo2pass

### test-outputVideo
use opencv to output

#### current complie line jan24
g++ -std=c++17  -Wall -Wextra   test_envoz.cpp partical_env.cpp  ../basez/opengl_utilityz.cpp  ../basez/shader_parser.cpp ../MCP_cmd/shader_pipeline_CMD.cpp ../basez/3rdparty/frame_to_video.cpp -I/usr/local/include/opencv4  -lSDL2_image -lGL -lglut -lGLEW -lglfw3 -pthread -ldl -lGLU -lGL -lrt -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lassimp  -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_videoio
