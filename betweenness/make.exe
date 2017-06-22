all: BetweennessO BetweennessO2 

BetweennessO:
	g++ BetweennessO main.cpp Betweenness.cpp Betweenness.h Edge.cpp Edge.h KeyValuePair.cpp KeyValuePair.h Utils.cpp Utils.h WeightDirectedGraph.cpp WeightDirectedGraph.h -fopenmp -std=c++11 -o teste.out

BetweennessO2:
	g++ BetweennessO2 -fopenmp -std=c++11 -o2 teste.out

clean:
	rm -r BetweennessO BetweennessO2

opc1:
	for t in 0 1 ; do \
			for n in 50; do \
				./teste.out -f graph_czech.csv  -v $$s -s 1 -e $$n; \
			done; \
		done; \