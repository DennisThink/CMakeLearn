# CMakeLearn1

## 1. 简介
CMake是一个跨平台的用来编译C++的工具，具体的方法是通过编写`CMakeLists.txt`来控制编译的过程。

## 2. 示例讲解

CMakeLists.txt
```cmake
#声明cmake的最低版本，必须有
cmake_minimum_required(VERSION 3.0)
#工程名称
project(CMakeDemo1)

#开启W3级编译警告，并将警告视为错误
add_compile_options(/W3 /WX)

SET(SOURCE_FILE main.cpp)
#用来区分32和64位
if(CMAKE_CL_64)
    #64位
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin/Debug64/)    
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/Release64/)
else()
    #32位
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin/Debug32/)    
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/Release32/)
endif()
add_executable(Demo1 ${SOURCE_FILE})
```

## 3. C++源代码

main.cpp
```cpp
#include <iostream>
int main(int argc,char * argv[])
{
    //消除参数未使用的警告
    std::cout<<argc<<"   "<<argv[0]<<std::endl;
    
    //程序名称
    std::cout<<"Cmake Demo 1"<<std::endl;
    
    //程序编译时间
    std::cout<<"Compile Time:     "<<__DATE__<<"  "<<__TIME__<<std::endl;
    
    //编译器版本VS适用
    std::cout<<"Compiler Version: "<<_MSC_VER<<std::endl;
    
    //判断程序是32位还是64位
    if(sizeof(int*)==4)
    {
        std::cout<<"32 Bit"<<std::endl;
    }
    else
    {
        std::cout<<"64 Bit"<<std::endl;
    }

    //判断大小端
    short int a = 0x1122;//十六进制，一个数值占4位
	char b =  *(char *)&a;  //通过将short(2字节)强制类型转换成char单字节，b指向a的起始字节（低字节）
	if( b == 0x11)//低字节存的是数据的高字节数据
	{
		std::cout<<"Big Endian"<<std::endl;
	}
	else
	{
		//是小端模式
        std::cout<<"Little Endian"<<std::endl;
	}
    //判断是Debug版本还是Release版本
#ifdef _DEBUG
    std::cout<<"Debug Mode"<<std::endl;
#else
    std::cout<<"Release Mode"<<std::endl;;
#endif
    return 0;
}
```

## 4.准备工作
### 4.1 CMake添加到Path

### 4.2 MSBuild添加到Path