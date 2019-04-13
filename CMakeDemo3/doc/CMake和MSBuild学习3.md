# CMake和MSBuild学习笔记(3)------编译MFC

## 1. 目录结构介绍
![Folder](https://www.dennisthink.com/wp-content/uploads/2019/04/MFC_FOLDER_STRUCT.png)

1. Build32.bat和Build64.bat分别是32位和64位的编译脚本。
2. CMakeMFC1/CMakeMFC1/CMakeLists.txt 是MFC程序的CMake编译脚本。
3. `CMakeMFC1.cpp`  `CMakeMFC1.h` `CMakeMFC1.rc` `CMakeMFC1Dlg.cpp` `CMakeMFC1Dlg.h` `Resource.h` `stdafx.cpp` `stdafx.h` `targetver.h` 以及`CMakeMFC1.ico` `CMakeMFC1.rc2`是用VisualStudio的MFC向导生成对话框源程序产生的代码。

4. `CMakeMFC1/CMakeLists.txt`是最外层的CMake编译脚本，当需要编译多个程序的时候，在此处修改。

## 2. CMakeLists.txt的详细说明
下面对 CMakeMFC1/CMakeMFC1/CMakeLists.txt 进行详细说明。
```cmake

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
```

此CMakeLists.txt需要注意的地方有

1. 需要增加以下两条针对MFC的设置
```cmake
# 需要增加这一条，具体原因不清楚
ADD_DEFINITIONS(-D_AFXDLL)

# 在共享库中使用MFC
SET(CMAKE_MFC_FLAG 2)
```
2. 需要增加针对Win32的程序设置
```cmake
#设置可执行程序的文件名，注意此处有WIN32表示是一个Win32的GUI程序(程序的入口不同，WIN32的入口函数不是main(int argc,char * argv[]) )
add_executable(MFCDemo1 WIN32 ${SOURCE_FILE} ${RC_FILE})
```

## 3.编译脚本介绍
此处的编译脚本与前两篇的编译脚本类似，注意的地方是 MSBuild.exe之后的文件名，需要和`CMakeMFC/CMakeLists.txt`的 *Project* 的设置相对应。
```bat
mkdir Build32

cd Build32

cmake ../CMakeMFC1

MSBuild.exe CMakeMFCDemo1.sln -property:Configuration=Debug
MSBuild.exe CMakeMFCDemo1.sln -property:Configuration=Release
cd ..
cd bin
cd Debug32
MFCDemo1.exe
```

## 4.编译后的结果

![after_build](https://www.dennisthink.com/wp-content/uploads/2019/04/after_build.png)


图中红色的方框里就是编译出的结果。中间文件都在Build32目录下，这样源代码和中间的编译结果彻底的分开了。

MFC的运行结果

![MFC_DIALOG](./Run_result.png)
