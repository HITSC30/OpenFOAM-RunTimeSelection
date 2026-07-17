#include "class_Base.h"

// RTS_BASEPART(Base);

Base::Base() : stringdata_()
{
    std::cout<< "Base基类的无参数默认构造函数" <<std::endl;
};
Base::Base(const std::string &str) : stringdata_(str)
{
    std::cout<< "Base基类的含参数构造函数" <<std::endl;
};
// Base::~Base()
// {
//     std::cout<< "Base基类的无参数默认构造函数" <<std::endl;
// };

// std::unique_ptr<Base> Base::New(const std::string& classname)
// {
//
//     auto iter = getBaseTable().find(classname);
//     if (iter == getBaseTable().end())
//     {
//         std::cout << "Unknown type: " << classname << std::endl;
//         return nullptr;
//     }
//     return iter->second();
// }

// 宏测试
DEFINE_CLASS_NAME(Base);
DefineRunTimeSelectionTable(Base,Word);
std::unique_ptr<Base> Base::New(const std::string &str)
{
    // RTS_LOOKUP_AND_CONSTRUCT(Base,str,Word,());
    RTS_LOOKUP_AND_CONSTRUCT(Base,str,Word,(const std::string&),"sc30");
    // RTS_LOOKUP_AND_CONSTRUCT(Base,str,Word,"sc30","hhh");

};