#include <string>
#include <iostream>
#include <thread>

#include "Max3SatProblem.h"
#include "Optimizer.h"
#include "Individual.h"
#include "Random.h"


int main()
{

    Max3SatProblem problem;

    if (problem.load("max3sat/100/m3s_100_0.txt"))
    {
        Optimizer optimizer(&problem);
        optimizer.initialize();

        for (int i = 0; i < 10000; i++)
        {
            optimizer.runIteration();
            std::cout << "Jakosc najlepszego osobnika: ";
            std::cout << optimizer.getBestFound()->getFitness() << "\n";
        }
    }
    else
    {
        std::cout << "Plik nie zaladowany prawidlowo.";
    }
}
