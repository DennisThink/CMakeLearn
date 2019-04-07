#ifndef _CMAKE_DEMO2_DIV_CLASS_SHARED_H_
#define _CMAKE_DEMO2_DIV_CLASS_SHARED_H_
#define DLLEXPORT   __declspec(dllexport)
class DLLEXPORT CDivClass
{
public:
    int Div(int x,int y);
};
#endif