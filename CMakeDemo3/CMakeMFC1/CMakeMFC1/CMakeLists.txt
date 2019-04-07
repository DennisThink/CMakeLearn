cmake_minimum_required(VERSION 3.0)
project(CMakeMFCDemo1Test)

#CMAKE_MFC_FLAG参数的意思是这样解释的：

#To use MFC, the CMAKE_MFC_FLAG variable must be set as follows:

#0: Use Standard Windows Libraries
#1: Use MFC in a Static Library
# 2: Use MFC in a Shared DLL
# set(CMAKE_MFC_FLAG 2)
ADD_DEFINITIONS(-D_AFXDLL)
SET(CMAKE_MFC_FLAG 2)

SET(SOURCE_FILE ./stdafx.h ./targetver.h ./stdafx.cpp ./Resource.h 
                ./CMakeMFC1Dlg.h ./CMakeMFC1Dlg.cpp
                ./CMakeMFC1.h ./CMakeMFC1.cpp)

SET(RC_FILE ./CMakeMFC1.rc ./res/CMakeMFC1.ico ./res/CMakeMFC1.rc2)
if(CMAKE_CL_64)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin/Debug64/)     
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin/Release64/) 
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin/Debug32/)     
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin/Release32/) 
endif()
add_executable(MFCDemo1 WIN32 ${SOURCE_FILE} ${RC_FILE})