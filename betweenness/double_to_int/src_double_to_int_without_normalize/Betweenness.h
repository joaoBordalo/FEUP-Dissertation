#pragma once
#include "KeyValuePair.h"
#include "WeightedDirectedGraph.h"
#include "Utils.h"
#include <stdlib.h>
#include <queue>
#include <stack>
#include <list>
#include <iostream>
#include <omp.h>
#include <chrono>
#include <cfloat>
#include <climits>
#include <functional> //greater

class Betweenness
{
private:
	WeightedDirectedGraph *graph;
public:
	Betweenness(WeightedDirectedGraph &graph);
	//Serial version of betweenness
	int* Calculate(int startVertex, int endVertex);
	//OpenMP version of betweenness
	int* CalculateOpenMP(int startVertex, int endVertex, int threads);
	~Betweenness();
};

