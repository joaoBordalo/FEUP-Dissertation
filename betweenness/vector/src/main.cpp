#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <queue>
#include "KeyValuePair.h"
#include "WeightedDirectedGraph.h"
#include "Betweenness.h"
#include <chrono>	//for time
#include <cfloat>
#include <cstring>

#include <fstream>
#include <iostream>
#include <sstream>

double RandBetween(double minIncluseive, double maxInclusive) {
	double val = rand() / RAND_MAX;
	double range = maxInclusive - minIncluseive;	//with +1 to max => exclusive, but take care of overflow
	return (val * range) + minIncluseive;
}

void PrintUsage() 
{
	cout << endl;
	cout << "Help for betweenness algorithm parameters" << endl;
	cout << "Usage: ./betweenness.exe -f <file> -v <version> -s <start> -e <end> -t <threads> " << endl;

	cout << "Where:" << endl;
	cout << " <file>: \tFile with graph in .csv format" << endl;
	cout << " <version>: \t0 is serial[default], 1 is OpenMP version" << endl;
	cout << " <start>: \tFrom which vertex id calculate betweenness [default=0]" << endl;
	cout << " <end>: \tTo which vertex id calculate [default=last vertex of graph]" << endl;
	cout << " <threads>: \tUsed threads by parallel version" << endl;
	cout << endl;
}

void WriteResult(double * bw, int vertices) 
{
	ofstream file("result_betweenness.csv");

	for (int v = 0; v < vertices; v++)
	{
		file << v << " " << bw[v] << "\n";
	}

	file.close();
}

int main(int argc, char* argv[])
{
	string fileName = "graph_facebook.csv";
	int threads = omp_get_max_threads();
	int version = 0;	//0=serial, 1=openmp
	int startVertex = 0;
	int endVertex = 0;
	
	for (size_t i = 1; i < argc; i++)
	{
		string argument = string(argv[i]);
		if (argument == "-h" || argument == "-help" || argument == "--help")
		{
			PrintUsage();
			exit(0);
		}
		else
		{
			if (i + 1 == argc)
			{
				PrintUsage();
				exit(0);
			}
			
			if (argument == "-v")//version
			{
				version = atoi(argv[i + 1]);
			}
			else if (argument == "-f")//file path with graph
			{
				fileName = argv[i + 1];
			}
			else if (argument == "-s")//start vertex
			{
				startVertex = atoi(argv[i + 1]);
			}
			else if (argument == "-e")//end vertex
			{
				endVertex = atoi(argv[i + 1]);
			}
			else if (argument == "-t")//number of used threads
			{
				threads = atoi(argv[i + 1]);
			}
			i++;
		}
	}

	WeightedDirectedGraph *graph = WeightedDirectedGraph::ReadGraph(fileName);
	graph->NormalizeWeights();
	/*WeightedDirectedGraph *graphTest = graph->GetSubGraph(0, 7);
	WeightedDirectedGraph::WriteGraph("testGraph4", graphTest);*/

	if (startVertex < 0 || startVertex > graph->GetVertices())
	{
		startVertex = 0;
	}

	if (endVertex <= 0 || endVertex > graph->GetVertices())
	{
		endVertex = graph->GetVertices();
	}
	Betweenness *bb = new Betweenness(*graph);

	auto start_time = std::chrono::high_resolution_clock::now();
	double *ar;
	if (version == 0)
	{
		ar = bb->Calculate(startVertex, endVertex);
	}
	else
	{
		ar = bb->CalculateOpenMP(startVertex, endVertex, threads);
	}
	
	auto end_time = std::chrono::high_resolution_clock::now();
	auto time = end_time - start_time;
	std::cout << "Betweenness took " <<
		std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << " ms to run.\n";

	delete graph;
	if (ar != nullptr)
	{
		WriteResult(ar, graph->GetVertices());
		delete ar;
	}
	delete bb;

	return 0;
}