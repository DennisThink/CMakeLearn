cmake_minimum_required(VERSION 3.0)
project(subShared)
SET(SUB_SOURCE_FILE ./Sub.h ./Sub.cpp)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../lib)
if(CMAKE_CL_64)
    #64位的设置
    set(CMAKE_DEBUG_POSTFIX "_64d")    
    set(CMAKE_RELEASE_POSTFIX "_64r") 
    #设置DEBUG的输出目录
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin/Debug64/)
    #设置RELEASE的输出目录
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin/Release64/)
else()
    #32位的设置
    #设置DEBUG版本的后缀为_32d
    set(CMAKE_DEBUG_POSTFIX "_32d")
    #设置Release版本的后缀为_32r    
    set(CMAKE_RELEASE_POSTFIX "_32r") 
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin/Debug32/)
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin/Release32/)
endif()
#设置生成共享lib
SET(BUILD_SHARED_LIBS ON)
#设置生成的动态库的名称为subShared
add_library(subShared ${SUB_SOURCE_FILE})