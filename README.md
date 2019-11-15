# Enumifier

```text
  _______ .__   __.  __    __  .___  ___.  __   _______  __   _______ .______
 |   ____||  \ |  | |  |  |  | |   \/   | |  | |   ____||  | |   ____||   _  \
 |  |__   |   \|  | |  |  |  | |  \  /  | |  | |  |__   |  | |  |__   |  |_)  |
 |   __|  |  . `  | |  |  |  | |  |\/|  | |  | |   __|  |  | |   __|  |      /
 |  |____ |  |\   | |  `--'  | |  |  |  | |  | |  |     |  | |  |____ |  |\  \----.
 |_______||__| \__|  \______/  |__|  |__| |__| |__|     |__| |_______|| _| `._____|

```

Enumifier is a single header library to facilitate scoped / unscoped enum to string and integer conversion operations.

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/bc15b104e34440c68cc9eaca99e7dc79)](https://app.codacy.com/manual/pranayaggarwal/enumifier/dashboard)
[![License](https://img.shields.io/github/license/pranayaggarwal/enumifier)](LICENSE)
![Size](https://img.shields.io/github/repo-size/pranayaggarwal/enumifier)
[![Build status](https://img.shields.io/appveyor/ci/pranayaggarwal/enumifier)](https://ci.appveyor.com/project/pranayaggarwal/enumifier/branch/master)
[![Try online](https://img.shields.io/badge/try-online-blue.svg)](https://wandbox.org/permlink/xuWvGrYlYVcNUEV2)

## Compiler Support
Though all compilers are suported, GCC/clang and MSVC are fully supported and rest of the compilers are supported via a constrained Macro mode.

## Features
* Minimum supported version C++11
* Single Header-only library
* Dependency free
* Compile time only (for fully supported compilers)
* Scoped / Unscoped Enum to string conversion
* Enum to interger 

## APIs and usage

* ## enumifier::is_supported_enumifier
This is constexpr boolean indicating if your compiler is supported.

```text
If supported, you can use enumifier API enum_name<...>() to get the string from enum.
```
or 

```text
If not supported, you can use Macro ENUMIFIER_ENUM_NAME to get the string from enum.
```

* ## enumifier::enum_name
To convert enum (scoped or unscoped) value into string.

* ## enumifier::enum_integral_value
To convert enum values into underlying integeral value.

* ## ENUMIFIER_ENUM_NAME (Macro)
Non-smart, (works for rvalues only) To convert enum (scoped or unscoped) value into string.

## Examples (main.cpp)

```cpp
// For example color enum.
enum Elements { EARTH = 2, WATER = 4, FIRE = 5 };
// or 
enum class Elements { EARTH = 2, WATER = 4, FIRE = 5 };
```

* Enum value to string : function
  ```cpp
  Elements element = Elements::WATER;
  auto element_name = enumifier::enum_name(Elements, element);
  // element_name -> "WATER"
  ```
* Enum value to string : Macro
  ```cpp
  std::string element_name;
  ENUMIFIER_ENUM_NAME(Elements::WATER, element_name); // must pass enum value directly
  // element_name -> "WATER"
  ```  

* Enum value to integer
  ```cpp
    Elements element = Elements::WATER;
    auto element_integer = enumifier::enum_integral_value(element);
  // element_integer -> 4
  ```

## Integration
You need to only add the required file [enumifier.h](include/enumifier.h).
In order to run the tests of this repo in [main.cpp](main.cpp), run following cmake commands 

```text
cmake .
make
```
This will create the enumifier executable in bin directory

## Licensed under the [MIT License](LICENSE)

