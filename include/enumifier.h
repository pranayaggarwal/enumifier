//
//  enumifier.h
//
//  Created by Pranay Kumar on 29/09/19.
// Copyright (c) 2019 pranayaggarwal25@gmail.com
//  _______ .__   __.  __    __  .___  ___.  __   _______  __   _______ .______
// |   ____||  \ |  | |  |  |  | |   \/   | |  | |   ____||  | |   ____||   _  \
// |  |__   |   \|  | |  |  |  | |  \  /  | |  | |  |__   |  | |  |__   |  |_)  |
// |   __|  |  . `  | |  |  |  | |  |\/|  | |  | |   __|  |  | |   __|  |      /
// |  |____ |  |\   | |  `--'  | |  |  |  | |  | |  |     |  | |  |____ |  |\  \----.
// |_______||__| \__|  \______/  |__|  |__| |__| |__|     |__| |_______|| _| `._____|
//
//https://github.com/pranayaggarwal/enumifier
//version 0.1
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
// SPDX-License-Identifier: MIT
//
// Permission is hereby  granted, free of charge, to any  person obtaining a copy
// of this software and associated  documentation files (the "Software"), to deal
// in the Software  without restriction, including without  limitation the rights
// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef enumifier_h
#define enumifier_h

#include <iostream>
#include <string>
#include <vector>

#if defined(__clang__) || defined(__GNUC__) && __GNUC__>= 9 || defined(_MSC_VER)
    #define ENUMIFIER_LIBRARY_COMPILER_SUPPORT 1
#else
    #define ENUMIFIER_LIBRARY_COMPILER_SUPPORT 0
#endif

namespace enumifier {

    namespace utils
    {
        std::string beautify(std::string name) noexcept;
        
        std::string trim_by_function_name(std::string const& fnName, std::string& sourceName);
        
        std::string trim_by_token_braces(std::string& sourceName);
        
        std::string preprocess_string(std::string functionName);
    }
}

namespace enumifier {
    
    constexpr bool is_supported_enumifier = ENUMIFIER_LIBRARY_COMPILER_SUPPORT;

    namespace type_traits
    {
        
        // Defining type_traits here to make this work back till C++11
        template <class T>
        using remove_reference_t = typename std::remove_reference<T>::type;
        
        template <class T>
        using remove_cv_t = typename std::remove_cv<T>::type;
        
        template <typename T>
        using remove_cvref_t = typename type_traits::remove_cv_t<type_traits::remove_reference_t<T>>;
        
        template< bool B, class T = void>
        using enable_if_t = typename std::enable_if<B,T>::type;
        
        template <class T>
        using underlying_type_t = typename std::underlying_type<T>::type;
    
        template <class T>
        using underlying_type_t = typename std::underlying_type<T>::type;
    }


#if ENUMIFIER_LIBRARY_COMPILER_SUPPORT

    namespace impl
    {
        template<typename E, E V>
        std::string namestring()
        {
#if __cpp_nontype_template_parameter_auto
        static_assert(std::is_enum<E>::value, "enumifier::enum_name() function requires enum types");
#endif // __cpp_nontype_template_parameter_auto
            
#if defined(__clang__) || defined(__GNUC__) && __GNUC__ >= 9
            std::string fullName = __PRETTY_FUNCTION__;
            fullName = utils::preprocess_string(fullName);
            auto name = utils::beautify(fullName);
            return name;
#elif defined(_MSC_VER)
            std::string fullName = __FUNCSIG__;
            fullName = utils::preprocess_string(fullName);
            auto name = utils::beautify(fullName);
            return name;
#endif
            return std::string{};
        }
    }
    
#if __cpp_nontype_template_parameter_auto
    
    
    /*
     
    For c++14, we don't need the second template argument but for sake of universal function
    signature, Have made the implementation two argument based.
     
    template <auto V, typename T = type_traits::enable_if_enum_t<decltype(V)>>
    std::string enum_name() noexcept
    {
        static_assert(type_traits::check_enum_v<decltype(V),T>, "enumifier::enum_name() function requires enum types");
        return impl::namestring<T, V>();
    }
    */
    
    template <typename T, auto V>
    std::string enum_name() noexcept
    {
        static_assert(std::is_enum<T>::value, "enumifier::enum_name() function requires enum types");
        return impl::namestring<T, V>();
    }

    
#else
    template <typename T, T V>
    std::string enum_name() noexcept
    {
        static_assert(std::is_enum<T>::value, "enumifier::enum_name() function requires enum types");
        const T X = V;
        return impl::namestring<T, X>();
    }

#endif
    
#endif // #if ENUMIFIER_LIBRARY_COMPILER_SUPPORT

    #define ENUMIFIER_MACRO_PRINT(x) (#x)
    
    #define ENUMIFIER_ENUM_NAME(VAR1, VAR2) {\
        std::string enum_name = ENUMIFIER_MACRO_PRINT(VAR1);\
        enum_name = enumifier::utils::beautify(enum_name);\
        VAR2 = enum_name; \
    }
    
    // Returns integer value from enum value.
    template <typename E>
    constexpr type_traits::underlying_type_t<E> enum_integral_value(E value) noexcept {
        return static_cast<type_traits::underlying_type_t<E>>(value);
    }
}



namespace enumifier {
    
    namespace utils
    {
        std::string beautify(std::string name) noexcept
        {
            for (std::size_t i = name.size(); i > 0; --i) {
                if (!((name[i - 1] >= '0' && name[i - 1] <= '9') ||
                      (name[i - 1] >= 'a' && name[i - 1] <= 'z') ||
                      (name[i - 1] >= 'A' && name[i - 1] <= 'Z') ||
                      (name[i - 1] == '_'))) {
                    name = name.substr(i);
                    break;
                }
            }
            
            if (name.size() > 0 && ((name.front() >= 'a' && name.front() <= 'z') ||
                                    (name.front() >= 'A' && name.front() <= 'Z') ||
                                    (name.front() == '_'))) {
                return name;
            }
            
            return name;
        }
        
        std::string trim_by_function_name(std::string const& fnName, std::string& sourceName)
        {
            size_t lIndex = sourceName.find(fnName);
            if(lIndex != std::string::npos)
            {
                sourceName = sourceName.substr(lIndex + fnName.length());
            }
            return sourceName;
        }
        
        std::string trim_by_token_braces(std::string& sourceName)
        {
            auto lIndexAngular = sourceName.find_first_of("<"), rIndexAngular = sourceName.find_first_of(">");
            auto lIndexSquare = sourceName.find_first_of("["), rIndexSquare = sourceName.find_first_of("]");
            
            if(lIndexAngular!= std::string::npos
               && rIndexAngular!= std::string::npos
               && rIndexAngular > lIndexAngular + 1)
            {
                sourceName = sourceName.substr(lIndexAngular + 1, rIndexAngular - lIndexAngular - 1);
            }
            else if(lIndexSquare!= std::string::npos
                    && rIndexSquare!= std::string::npos
                    && rIndexSquare > lIndexSquare + 1)
            {
                sourceName = sourceName.substr(lIndexSquare + 1, rIndexSquare - lIndexSquare - 1);
            }
            
            return sourceName;
        }
        
        std::string preprocess_string(std::string functionName)
        {
            const std::string fnName = "namestring";
            functionName = utils::trim_by_function_name(fnName, functionName);
            return utils::trim_by_token_braces(functionName);
        }
    }
}


#endif /* enumifier_h */
