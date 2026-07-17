#ifndef __DERIVEDB_HPP__
#define __DERIVEDB_HPP__

#include "class_Base.h"
#include "RTS_Macros01.hpp"

class DerivedB : public Base
{
public:
    // ！！！构造函数不继承
    DerivedB();
    DerivedB(const std::string &str);
    void print() override;
    // 宏
    CLASS_NAME;
private:

};

#endif
