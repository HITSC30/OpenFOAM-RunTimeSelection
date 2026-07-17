#include "class_DerivedB.h"
void DerivedB::print()
{
    std::cout << "DerivedB类的print()函数" << std::endl;
}
// 宏测试
DEFINE_CLASS_NAME(DerivedB);