#pragma once
#include <iostream>

using namespace std;

class Edge
{
private:
	int input;
	int output;
	double weight;
public:
	int GetInput();
	int GetOutput();
	void SetInput(int input);
	void SetOutput(int output);
	double GetWeight();
	void SetWeight(double weight);
	Edge(int input, int output, double weight);
	~Edge();
};

