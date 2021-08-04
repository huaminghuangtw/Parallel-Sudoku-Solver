#ifndef HELPER_HPP
#define HELPER_HPP


#include <iomanip>
#include <sstream>
#include <string>


inline std::string operator* (const std::string& str, size_t times)
{
    std::stringstream stream;
    for (size_t i = 0; i < times; i++) stream << str;
    return stream.str();
}


#endif   // HELPER_HPP