#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>

#include "class_Base.h"
#include "class_DerivedA.h"
#include "class_DerivedB.h"
#include "RTS_Macros01.hpp"


#define X SC
#define Y 30


int main(int argc,char* argv[])
{
    // // 测试第一个宏
    // double XY = 0.0;
    // double SC30 = 30.0;
    // std::cout << RTS_COMBINE_IMPL(X,Y) << std::endl;
    // std::cout << RTS_COMBINE(X,Y) << std::endl;
    // int XY = 0;
    // int SC30 = 1;
    // std::cout << RTS_COMBINE_IMPL(X,Y) << std::endl;
    // std::cout << RTS_COMBINE(X,Y) << std::endl;
    // // 测试第二个宏
    // std::cout << Base::typeName << std::endl;
    // std::cout << DerivedA::typeName << std::endl;
    // std::cout << DerivedB::typeName << std::endl;
    // // 测试第三个宏
    // if (Base::WordConstructorTablePtr == nullptr)
    // {
    //     std::cout << "基类中哈希表指针构造成功" << std::endl;
    // }
    // auto ptr = (*Base::WordConstructorTablePtr)["DerivedA"]();
    // ptr->print();
    // 测试第五个宏
    Base::New("DerivedB")->print();
    return 0;
}