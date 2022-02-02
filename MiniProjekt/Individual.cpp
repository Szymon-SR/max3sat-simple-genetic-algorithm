#include "Individual.h"
#include "Random.h"


Individual::Individual(const Individual& other)
{
	genotypeSize = other.genotypeSize;
	fitness = other.fitness;
	genotype = new bool[genotypeSize];

	for (int i = 0; i < genotypeSize; i++)
	{
		genotype[i] = other.genotype[i];
	}
}

void Individual::calculateFitness(int computed, int numberOfClauses)
{
	this->fitness = static_cast<double> (computed) / static_cast<double> (numberOfClauses);
}

Individual* Individual::crossover(const Individual* other, double crossoverProbability) const
{
	if (Random::generateRandomDouble(0.0, 1.0) < crossoverProbability)
	{
		// podjecie decyzji o dokonaniu krzyzowania
		int crossPoint = (Random::generateRandomInt(0, this->genotypeSize));
		bool* genotypeAfterCrossover = new bool[this->genotypeSize];

		for (int i = 0; i < crossPoint; i++)
		{
			genotypeAfterCrossover[i] = this->genotype[i];
		}
		for (int i = crossPoint; i < this->genotypeSize; i++)
		{
			genotypeAfterCrossover[i] = other->genotype[i];
		}

		return new Individual(genotypeAfterCrossover, this->genotypeSize);
	}
	else
	{
		// podjecie decyzji o nie dokonywaniu krzyzowania, tworzona jest kopia rodzica
		return new Individual(*this);
	}
}

void Individual::mutation(double mutationFrequency)
{
	// losujemy liczbe zmiennych ktore ulegna zmianie z 1 na 0 i na odwrot
	int numToMutate = Random::generateRandomInt(0, static_cast<int> (genotypeSize * mutationFrequency + 1));

	for (int i = 0; i < numToMutate; i++)
	{
		int indexToSwap = Random::generateRandomInt(0, genotypeSize);
		genotype[indexToSwap] = !genotype[indexToSwap];
	}
}
