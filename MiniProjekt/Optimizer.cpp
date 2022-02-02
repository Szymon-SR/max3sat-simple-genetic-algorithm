#include "Optimizer.h"
#include "Random.h"

Optimizer::~Optimizer()
{
	delete bestFound;
	clearPopulation();
}

void Optimizer::clearPopulation()
{
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		delete population[i];
	}
}

void Optimizer::initialize()
{
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		bool* newGenotype = new bool[problem->getNumberOfVariables()];

		for (int k = 0; k < problem->getNumberOfVariables(); k++)
		{
			newGenotype[k] = Random::generateRandomBool();
		}

		Individual* newIndividual = new Individual(newGenotype, problem->getNumberOfVariables());
		newIndividual->calculateFitness(problem->compute(newIndividual->getGenotype()), problem->getNumberOfClauses());
		population.push_back(newIndividual);
	}
	bestFound = new Individual(*population.at(0));
	findBestIndividual();
}

void Optimizer::runIteration()
{
	std::vector <Individual*> newPopulation;
	while (newPopulation.size() < population.size())
	{
		Individual* parent1 = population[pickParent()];
		Individual* parent2 = population[pickParent()];
		Individual* child1 = parent1->crossover(parent2, CROSSOVER_PROBABILITY);
		Individual* child2 = parent2->crossover(parent1, CROSSOVER_PROBABILITY);
		child1->mutation(MUTATION_FREQUENCY);
		child2->mutation(MUTATION_FREQUENCY);

		child1->calculateFitness(problem->compute(child1->getGenotype()), problem->getNumberOfClauses());
		child2->calculateFitness(problem->compute(child2->getGenotype()), problem->getNumberOfClauses());

		newPopulation.push_back(child1);
		newPopulation.push_back(child2);
	}

	clearPopulation();
	population = newPopulation;
	findBestIndividual();
}

void Optimizer::findBestIndividual()
{
	for (int i = 0; i < static_cast<int> (population.size()); i++)
	{
		if (population.at(i)->getFitness() > bestFound->getFitness())
		{
			delete bestFound;
			bestFound = new Individual(*population.at(i));
		}
	}
}

int Optimizer::pickParent() const
{
	int winnerIndex = Random::generateRandomInt(0, POPULATION_SIZE);

	for (int i = 0; i < TOURNAMENT_SIZE - 1; i++)
	{
		int pickedIndex = Random::generateRandomInt(0, POPULATION_SIZE);
		if (population[pickedIndex]->getFitness() > population[winnerIndex]->getFitness())
		{
			winnerIndex = pickedIndex;
		}
	}

	return winnerIndex;
}
