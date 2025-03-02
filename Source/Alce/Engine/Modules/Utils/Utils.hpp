#pragma once

#if defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
    #define COMPILED_IN_LINUX
#elif defined(__APPLE__) && defined(__MACH__)
    #define COMPILED_IN_MACOS
#elif defined(_WIN32) || defined(_WIN64)
    #define COMPILED_IN_WINDOWS
#endif

#include <stdlib.h>
#include <random>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <chrono>

#include "../FileSystem/FileSystem.hpp"
#include "../String/String.hpp"

namespace alce
{
    void Shell(std::string cmd);
    
    String OS();

    String GenerateUUID();

    String FormatString(String format, List<String> values);

    String ConcatString(List<String> strings, String join = "");

    template<typename T>
    List<T> MergeLists(List<List<T>> lists)
    {
        if(lists.Empty()) return {};

        List<T> result = lists.First();

        for(int i = 1; i < lists.Length(); i++)
        {
            result.Merge(lists[i]);
        }

        return result;
    }

}