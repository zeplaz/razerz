
BASE_DEPZ = exrtn_vulkan.hpp  vk_abstracionz.hpp
#vk_base.o $(BASE_DEPZ) $(CXX) -c -o  $@ $< $(CFLAGS)
$(OBJDIR)/main.o:  main.cpp vk_shaderz.hpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c main.cpp
$(OBJDIR)/exrtn_vulkan.o: $(BASE_DEPZ) exrtn_vulkan.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c exrtn_vulkan.cpp 
$(OBJDIR)/vk_abstracionz.o:  $(BASE_DEPZ) $(DEPS_FULLH) vk_abstracionz.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c vk_abstracionz.cpp
$(OBJDIR)/vk_shaderz.o: vk_shaderz.hpp vulkan_definz.hpp  vk_shaderz.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c vk_shaderz.cpp
$(OBJDIR)/vulkan_api.o: vulkan_api.hpp  $(BASE_DEPZ) vulkan_api.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c  vulkan_api.cpp


vlkantest.out: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(OBJS) $(LIBS)

$(OBJDIR)/%.o : $(CURRENT_CPP_LIST)
	$(COMPILE.cc)
	
$(OBJDIR)/main.o: main.cpp 
	$(CXX) $(CXXFLAGS) $(LIBS) -c main.cpp
$(OBJDIR)/exrtn_vulkan.o: exrtn_vulkan.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c exrtn_vulkan.cpp 
$(OBJDIR)/vk_abstracionz.o: vk_abstracionz.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c vk_abstracionz.cpp
$(OBJDIR)/vk_shaderz.o: vk_shaderz.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c vk_shaderz.cpp
$(OBJDIR)/vulkan_api.o: vulkan_api.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c  vulkan_api.cpp

	DEPS_FULLH = flag_templatez.hpp vulkan_definz.hpp vulkani_strucz.hpp

CURRENT_CPP_LIST = main.cpp vk_shaderz.cpp vulkan_api.cpp vk_abstracionz.cpp exrtn_vulkan.cpp