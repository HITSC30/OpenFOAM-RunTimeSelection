// 复现工厂模式，从而抽象出宏
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>

#include "class_Base.h"
#include "class_DerivedA.h"
#include "class_DerivedB.h"

using creator = std::function<std::unique_ptr<Base>()>;
std::unordered_map<std::string, creator>& getBaseTable()
{
    static std::unordered_map<std::string, creator> table;
    return table;
}
void registerToBaseTable(const std::string& baseType, creator ct)
{
    getBaseTable()[baseType] = std::move(ct);
}
std::unique_ptr<Base> New(const std::string& baseType)
{
    auto iter = getBaseTable().find(baseType);
    if (iter == getBaseTable().end())
    {
        std::cout << "Unknown type: " << baseType << std::endl;
        return nullptr;
    }
    return iter->second();
}
namespace
{
    const static bool test = []()->bool
    {
        registerToBaseTable("DerivedA",
            []()->std::unique_ptr<Base>
            {
                return std::make_unique<DerivedA>();
            }
            );

        return true;
    }();
}