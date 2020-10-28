
CXX=g++
CXXFLAGS = -Wall -g -std=c++17

LIBS = -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi -lxcb  -lglslang -lSPIRV  -lMachineIndependent -lOSDependent -lpthread -lGenericCodeGen -lOGLCompiler 

#ODIR = objz
LDIR = /libz

DEPS_FULLH = flag_templatez.hpp vulkan_definz.hpp vulkani_strucz.hpp

main: main.o vk_abstracionz.o vk_shaderz.o vulkan_api.o exrtn_vulkan.o
	$(CXX) $(CXXFLAGS) -o main main.o vk_abstracionz.o vk_shaderz.o vulkan_api.o exrtn_vulkan.o $(LIBS)

#_OBJ = main.o vk_base.o

BASE_DEPZ = exrtn_vulkan.hpp  vk_abstracionz.hpp 
#vk_base.o $(BASE_DEPZ) $(CXX) -c -o  $@ $< $(CFLAGS)
main.o: main.cpp vk_shaderz.hpp 
	$(CXX) $(CXXFLAGS) $(LIBS) -c main.cpp
exrtn_vulkan.o: $(BASE_DEPZ) exrtn_vulkan.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c exrtn_vulkan.cpp	
vk_abstracionz.o:  $(BASE_DEPZ) $(DEPS_FULLH) vk_abstracionz.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c vk_abstracionz.cpp
vk_shaderz.o: vk_shaderz.hpp $(DEPS_FULLH)  vk_shaderz.cpp 
	$(CXX) $(CXXFLAGS) $(LIBS) -c vk_shaderz.cpp
vulkan_api.o: vulkan_api.hpp  $(BASE_DEPZ) vulkan_api.cpp 
	$(CXX) $(CXXFLAGS) $(LIBS) -c  vulkan_api.cpp

binaries = vulkan_api.o vk_shaderz.o vk_abstracionz.o main.o exrtn_vulkan.o
all: clean $(binaries)

.PHONY: clean

clean:
	rm -f $(binaries) *.o
	echo Clean done