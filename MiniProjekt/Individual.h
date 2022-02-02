#pragma once

#include "Max3SatProblem.h"

class Individual
{
public:
	Individual(bool* newGenotype, int newGenotypeSize) { genotype = newGenotype; genotypeSize = newGenotypeSize; fitness = 0.0; };
	Individual(const Individual& other);

	~Individual() { delete[] genotype; };

	void calculateFitness(int computed, int numberOfClauses);
	Individual* crossover(const Individual* other, double crossoverProbability) const;
	void mutation(double mutationProbability);
	double getFitness() const { return fitness; };
	bool* getGenotype() const { return genotype; };

private:
	bool* genotype;
	int genotypeSize;
	double fitness;
};