# Vulkan_modual_01.01

##### GOAL a linux-windows crossplatform vulkan rendering envroment.
is an exermental work on building up..
currenrly a binnary for linux is usally uptodate..
currently only linux code is finshed but it is designed to allow expantion
into windows easly. 

BINARY linux built via makefile, updated regulary, 
built on and for linux 86_64 ubuntu 20.10:
#### vlkantest.out

## BUILDING
USE the makefile it should work in a linux envroment which has the nessary libraryes installed. (see list in makefile for libs)

currently cmake is not settup (have some linking issues)

## FOLDERS

### ROOT 

Makefile to make build.

#### shader_build_info.info
this file is very imporant it is used to sort out shaders that are located
in the folder ../shaderglsl it also outlines some info that is used in them 
this is done to allow for on the fly recompling of shaders well program is running
of changes made to them in devlopment witout needing to recomple the main program.

### src
cpp files.
### headers
hpp files.

### objz
current objectfiles stages for make

### 3rd_party
includes some of the cmake finds and also the glad implimations
and other 3rd party tools for linux some of which are currntly not needed.
but will likely play a role later.

### l_build
location where cmake WOULD send linux builds...

### compile_bitz 
workspace for makefiles and cmake and other info

