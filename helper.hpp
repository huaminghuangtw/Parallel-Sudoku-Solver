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


#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define BAR_WIDTH 70


inline void printProgressBar1(double percentage)
{
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * BAR_WIDTH);
    int rpad = BAR_WIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

inline void printProgressBar2(double percentage)
{
	std::cout << "[";

	int pos = BAR_WIDTH * percentage;
	for (int i = 0; i < BAR_WIDTH; ++i)
	{
		if (i < pos) std::cout << "=";
		else if (i == pos) std::cout << ">";
		else std::cout << " ";
	}
	std::cout << "] " << int(percentage * 100.0) << " %\r";
	std::cout.flush();
}


#endif   // HELPER_HPP