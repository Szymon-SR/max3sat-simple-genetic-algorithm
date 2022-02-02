#include "Max3SatProblem.h"
#include <fstream>
#include <iostream>

void SignedNumber::takeString(const std::string number)
{
	isPositive = number[0] != '-';
	value = abs(stoi(number));
}

Max3SatProblem::~Max3SatProblem()
{
	for (int i = 0; i < static_cast <int>(inputNumbers.size()); i++)
	{
		delete inputNumbers[i];
	}
}

bool Max3SatProblem::load(const std::string& sourcePath)
{
	std::ifstream file(sourcePath);
	std::string line;

	if (file.good())
	{
		while (!file.eof())
		{
			getline(file, line);
			if (line[0] == '(')
			{
				std::string currentNumber;
				int numberInArray = 0;
				SignedNumber* currentArray = new SignedNumber[3];

				for (int i = 2; i < static_cast <int>(line.length()) - 1; i++)
				{
					if (line[i] == ' ')
					{
						// spacja - koniec zmiennej
						if (!currentNumber.empty())
						{
							currentArray[numberInArray].takeString(currentNumber);
							allVariables.insert(currentArray[numberInArray].getValue());

							numberInArray++;
							currentNumber = "";
						}
					}
					else if (line[i] == '-' || isdigit(line[i]))
					{
						// cyfra lub znak minus
						currentNumber += line[i];
					}
					else
					{
						// nieprawid³owe znaki, nie wczytujemy
						return false;
					}
				}
				inputNumbers.push_back(currentArray);
				numberOfClauses++;
			}
		}
		file.close();
		return true;
	}
	else
	{
		return false;
	}
}

int Max3SatProblem::compute(const bool* solution) const
{
	int numOfFullfilledClauses = 0;
	bool isCurrentClauseAdded = false;
	int j = 0;

	for (int i = 0; i < numberOfClauses; i++)
	{
		isCurrentClauseAdded = false;
		j = 0;

		while (j < MAX_CLAUSE_SIZE && !isCurrentClauseAdded)
		{
			if (inputNumbers.at(i)[j].getIsPositive() == solution[inputNumbers.at(i)[j].getValue()])
			{
				numOfFullfilledClauses++;
				isCurrentClauseAdded = true;
			}
			j++;
		}
	}
	return numOfFullfilledClauses;
}
