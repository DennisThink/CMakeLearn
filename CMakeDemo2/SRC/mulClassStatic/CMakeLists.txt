cmake_minimum_required(VERSION 3.0)
project(mulClassStatic)
SET(MUL_SOURCE_FILE ./mulClass.h ./mulClass.cpp)
#设置生成lib的路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../lib)

if(CMAKE_CL_64)
    #64位编译的设置
    set(CMAKE_DEBUG_POSTFIX "_64d")    
    set(CMAKE_RELEASE_POSTFIX "_64r")
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin/Debug64/)
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin/Release64/)
else()
    #32位编译的设置
    set(CMAKE_DEBUG_POSTFIX "_32d")    
    set(CMAKE_RELEASE_POSTFIX "_32r")
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin/Debug32/)
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin/Release32/)
endif()
 
add_library(mulClassStatic ${MUL_SOURCE_FILE})