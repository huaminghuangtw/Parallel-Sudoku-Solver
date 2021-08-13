#ifndef HELPER_HPP
#define HELPER_HPP


// =========================================================================


#include <iomanip>
#include <sstream>
#include <string>


inline std::string operator* (const std::string& str, size_t times)
{
    std::stringstream stream;
    for (size_t i = 0; i < times; i++) stream << str;
    return stream.str();
}


// =========================================================================


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


// =========================================================================


#include <random>
#include <iterator>


// Randomly select an element from a container
// source: https://gist.github.com/cbsmith/5538174
template <typename RandomGenerator = std::default_random_engine>
struct random_selector
{
	// On most platforms, you probably want to use std::random_device("/dev/urandom")()
	random_selector(RandomGenerator g = RandomGenerator(std::random_device()()))
		: gen(g)
	{ }

	template <typename Iter>
	Iter select(Iter start, Iter end)
	{
		std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
		std::advance(start, dis(gen));
		return start;
	}

	// convenience function
	template <typename Iter>
	Iter operator() (Iter start, Iter end)
	{
		return select(start, end);
	}

	// convenience function that works on anything with a sensible begin() and end(),
	// and returns with a ref to the value type
	template <typename Container>
	auto operator() (const Container& c) -> decltype(*begin(c))&
	{
		return *select(begin(c), end(c));
	}

private:
	RandomGenerator gen;
};


// =========================================================================


#endif   // HELPER_HPP