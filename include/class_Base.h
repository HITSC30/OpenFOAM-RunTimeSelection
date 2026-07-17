#ifndef __BASE_BASE_H__
#define __BASE_BASE_H__

#include <iostream>
#include <string>
#include <memory>
// #include "RTS_Macros00.hpp"
#include "RTS_Macros01.hpp"


class Base
{
public:
    Base();
    Base(const std::string &str);
    virtual ~Base() = default;
    virtual void print() = 0;

    // step0: 将New抽象做Base基类函数，非常的复杂，不适合做，或者是目前的思路做不出来
    // static std::unique_ptr<Base>New(const std::string& classname);

    // 宏测试
    CLASS_NAME;
    DeclareRunTimeSelectionTable(Word,std::unique_ptr,Base,(const std::string&));
    static std::unique_ptr<Base> New(const std::string &str);

private:
    std::string stringdata_;
};


#endif