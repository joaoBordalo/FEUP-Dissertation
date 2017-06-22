all: MATRIXMUL MATRIXMULOPENMP MATRIXMULKREMLIN allresults

allresults: original printblock openmp printblock kremlin

original: printversion12 matrixmuloriginal

openmp: printversion45 matrixmulopenmp

kremlin: printversion67 matrixmulkremlin

MATRIXMUL:
	g++ matrixmul.cpp -fopenmp -std=c++11 -o matrixMulOriginal

MATRIXMULOPENMP:
	g++ matrixmul.cpp -fopenmp -std=c++11 -o matrixMulOpenmp

MATRIXMULKREMLIN:
	g++ matrixmul.cpp -fopenmp -std=c++11 -o matrixMulKremlin

clean:
	rm -r matrixmul matrixmulopenmp matrixmulkremlin

printversion12:
	@echo "\t\t------Version Mul and Muline------\n"

matrixmuloriginal:
	for version in 1 2; do \
		for length in 1000 2000 3000 4000; do \
			./matrixMulOriginal $$version $$length 0 >> original.txt; \
		done; \
	done; \


printblock:
	@echo "\t****************************************************\n\t****************************************************\n"

printversion45:
	@echo "\t\t------Version Mul and Muline OpenMP------\n"

matrixmulopenmp:
	for version in 4 5; do \
		for thread in 1 2 3 4 5 6 7 8; do \
			for length in 1000 2000 3000 4000; do \
				./matrixMulOpenmp $$version $$length $$thread >> openmp.txt; \
			done; \
		done; \
	done; \

printversion67:
	@echo "\t\t------Version Mul and Muline Kremlin------\n"


matrixmulkremlin:
	for version in 6 7; do \
		for thread in 1 2 3 4 5 6 7 8; do \
			for length in 1000 2000 3000 4000; do \
				./matrixMulKremlin $$version $$length $$thread >> kremlin.txt; \
			done; \
		done; \
	done; \