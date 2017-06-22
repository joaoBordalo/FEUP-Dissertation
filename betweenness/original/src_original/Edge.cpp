#include "Edge.h"

int Edge::GetInput()
{
	return input;
}

int Edge::GetOutput()
{
	return output;
}

void Edge::SetInput(int input)
{
	this->input = input;
}

void Edge::SetOutput(int output)
{
	this->output = output;
}

double Edge::GetWeight()
{
	return weight;
}

void Edge::SetWeight(double weight)
{
	this->weight = weight;
}

Edge::Edge(int input, int output, double weight)
{
	this->input = input;
	this->output = output;
	this->weight = weight;
}

Edge::~Edge()
{
	//cout << "Edge " << input << ", " << output << ", " << weight << " destroyed\n";
}
