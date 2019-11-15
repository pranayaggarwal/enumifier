//
//  main.cpp
//  enumifier
//
//  Created by Pranay Kumar on 29/09/19.
//  Copyright © 2019 AdobeInc. All rights reserved.
//

#include <iostream>
#include "enumifier.h"

void TestUnscopedEnumToString()
{
    std::cout<< " ===================== Started TestUnscopedEnumToString ===================== \n";
    std::cout<< "\n Unscoped Enum name = Color, value = Yellow, enumifier::enum_name = ";
    enum Color {Red, Green, Yellow};
    
    if(enumifier::is_supported_enumifier)
    {
        const Color g = Color::Yellow;
        std::cout<< enumifier::enum_name<Color, g>()<< '\n';
    }
    else
    {
        std::string enumString;
        ENUMIFIER_ENUM_NAME(Color::Yellow, enumString);
        std::cout<< enumString << '\n';
    }
    std::cout<< "\n ===================== Ended TestUnscopedEnumToString ===================== \n\n\n\n";
}

void TestScopedEnumToString()
{
    std::cout<< " ===================== Started TestScopedEnumToString ===================== \n";
    std::cout<< "\n Scoped Enum name = Color, value = Color::Yellow, enumifier::enum_name = ";
    enum class Color {Red, Green, Yellow};
    
    if(enumifier::is_supported_enumifier)
    {
        const Color g = Color::Yellow;
        std::cout<< enumifier::enum_name<Color, g>()<< '\n';
    }
    else
    {
        std::string enumString;
        ENUMIFIER_ENUM_NAME(Color::Yellow, enumString);
        std::cout<< enumString << '\n';
    }
    std::cout<< "\n ===================== Ended TestScopedEnumToString ===================== \n\n\n\n";
}

void TestUnscopedEnumToInteger()
{
    std::cout<< " ===================== Started TestUnscopedEnumToInteger ===================== \n";
    enum Color {Red, Green, Yellow};
    std::cout<< "\n Unscoped Enum name = Color{Red, Green, Yellow}, value = Yellow, enumifier::enum_integral_value = " << enumifier::enum_integral_value(Yellow)<< '\n';
    std::cout<< "\n ===================== Ended TestUnscopedEnumToInteger ===================== \n\n\n\n";
}

void TestScopedEnumToInteger()
{
    std::cout<< " ===================== Started TestScopedEnumToInteger ===================== \n";
    enum class Color {Red, Green, Yellow};
    std::cout<< "\n Scoped Enum name = Color{Red, Green, Yellow}, value = Color::Yellow, enumifier::enum_integral_value = " << enumifier::enum_integral_value(Color::Yellow)<< '\n';
    std::cout<< "\n ===================== Ended TestScopedEnumToInteger ===================== \n\n\n\n";
}

int main() {
    
    TestUnscopedEnumToString();
    TestScopedEnumToString();
    TestUnscopedEnumToInteger();
    TestScopedEnumToInteger();
    
    return 0;
}
