// 第一版本将宏细化，尽可能还原OpenFOAM宏名称及作用
#ifndef __RTS_Macros01_hpp__
#define __RTS_Macros01_hpp__

#include <iostream>
#include <functional>
#include <memory>
#include <unordered_map>
#include <stdexcept>

// 第一个宏，辅助宏，解决变量作为参数的情况下
// eg:combine(x,y) =>xy
// if x = red ,y = y, combine(x,y) = redy, but combine(x,y) = xy
#define RTS_COMBINE(X,Y) RTS_COMBINE_IMPL(X,Y)
#define RTS_COMBINE_IMPL(X,Y) X##Y

// 第二个宏，实际上在内中定义一个静态变量，描述类
// 定义宏
#define CLASS_NAME static std::string typeName
// 实现宏
// 虚类静态变量定义的一个特征，且cpp里只写类型作用区域和数值
#define DEFINE_CLASS_NAME(classType)    \
std::string classType::typeName(#classType)

// 第三个宏，实际上在基类中定义一个静态变量，哈希表储存相关类型的数据
// 本质上是完成New函数的相关功能，能够从基类静态变量中提取相关数据
// 定义宏
// 基类中定义一个静态变量，子类继承的时候，可以选择注册到Base中的哈希表中
// 类比OpenFOAM，可以选择Word或Dict两种模式，注册到哈希表中
// step0：定义一个储存函数类型的容器,命名规则为WordConstructorPtr/DictCOnstructorPtr
// step1：定义一个哈希表类型，命名规则为WordConstructorTable/DictCOnstructorTable
// step2：定义一个哈希表类型指针，命名规则为WordConstructorTablePtr/DictCOnstructorTablePtr，该指针为基类中的静态变量；注册为指针避免静态初始化顺序导致问题
// RegisterType：注册类型，可以选择为Word/Dict
// PtrType：指针类型，可以选择为OpenFOAM封装的指针或memory库封装的指针，默认为std::unique_ptr
// BaseType：基类类型
// Args1：参数1,其为()则为空参，("str")则用str初始化std::unique_ptr<Base>
// 后续扩展为完美转发以及可变参数
#define DeclareRunTimeSelectionTable(RegisterType,PtrType,BaseType,Args1)  \
using RTS_COMBINE(RTS_COMBINE(RegisterType,Constructor),Ptr) = std::function<PtrType<BaseType>Args1>;  \
using RTS_COMBINE(RTS_COMBINE(RegisterType,Constructor),Table) = std::unordered_map<std::string,RTS_COMBINE(RTS_COMBINE(RegisterType,Constructor),Ptr)>; \
static RTS_COMBINE(RTS_COMBINE(RegisterType,Constructor),Table)* RTS_COMBINE(RTS_COMBINE(RegisterType,Constructor),TablePtr)
// 实现宏
// 基类静态变量定义：声明类型后，初始化
#define DefineRunTimeSelectionTable(BaseType,RegisterType)  \
BaseType::RTS_COMBINE(RTS_COMBINE(RegisterType,Constructor),Table)* BaseType::RTS_COMBINE(RTS_COMBINE(RegisterType,Constructor),TablePtr) = nullptr

// 第四个宏，注册宏。子类调用注册到基类的哈希表中
// 首先判断是否存在哈希表指针，避免越界，本质上nullptr不能注册
// 哈希表存在的情况下，注册
// 工具参数，帮助执行注册，命名规则为：WordConstructorDerivedA,WordConstructorDerivedB,DictConstructorDerivedA,DictConstructorDerivedB
// Args1，为()，则 == std::unique_ptr<double>()，为(3) == std::unique_ptr<double>(3)
// RegisterType：注册类型，可以选择为Word/Dict
// BaseType：基类类型
// DerivedType：子类类型
// 哈希表指针注册： (*Ptr)[DerivedName] = 一个函数（符合类型）
// 实现宏
#define addToRunTimeSelectionTable(Args1,RegisterType,BaseType,DerivedType) \
static const bool RTS_COMBINE(RTS_COMBINE(RegisterType,Constructor),DerivedType) = []()->bool \
{   \
    if(BaseType::RTS_COMBINE(RTS_COMBINE(RegisterType,Constructor),TablePtr) == nullptr)    \
    {   \
        std::cout << "哈希表指针不存在，首先创建一个新的哈希表指针" << std::endl; \
        BaseType::RTS_COMBINE(RTS_COMBINE(RegisterType,Constructor),TablePtr) = new BaseType::RTS_COMBINE(RTS_COMBINE(RegisterType,Constructor),Table)();  \
    }   \
    (*(BaseType::RTS_COMBINE(RTS_COMBINE(RegisterType,Constructor),TablePtr)))[#DerivedType]    \
    = [](auto &&... a)->std::unique_ptr<BaseType> \
    {   \
        return std::make_unique<DerivedType>(std::forward<decltype(a)>(a)...); \
    };    \
    return true;    \
}()

// 第五个宏，封装到基类中New函数。查询哈希表是否存在相应的键值对
// 同样先查询是否存在哈希表，然后返回其数值。我们同样用一个bool类型触发其产生
// 工具参数，帮助执行注册，命名规则为：WordConstructorLookUpDerivedA,WordConstructorLookUpDerivedB,DictConstructorLookUpDerivedA,DictConstructorLookUpDerivedB
// 获取哈希表，命名规则为：WordConstructorTableDerivedA,WordConstructorTableDerivedB,DictConstructorTableDerivedA,DictConstructorTableDerivedB
// RegisterType：注册类型，可以选择为Word/Dict
// BaseType：基类类型
// DerivedType：子类类型
#define RTS_LOOKUP_AND_CONSTRUCT(BaseType,DerivedType,RegisterType,Args1,...) \
if(BaseType::RTS_COMBINE(RTS_COMBINE(RegisterType,Constructor),TablePtr) == nullptr)    \
{   \
std::cout << "哈希表指针不存在，您查询的表格不可能存在一个不存在的东西里。" << std::endl; \
std::cout << "我们先建立一个哈希表" << std::endl; \
BaseType::RTS_COMBINE(RTS_COMBINE(RegisterType,Constructor),TablePtr) = new BaseType::RTS_COMBINE(RTS_COMBINE(RegisterType,Constructor),Table)();  \
}   \
auto& RTS_COMBINE(RTS_COMBINE(RegisterType,ConstructorTable),RegisterType) = *(BaseType::RTS_COMBINE(RTS_COMBINE(RegisterType,Constructor),TablePtr));  \
auto iter = RTS_COMBINE(RTS_COMBINE(RegisterType,ConstructorTable),RegisterType).find(DerivedType);    \
if(iter == RTS_COMBINE(RTS_COMBINE(RegisterType,ConstructorTable),RegisterType).end())  \
{   \
    std::cout << "Unknown Type: " << DerivedType << std::endl; \
    return nullptr; \
}   \
return iter->second(__VA_ARGS__)






#endif
