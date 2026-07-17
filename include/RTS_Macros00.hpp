// 抽象出整个宏
#ifndef __RTS_Macros00__
#define __RTS_Macros00__

#include <iostream>
#include <functional>
#include <memory>
#include <unordered_map>
#include <stdexcept>

// 定义一个辅助宏，解决宏作为参数传入的情况
#define RTS_COMBINE00(X,Y) RTS_COMBINE_IMPL00(X,Y)
#define RTS_COMBINE_IMPL00(X,Y) X##Y
// 第一个宏，基础构件
#define RTS_BASEPART(baseType)  \
using creator = std::function<std::unique_ptr<baseType>()>; \
std::unordered_map<std::string, creator>& getBaseTable()    \
{   \
    static std::unordered_map<std::string, creator> table;  \
    return table;   \
}   \
void registerToBaseTable(const std::string& basetype, creator ct)   \
{   \
    getBaseTable()[basetype] = std::move(ct);   \
}

// 定义第二个宏，构建多态
#define RTS_INITILIZE(baseType,derivedType)   \
const static bool test = []()->bool \
{   \
    registerToBaseTable(#derivedType, \
        []()->std::unique_ptr<baseType> \
        {   \
            return std::make_unique<derivedType>();    \
        }   \
        );  \
    return true;    \
}()


#endif