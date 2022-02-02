#pragma once

#include <vector>
#include <random>
#include <string>
#include <iostream>

#include "Individual.h"
#include "Max3SatProblem.h"

const double CROSSOVER_PROBABILITY = 0.6;
const double MUTATION_FREQUENCY = 0.025;

const int POPULATION_SIZE = 15;
const int TOURNAMENT_SIZE = 3;

class Optimizer
{
public:
	explicit Optimizer(Max3SatProblem* newProblem) { problem = newProblem; bestFound = nullptr; };

	~Optimizer();

	void clearPopulation();
	void initialize();
	void runIteration();
	void findBestIndividual();
	int pickParent() const;
	Individual* getBestFound() const { return bestFound; };

private:
	std::vector<Individual*> population;
	Individual* bestFound;
	Max3SatProblem* problem;
};
