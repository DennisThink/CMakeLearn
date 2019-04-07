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