
CXX=g++
CXXFLAGS = -Wall -g -std=c++17

LIBS = -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi -lxcb  -lglslang  -lSPIRV -lSPVRemapper  -lSPIRV-Tools-opt -lSPIRV-Tools -lMachineIndependent -lOSDependent -lpthread -lGenericCodeGen -lOGLCompiler


OBJDIR := objz
OBJS := $(addprefix $(OBJDIR)/,main.o vk_shaderz.o vulkan_api.o vk_abstracionz.o  exrtn_vulkan.o) 

VPATH = src: headers
GPATH = %.o OBJDIR
vpath %.hpp headers 
#_OBJ = main.o vk_base.o

vlkantest.out: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(OBJS) $(LIBS)  $(OUTPUT_OPTION) $< 

$(OBJDIR)/main.o: main.cpp 
	$(CXX) $(CXXFLAGS) $(LIBS) -c $(OUTPUT_OPTION) src/main.cpp
$(OBJDIR)/exrtn_vulkan.o: exrtn_vulkan.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c $(OUTPUT_OPTION) src/exrtn_vulkan.cpp 
$(OBJDIR)/vk_abstracionz.o: vk_abstracionz.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c $(OUTPUT_OPTION) src/vk_abstracionz.cpp
$(OBJDIR)/vk_shaderz.o: vk_shaderz.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c $(OUTPUT_OPTION) src/vk_shaderz.cpp
$(OBJDIR)/vulkan_api.o: vulkan_api.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c $(OUTPUT_OPTION) src/vulkan_api.cpp	

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
