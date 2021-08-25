
CXX=g++
CXXFLAGS= -g -O0 -Wall -std=c++17
CXXFLAGS_D= -g -O0 -Wall -std=c++17

LIBS = -g -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi -lxcb  -lglslang  -lSPIRV -lSPVRemapper  -lSPIRV-Tools-opt -lSPIRV-Tools -lMachineIndependent -lOSDependent -lpthread -lGenericCodeGen -lOGLCompiler


OBJDIR := objz
SHADER_DIR := ../shaderzglsl
OBJS := $(addprefix $(OBJDIR)/,main.o vk_shaderz.o vulkan_api.o vk_abstracionz.o  exrtn_vulkan.o swap_chain.o render_linux.o partical_lib.o) 

VPATH = src: headers
GPATH = %.o OBJDIR
vpath %.hpp headers 
#_OBJ = main.o vk_base.o

vlkantest.out: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(OBJS) $(LIBS)  $(OUTPUT_OPTION) $< 

$(OBJDIR)/main.o: main.cpp 
	$(CXX) $(CXXFLAGS) $(LIBS) -c $(OUTPUT_OPTION) src/main.cpp
$(OBJDIR)/swap_chain.o: swap_chain.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c $(OUTPUT_OPTION) src/swap_chain.cpp 
$(OBJDIR)/exrtn_vulkan.o: exrtn_vulkan.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c $(OUTPUT_OPTION) src/exrtn_vulkan.cpp 
$(OBJDIR)/vk_abstracionz.o: vk_abstracionz.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c $(OUTPUT_OPTION) src/vk_abstracionz.cpp 
$(OBJDIR)/vk_shaderz.o: vk_shaderz.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c $(OUTPUT_OPTION) src/vk_shaderz.cpp
$(OBJDIR)/vulkan_api.o: vulkan_api.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c $(OUTPUT_OPTION) src/vulkan_api.cpp	

$(OBJDIR)/render_linux.o: render_linux.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c $(OUTPUT_OPTION) src/render_linux.cpp		

$(OBJDIR)/partical_lib.o: partical_lib.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c $(OUTPUT_OPTION) src/partical_lib.cpp	


debug.out: $(OBJS)
	$(CXX) $(CXXFLAGS_D) -o $(OBJS) $(LIBS)  $(OUTPUT_OPTION) $< 

.PHONY: shaderz 
shaderz: $(SHADER_LIST)
	bash shader_complie.sh 

.PHONY: all

all: $(OBJS) 

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

BINARIEZ = $(OBJS) vlkantest.out


#all: clean $(binaries)
print: *.hpp *.cpp
	 lpr -p $?
	
.PHONY: clean
clean:
	rm -f $(BINARIEZ) *.o
	echo Clean done

SHADER_LIST := $(addprefix $(SHADER_DIR)/,elemental/compute_partical/compute_expanse_BASE_A.glsl elemental/compute_partical/vertex_partical_BASE_A.glsl elemental/compute_partical/frag_partical_BASE_A.glsl)
