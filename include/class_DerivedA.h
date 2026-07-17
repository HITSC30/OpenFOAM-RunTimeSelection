#ifndef __DERIVEDA_HPP__
#define __DERIVEDA_HPP__

#include "class_Base.h"
#include "RTS_Macros01.hpp"

class DerivedA : public Base
{
public:
    // ！！！构造函数不继承
    DerivedA();
    DerivedA(const std::string &str);
    void print() override;
    // 宏
    CLASS_NAME;
private:

};

#endif