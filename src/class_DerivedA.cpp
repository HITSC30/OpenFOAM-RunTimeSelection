#include "class_DerivedA.h"


void DerivedA::print()
{
    std::cout << "DerivedA类的print()函数" << std::endl;
}
// 宏测试
DEFINE_CLASS_NAME(DerivedA);
addToRunTimeSelectionTable((),Word,Base,DerivedA);
// ！！！构造函数不继承
DerivedA::DerivedA():Base()
{

};
DerivedA::DerivedA(const std::string &str):Base(str)
{

};