#include "Betweenness.h"


Betweenness::Betweenness(WeightedDirectedGraph &graph)
{
	this->graph = &graph;
}

double * Betweenness::Calculate(int startVertex, int endVertex)
{
	int vertices = graph->GetVertices();
	double *betweenness = new double[vertices];

	for (size_t i = 0; i < vertices; i++)
	{
		betweenness[i] = 0;
	}

	priority_queue<KeyValuePair, vector<KeyValuePair>, greater<KeyValuePair>> Q;
	stack<int> S;
	double *dist = new double[vertices];
	vector<int> *Pred;
	double *sp = new double[vertices];
	double *delta = new double[vertices];
	bool *isInStack = new bool[vertices];

	for (int s = startVertex; s < endVertex; s++)
	{
		/*auto start_time = std::chrono::high_resolution_clock::now();*/

		//Single source shortest-paths problem
		{
			//Initialization
			{
				Pred = new vector<int>[vertices];
				for (int i = 0; i < vertices; i++)
				{
					dist[i] = DBL_MAX;
					sp[i] = 0;
					isInStack[i] = false;
				}
				dist[s] = 0;
				sp[s] = 1;
				Q.push(KeyValuePair(dist[s], s));
			}

			while (!Q.empty())
			{
				KeyValuePair pair = Q.top();
				int v = pair.Value;
				Q.pop();

				//this part of code should replace updating in priority queue which is expensive
				if (isInStack[v] == false)
				{
					isInStack[v] = true;
					S.push(v);


					vector<Edge*> adjEdges = graph->GetAdjacentVertices(v);
					for (vector<Edge*>::iterator it = adjEdges.begin(); it != adjEdges.end(); it++)
					{
						Edge *adjEdge = *it;
						double edgeDistance = adjEdge->GetWeight();
						int w = adjEdge->GetOutput();

						//path discovery, shorter path found?
						if (dist[w] > dist[v] + edgeDistance)
						{
							dist[w] = dist[v] + edgeDistance;
							Q.push(KeyValuePair(dist[w], w));
							sp[w] = 0;
							Pred[w].clear();
						}

						//path counting, edge(v,w) on a shortest path?
						if (Utils::AreEqual(dist[w], dist[v] + edgeDistance))
						{
							//sp[w] = sp[w] + edgeDistance*sp[v];
							sp[w] = sp[w] + sp[v];
							Pred[w].push_back(v);
						}
					}
				}
			}
		}

		//Accumulation
		{
			for (int v = 0; v < vertices; v++)
			{
				delta[v] = 0;
			}

			while (S.size() != 0)
			{
				int w = S.top();
				S.pop();

				for (vector<int>::iterator it = Pred[w].begin(); it != Pred[w].end(); it++)
				{
					int v = *it;
					//double before = delta[v];
					delta[v] = delta[v] + (sp[v] / sp[w] * (1 + delta[w]));
					//double after = delta[v];

					//if (after - before > 1)
					//{
					//	cout << "before: " << before << ", after: " << after << ", spv: " << sp[v] << ", spw: " << sp[w] << ", delta[w]: " << delta[w] << endl;
					//	getchar();
					//}
				}
				if (w != s)
				{
					betweenness[w] = betweenness[w] + delta[w];
				}
			}
		}

		/*for (size_t i = 0; i < vertices; i++)
		{
			if (betweenness[i] > 10000)
			{
				cout << betweenness[i] << endl;
			}
		}*/

		/*auto end_time = std::chrono::high_resolution_clock::now();
		auto time = end_time - start_time;
		std::cout << "Calculation for vertex " << s << " took " <<
			std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << " ms to run.\n";*/

		delete[] Pred;
	}


	delete[] dist;
	delete[] sp;
	delete[] delta;
	delete[] isInStack;
	return betweenness;
}


double * Betweenness::CalculateOpenMP(int startVertex, int endVertex, int threads)
{
	//Each thread is using serial version
	int vertices = graph->GetVertices();
	double *betweenness = new double[vertices];
	omp_lock_t *lockArray = new omp_lock_t[vertices];
	for (size_t i = 0; i < vertices; i++)
	{
		betweenness[i] = 0;
		omp_init_lock(&lockArray[i]);
	}

	#pragma omp parallel shared(betweenness, lockArray) num_threads(threads)
	{
		int vertices = endVertex - startVertex;
		int tid = omp_get_thread_num();
		//if (tid == 0)
		//{
			//cout << "Used threads: " << threads << endl;//
			//cout << "Vertices: " << graph->GetVertices() << endl;
		//}
				
		int size = (int)ceill((float)vertices / (float)threads);
		int start = tid * size;
		int end = start + size;
		if (tid == threads - 1)
		{
			end = vertices;
		}
		//cout << "Thread: " << tid << ", start: " << start << ", end: " << end << endl;

		//for low number of vertices if start is higher than max vertex id then this method will not modify betweenness
		double *subBetweenness = Calculate(start, end);
		
		for (int i = 0; i < graph->GetVertices(); i++) {
			omp_set_lock(&lockArray[i]);
			betweenness[i] = betweenness[i] + subBetweenness[i];
			omp_unset_lock(&lockArray[i]);
		}

		delete[] subBetweenness;
	}
	
	for (size_t i = 0; i < vertices; i++)
	{
		omp_destroy_lock(&lockArray[i]);
	}
	delete[] lockArray;

	return betweenness;
}

Betweenness::~Betweenness()
{
}
