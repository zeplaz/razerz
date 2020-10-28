#!/bin/bash

BUILD_DRECTORY=l_build

if [ ! -d "$BUILD_DRECTORY" ]; then 
mkdir l_build 
   echo "new buildfolder created"
else 
   echo "l_build drectory exists"
fi 

if [ -z "$(ls -A $BUILD_DRECTORY)" ]; then
   echo "clean build"

else
   echo "drectory is NOT empty building on old.. set --cleaner flag to force clean build"
fi

cd l_build

cmake ..

#if [ "$SUCESS" = 0]; then 
    echo "cmake has run... runing make..."
make 
#fi




