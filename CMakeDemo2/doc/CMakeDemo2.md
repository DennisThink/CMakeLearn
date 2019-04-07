# CMake 和MSBuild学习笔记(2)

本次的学习主要介绍使用CMake和MSBuild来使用静态库和动态库的方法。

## 1.整体目录结构介绍
整个程序主要分为5个部分，包括4个库和一个主程序，下面依次介绍这些库和程序。
1. addStatic 加法函数静态库，导出为函数
2. divClassShared 除法运算动态库,动态导出类
3. main 主程序
4. mulClassStatic 乘法运算静态库,静态导出类
5. subShared 减法运算的动态库，导出为函数

整体目录结构图
![Tree](https://www.dennisthink.com/wp-content/uploads/2019/04/CMakeDemo2_Tree.png)
## 2. 编译脚本和编译效果

### 2.1 32位编译

1. 编译脚本
```bat
pause
mkdir Build32
cd Build32
cmake ../SRC
MSBuild.exe CMakeDemo2.sln -property:Configuration=Debug
MSBuild.exe CMakeDemo2.sln -property:Configuration=Release

cd ../bin/Debug32/
Main.exe
pause

cd ../Release32/
Main.exe
pause
```
2. 编译效果

![Compile_32](https://www.dennisthink.com/wp-content/uploads/2019/04/Compile_32_GIF_Demo2.gif)

### 2.2 64位编译脚本

1. 编译脚本
```bat
pause
mkdir Build64
cd Build64
cmake ../SRC -G "Visual Studio 15 2017 Win64"
MSBuild.exe CMakeDemo2.sln -property:Configuration=Debug
MSBuild.exe CMakeDemo2.sln -property:Configuration=Release

cd ../bin/Debug64/
Main.exe
pause

cd ../Release64/
Main.exe
pause
```
2. 编译效果

![Compile_64](https://www.dennisthink.com/wp-content/uploads/2019/04/Compile_64_GIF_Demo2.gif)

## 3. 具体内容介绍

### 3.1 addStatic 
1. CMakeLists.txt
```CMake
cmake_minimum_required(VERSION 3.0)
project(addStatic)
SET(ADD_SOURCE_FILE ./Add.h ./Add.cpp)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../lib)
if(CMAKE_CL_64)
    #64位的设置
    SET(CMAKE_DEBUG_POSTFIX "_64d")    
    SET(CMAKE_RELEASE_POSTFIX "_64r") 
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin/Debug64/)
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin/Release64/)
else()
    #32位的设置
    SET(CMAKE_DEBUG_POSTFIX "_32d")    
    SET(CMAKE_RELEASE_POSTFIX "_32r") 
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin/Debug32/)
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin/Release32/)
endif()
add_library(addStatic ${ADD_SOURCE_FILE})
```

2. Add.h

```cpp
#ifndef _CMAKE_DEMO2_ADD_UTIL_H_
#define _CMAKE_DEMO2_ADD_UTIL_H_
int Add(int x,int y);
#endif
```

3. Add.cpp

```cpp
#include "Add.h"
int Add(int x,int y)
{
    return x+y;
}
```

### 3.2 divClassShared 

1. CMakeLists.txt

```CMake
cmake_minimum_required(VERSION 3.0)
project(divShared)
SET(DIV_SOURCE_FILE ./divClass.h ./divClass.cpp)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../lib)
if(CMAKE_CL_64)
    #64位的设置
    set(CMAKE_DEBUG_POSTFIX "_64d")    
    set(CMAKE_RELEASE_POSTFIX "_64r") 
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin/Debug64/)
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin/Release64/)
else()
    #32位的设置
    set(CMAKE_DEBUG_POSTFIX "_32d")    
    set(CMAKE_RELEASE_POSTFIX "_32r") 
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin/Debug32/)
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin/Release32/)
endif()
SET(BUILD_SHARED_LIBS ON)

add_library(divShared ${DIV_SOURCE_FILE})
```
2. divClass.h

```
#ifndef _CMAKE_DEMO2_DIV_CLASS_SHARED_H_
#define _CMAKE_DEMO2_DIV_CLASS_SHARED_H_
#define DLLEXPORT   __declspec(dllexport)
class DLLEXPORT CDivClass
{
public:
    int Div(int x,int y);
};
#endif
```

3. divClass.cpp

```
#include "divClass.h"
int CDivClass::Div(int x,int y)
{
    if( y != 0 )
    {
        return x/y;
    }
    else
    {
        return 0;
    }
    
}
```

### 3.3 main

1. CMakeLists.txt

```CMake
cmake_minimum_required(VERSION 3.0)
project(Main)
SET(SOURCE_FILE main.cpp)
include_directories(../AddStatic/)
include_directories(../subShared)
include_directories(../mulClassStatic)
include_directories(../divClassShared)
link_libraries(addStatic)
link_libraries(subShared)
link_libraries(mulClassStatic)
link_libraries(divShared)

if(CMAKE_CL_64)
    set(CMAKE_DEBUG_POSTFIX "_64d")    
    set(CMAKE_RELEASE_POSTFIX "_64r")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin/Release64)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin/Debug64)
else(CMAKE_CL_64)
    set(CMAKE_DEBUG_POSTFIX "_32d")    
    set(CMAKE_RELEASE_POSTFIX "_32r")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin/Release32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin/Debug32)
endif()
add_executable(Main ${SOURCE_FILE}) 
```

2. main.cpp

```cpp
#include <iostream>
#include "Add.h"
#include "Sub.h"
#include "mulClass.h"
#include "divClass.h"
int main(int argc,char * argv[])
{
    std::cout<<"CMakeDemo2"<<std::endl;
    std::cout<<argc<<"    "<<argv[0]<<std::endl;
    std::cout<<"Add: "<<Add(3,2)<<std::endl;
    std::cout<<"Sub: "<<Sub(4,2)<<std::endl;
    CMulClass mulUtil;
    std::cout<<"Mul: "<<mulUtil.Mul(2,8)<<std::endl;
    CDivClass divUtil;
    std::cout<<"Div: "<<divUtil.Div(8,4)<<std::endl;
    return 0;
}
```

### 3.4 mulClassStatic

1. CMakeLists.txt

```CMake
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
```

2. mulClass.h

```cpp
#ifndef _CMAKE_DEMO2_MUL_CLASS_STATIC_H_
#define _CMAKE_DEMO2_MUL_CLASS_STATIC_H_
class CMulClass
{
public:
    int Mul(int x,int y);
};
#endif
```

3. mulClass.cpp

```cpp
#include "mulClass.h"
int CMulClass::Mul(int x,int y)
{
    return x*y;
}
```

### 3.5 subShared

1. CMakeLists.txt

```CMake
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
```

2. Sub.h

```cpp
#ifndef _CMAKE_DEMO2_SUB_SHARED_H_
#define _CMAKE_DEMO2_SUB_SHARED_H_
#define DllExport   __declspec(dllexport)
int DllExport Sub(int x,int y);
#endif
```

3. Sub.cpp

```cpp
#include "Sub.h"
int Sub(int x,int y)
{
    return x-y;
}
```
