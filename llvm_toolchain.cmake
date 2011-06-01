#include using cmake -DCMAKE_TOOLCHAIN_FILE=../llvm_toolchain.cmake
# Modified from a tip by Matthew Hungerford in http://mhungerford.blogspot.com/2010/10/cmake-and-clangllvm-fun.html
INCLUDE(CMakeForceCompiler) #Disables checks
SET(CMAKE_SYSTEM_NAME Generic)
#Generic removes -rdynamic from linker, which llvm-ld doesn't support

CMAKE_FORCE_C_COMPILER( /usr/bin/clang CLang )
CMAKE_FORCE_CXX_COMPILER ( /usr/bin/clang++ CLang )
SET(CMAKE_RANLIB "/usr/bin/llvm-ranlib" CACHE INTERNAL STRING)
SET(CMAKE_AR "/usr/bin/llvm-ar" CACHE INTERNAL STRING)

SET(CMAKE_LINKER "/usr/bin/llvm-ld" CACHE INTERNAL STRING)
#SET(CMAKE_C_LINKER "/usr/bin/llvm-ld")
#SET(CMAKE_CXX_LINKER "/usr/bin/llvm-ld")

SET(CMAKE_C_LINK_EXECUTABLE "/usr/bin/llvm-ld -native <OBJECTS> -o  <TARGET> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <LINK_LIBRARIES>")
SET(CMAKE_CXX_LINK_EXECUTABLE "/usr/bin/llvm-ld -native <OBJECTS> -o  <TARGET> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <LINK_LIBRARIES> -L /usr/lib/gcc/i686-pc-linux-gnu/4.5.2 -lstdc++")

SET(CMAKE_FIND_ROOT_PATH /usr/bin)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)