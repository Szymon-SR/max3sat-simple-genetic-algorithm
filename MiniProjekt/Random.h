#pragma once

#include <random>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

class Random
{
public:
	static double generateRandomDouble(double min, double max);
	static int generateRandomInt(int min, int max);
	static bool generateRandomBool();

private:
};
