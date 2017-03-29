#pragma once
#include <list>
#include <stdlib.h>
#include "Edge.h"
#include <unordered_set>
#include <map>
#include <queue>
#include <stack>
#include "KeyValuePair.h"
#include <cfloat>
#include <cstring>
#include <functional>
#include <vector>

#include <fstream>
#include <iostream>
#include <sstream>

class WeightedDirectedGraph
{
private:
	vector<Edge*> *adj;
	int vertices;
public:
	WeightedDirectedGraph(int vertices);

	int GetVertices();
	void AddEdge(Edge & edge);
	void AddEdge(int input, int output, double weight);

	//returns list of edges for a given vertex
	vector<Edge*> GetAdjacentVertices(int vertex);
	void ReverseEdges();

	//normalizes weights of edges in graph to <0,1> and returns denormalizeValue
	double NormalizeWeights();
	void DenormalizeWeights(double denormalizeValue);

	//this method returns subgraph with vertices around centerVertex that are accessible in path of distance length
	WeightedDirectedGraph * GetSubGraph(int centerVertex, double distance);

	//Returns graph object loaded from file
	static WeightedDirectedGraph * ReadGraph(string fileName);
	
	//Writes given graph to file
	static void WriteGraph(string fileName, WeightedDirectedGraph * graph);
	
	~WeightedDirectedGraph();
};

