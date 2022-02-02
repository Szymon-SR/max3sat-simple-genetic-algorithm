#pragma once

#include <string>
#include <vector>
#include <set>

const int MAX_CLAUSE_SIZE = 3;

class SignedNumber	// klasa powstala aby moc przechowac zmienna -0
{
public:
	SignedNumber() { value = 0; isPositive = false; }

	void takeString(const std::string number);
	int getValue() const { return value; }
	bool getIsPositive() const { return isPositive; }

private:
	int value;
	bool isPositive;
};

class Max3SatProblem
{
public:
	Max3SatProblem() { numberOfClauses = 0; };

	~Max3SatProblem();

	bool load(const std::string& sourcePath);
	int compute(const bool* solution) const;
	int getNumberOfVariables() const { return allVariables.size(); };
	int getNumberOfClauses() const { return numberOfClauses; };

private:
	std::vector<SignedNumber*> inputNumbers;
	std::set<int> allVariables;

	int numberOfClauses;
};
