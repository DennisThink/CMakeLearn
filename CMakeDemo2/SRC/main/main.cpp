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