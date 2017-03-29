#include "WeightedDirectedGraph.h"

WeightedDirectedGraph::WeightedDirectedGraph(int vertices)
{
	this->vertices = vertices;
	adj = new list<Edge*>[vertices];	//array of lists of adj vertices to vertex represented by index
}

int WeightedDirectedGraph::GetVertices()
{
	return vertices;
}

void WeightedDirectedGraph::AddEdge(Edge & edge)
{
	adj[edge.GetInput()].push_back(&edge);
}

void WeightedDirectedGraph::AddEdge(int input, int output, double weight)
{
	Edge *edge = new Edge(input, output, weight);
	adj[input].push_back(edge);
}

list<Edge*> WeightedDirectedGraph::GetAdjacentVertices(int vertex)
{
	return adj[vertex];
}

void WeightedDirectedGraph::ReverseEdges()
{
	//alter Edges and reallocate to new list
	list<Edge*> *adjNew = new list<Edge*>[vertices];
	for (size_t i = 0; i < vertices; i++)
	{
		while (!adj[i].empty())
		{
			Edge *edge = adj[i].front();

			int output = edge->GetOutput();
			edge->SetOutput(edge->GetInput());
			edge->SetInput(output);

			adj[i].pop_front();
			adjNew[output].push_back(edge);
		}
	}
	delete adj;		//delete reference on old list
	adj = adjNew;	//add reference to new list
}

double WeightedDirectedGraph::NormalizeWeights()
{
	double maxWeight = 0;
	for (size_t i = 0; i < vertices; i++)
	{
		for (list<Edge*>::iterator it = adj[i].begin(); it != adj[i].end(); it++)
		{
			Edge *adjEdge = *it;
			if (adjEdge->GetWeight() > maxWeight)
			{
				maxWeight = adjEdge->GetWeight();
			}
		}
	}

	for (size_t i = 0; i < vertices; i++)
	{
		for (list<Edge*>::iterator it = adj[i].begin(); it != adj[i].end(); it++)
		{
			Edge *adjEdge = *it;
			//adjEdge->SetWeight(adjEdge->GetWeight());
			//adjEdge->SetWeight(adjEdge->GetWeight() / maxWeight);
			adjEdge->SetWeight((adjEdge->GetWeight()/maxWeight)*1000 );
		}
	}

	return maxWeight;
}

void WeightedDirectedGraph::DenormalizeWeights(double denormalizeValue)
{
	double maxWeight = denormalizeValue;

	for (size_t i = 0; i < vertices; i++)
	{
		for (list<Edge*>::iterator it = adj[i].begin(); it != adj[i].end(); it++)
		{
			Edge *adjEdge = *it;
			adjEdge->SetWeight(adjEdge->GetWeight() * maxWeight);
		}
	}
}


WeightedDirectedGraph * WeightedDirectedGraph::ReadGraph(string fileName)
{
	WeightedDirectedGraph *graph = nullptr;
	ifstream file(fileName);
	string line;
	int c = 0;

	getline(file, line);
	int vertices;
	istringstream iss(line);
	iss >> vertices;
	graph = new WeightedDirectedGraph(vertices);

	while (getline(file, line))
	{
		istringstream iss(line);
		int v, w, weight;
		iss >> v >> w >> weight;
		graph->AddEdge(v, w, weight);
	}
	file.close();
	return graph;
}

void WeightedDirectedGraph::WriteGraph(string fileName, WeightedDirectedGraph * graph)
{
	ofstream file(fileName);
	file << graph->vertices << "\n";

	for (int v = 0; v < graph->vertices; v++)
	{
		for (auto * edge : graph->GetAdjacentVertices(v))
		{
			int w = edge->GetOutput();
			file << v << " " << w << " " << edge->GetWeight() << "\n";
		}
	}

	file.close();
}

WeightedDirectedGraph * WeightedDirectedGraph::GetSubGraph(int centerVertex, double distance)
{
	priority_queue<KeyValuePair, vector<KeyValuePair>, greater<KeyValuePair>> Q;
	stack<int> S;
	double *dist = new double[vertices];
	bool *isInStack = new bool[vertices];

	int s = centerVertex;
	//Single source shortest-paths problem
	{
		//Initialization
		{
			for (size_t i = 0; i < vertices; i++)
			{
				dist[i] = DBL_MAX;
				isInStack[i] = false;
			}
			dist[s] = 0;
			Q.push(KeyValuePair(dist[s], s));
		}

		while (!Q.empty())
		{
			KeyValuePair pair = Q.top();
			int v = pair.Value;
			Q.pop();

			//this part of code should replace updating in priority queue which is expensive
			if (isInStack[v] == false)	//is it good solution that when i get vertex from the priority queue that is best then all others same vertices will not be better later?
			{
				isInStack[v] = true;
				S.push(v); //problem => when queue contains duplicities? Can priority queue ensure that when i get specific vertex then i will not get that vertex again?

				list<Edge*> adjEdges = this->GetAdjacentVertices(v);
				for (list<Edge*>::iterator it = adjEdges.begin(); it != adjEdges.end(); it++)
				{
					Edge *adjEdge = *it;
					double edgeDistance = adjEdge->GetWeight();
					int w = adjEdge->GetOutput();

					//path discovery, shorter path found?
					if (dist[w] > dist[v] + edgeDistance)
					{
						dist[w] = dist[v] + edgeDistance;
						Q.push(KeyValuePair(dist[w], w));
					}
				}
			}
		}
	}

	unordered_set<int> inRangeVertices;
	for (int i = 0; i < vertices; i++)
	{
		if (dist[i] < distance)
		{
			inRangeVertices.insert(i);
		}
	}

	//normalize vertex numbers
	map<int, int> normalizedVertexPairs; //key is vertex id
	int normValue = 0;
	for (const auto& v : inRangeVertices)
	{
		normalizedVertexPairs.insert(make_pair(v, normValue));
		normValue++;
	}

	WeightedDirectedGraph *subGraph = new WeightedDirectedGraph(inRangeVertices.size());	//Id's are same
	for (const auto& v : inRangeVertices)
	{
		for (const auto& edge : this->GetAdjacentVertices(v))
		{
			int w = edge->GetOutput();
			if (inRangeVertices.count(w) > 0)//if w is also in range then create edge in subgraph
			{
				int normV = normalizedVertexPairs[v];
				int normW = normalizedVertexPairs[w];
				subGraph->AddEdge(normV, normW, edge->GetWeight());
			}
		}
	}

	return subGraph;
}

WeightedDirectedGraph::~WeightedDirectedGraph()
{
	for (size_t i = 0; i < vertices; i++)
	{
		while (!adj[i].empty())
		{
			delete adj[i].front();	//delete edge objects
			adj[i].pop_front();
		}
	}

	delete[] adj;	//delete array of lists
}
