#设置需要的CMake的最低版本
cmake_minimum_required(VERSION 3.0)
#设置工程名称
project(CMakeMFCDemo1Test)

#CMAKE_MFC_FLAG参数的意思是这样解释的：

#To use MFC, the CMAKE_MFC_FLAG variable must be set as follows:
#为了使用MFC，CMAKE_MFC_FLAG需要设置为以下的值

# 0: Use Standard Windows Libraries
# 0: 使用标准的Windows库

# 1: Use MFC in a Static Library
# 1：在静态库中使用MFC
# 2: Use MFC in a Shared DLL

# 2: 在共享库中使用MFC
# set(CMAKE_MFC_FLAG 2)

# 需要增加这一条，具体原因不清楚
ADD_DEFINITIONS(-D_AFXDLL)

# 在共享库中使用MFC
SET(CMAKE_MFC_FLAG 2)

# 设置源文件
SET(SOURCE_FILE ./stdafx.h ./targetver.h ./stdafx.cpp ./Resource.h 
                ./CMakeMFC1Dlg.h ./CMakeMFC1Dlg.cpp
                ./CMakeMFC1.h ./CMakeMFC1.cpp)

# 设置资源文件
SET(RC_FILE ./CMakeMFC1.rc ./res/CMakeMFC1.ico ./res/CMakeMFC1.rc2)

if(CMAKE_CL_64)
    #设置64位的程序目标(可执行程序)输出路径
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin/Debug64/)     
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin/Release64/) 
else()
    #设置32位的程序目标(可执行程序)输出路径
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin/Debug32/)     
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin/Release32/) 
endif()

#设置可执行程序的文件名，注意此处有WIN32表示是一个Win32的GUI程序
add_executable(MFCDemo1 WIN32 ${SOURCE_FILE} ${RC_FILE})