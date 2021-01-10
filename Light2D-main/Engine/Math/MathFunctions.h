#pragma once
#include <random>
namespace Math
{
	int16_t RandomRange(int16_t min, int16_t max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(min, max);
		return distr(gen);
	}
}
