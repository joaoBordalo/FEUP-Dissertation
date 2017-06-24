#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <fstream>

using namespace std;

double OnMultLineKremlin(int m_ar, int m_br,int x) 
{
	double Time1, Time2;
	int i, j, k;
	double *pha, *phb, *phc;

	//Matrixes Memory allocation
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	//Starting counting time
	Time1 = omp_get_wtime();

	//Loading matrix values
	for(i=0; i<m_ar; i++)
		#pragma omp parallel for num_threads (x)
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1,0;

	for(i=0; i<m_br; i++)
		#pragma omp parallel for num_threads (x)
		for(j=0; j<m_br; j++)
			phb[i*m_br + j] = (double)(i+1);

	for(i=0; i<m_ar; i++)
		#pragma omp parallel for num_threads (x)
		for(j=0; j<m_ar; j++)
			phc[i*m_ar + j] = (double)0.0;

	//Matrix Multiplication
	for(i=0; i<m_ar; i++)
	{	for( k=0; k<m_ar; k++)
		{	
			#pragma omp parallel for num_threads (x) 
			for( j=0; j<m_br; j++)
			{	
				phc[i*m_ar+j] += pha[i*m_ar+k] * phb[k*m_br+j]; 
			}
			
		}
	}

	//Stoping time
    Time2 = omp_get_wtime();

    //Freeing memory used for matrixes
    free(pha);
    free(phb);
    free(phc);

	return Time2 - Time1;  
}

double OnMultKremlin(int m_ar, int m_br,int x) 
{
	double Time1, Time2;
	double temp;
	int i, j, k;
	double *pha, *phb, *phc;
	
	//Matrixes Memory allocation	
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	//Starting counting time
	Time1 = omp_get_wtime();

	//Loading matrix values
	for(i=0; i<m_ar; i++)
		#pragma omp parallel for num_threads (x)
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1,0;

	for(i=0; i<m_br; i++)
		#pragma omp parallel for num_threads (x)
		for(j=0; j<m_br; j++)
			phb[i*m_br + j] = (double)(i+1);


	//Matrix Multiplication
	for(i=0; i<m_ar; i++)
	{	for( j=0; j<m_br; j++)
		{	temp = 0;
			#pragma omp parallel for reduction(+:temp) num_threads (x) 
			for( k=0; k<m_ar; k++)
			{	
				temp += pha[i*m_ar+k] * phb[k*m_br+j];
			}
			phc[i*m_ar+j]=temp;
		}
	}

	//Stoping time
    Time2 = omp_get_wtime();

    //Freeing memory used for matrixes
    free(pha);
    free(phb);
    free(phc);

	return Time2 - Time1;
}

double OnMultLineThreading(int m_ar, int m_br,int x) 
{
	double Time1, Time2;
	int i, j, k;
	double *pha, *phb, *phc;
	
	//Matrixes Memory allocation
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	//Starting counting time
	Time1 = omp_get_wtime();

	//Loading matrix values
	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1,0;

	for(i=0; i<m_br; i++)
		for(j=0; j<m_br; j++)
			phb[i*m_br + j] = (double)(i+1);

	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			phc[i*m_ar + j] = (double)0,0;


	//Matrix Multiplication
	for(i=0; i<m_ar; i++)
	{	for( k=0; k<m_ar; k++)
		{	
			#pragma omp parallel for num_threads (x) 
			for( j=0; j<m_br; j++)
			{	
				phc[i*m_ar+j] += pha[i*m_ar+k] * phb[k*m_br+j]; 
			}
			
		}
	}

	//Stoping time
    Time2 = omp_get_wtime();

    //Freeing memory used for matrixes
    free(pha);
    free(phb);
    free(phc);

	return Time2 - Time1; 
}

double OnMultThreading(int m_ar, int m_br,int x) 
{
	double Time1, Time2;
	double temp;
	int i, j, k;
	double *pha, *phb, *phc;

	//Matrixes Memory allocation
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	//Starting counting time
	Time1 = omp_get_wtime();

	//Loading matrix values
	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1,0;

	for(i=0; i<m_br; i++)
		for(j=0; j<m_br; j++)
			phb[i*m_br + j] = (double)(i+1);


	//Matrix Multiplication
	for(i=0; i<m_ar; i++)
	{	for( j=0; j<m_br; j++)
		{	temp = 0;
			#pragma omp parallel for reduction(+:temp) num_threads (x) 
			for( k=0; k<m_ar; k++)
			{	
				temp += pha[i*m_ar+k] * phb[k*m_br+j];
			}
			phc[i*m_ar+j]=temp;
		}
	}

	//Stoping time
    Time2 = omp_get_wtime();

    //Freeing memory used for matrixes
    free(pha);
    free(phb);
    free(phc);

	return Time2 - Time1;
}
 
double OnMult(int m_ar, int m_br) 
{
	double Time1, Time2;
	double temp;
	int i, j, k;
	double *pha, *phb, *phc;

	//Matrixes Memory allocation	
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	//Starting counting time
	Time1 = omp_get_wtime();

	//Loading matrix values
	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;

	for(i=0; i<m_br; i++)
		for(j=0; j<m_br; j++)
			phb[i*m_br + j] = (double)(i+1);


	//Matrix Multiplication
	for(i=0; i<m_ar; i++)
	{	for( j=0; j<m_br; j++)
		{	temp = 0;
			for( k=0; k<m_ar; k++)
			{	
				temp += pha[i*m_ar+k] * phb[k*m_br+j];
			}
			phc[i*m_ar+j]=temp;
		}
	}

	//Stoping time
	Time2 = omp_get_wtime();

	//Freeing memory used for matrixes
    free(pha);
    free(phb);
    free(phc);

	return Time2 - Time1;
}


double OnMultLine(int m_ar, int m_br)
{
    double Time1, Time2;
	double temp;
	int i, j, k;
	double *pha, *phb, *phc;
	
	//Matrixes Memory allocation	
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	//Starting counting time
	Time1 = omp_get_wtime();

	//Loading matrix values
	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;

	for(i=0; i<m_br; i++)
		for(j=0; j<m_br; j++)
			phb[i*m_br + j] = (double)(i+1);

	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			phc[i*m_ar + j] = (double)0.0;


	//Matrix Multiplication
	for(i=0; i<m_ar; i++)
	{	for( k=0; k<m_ar; k++)
		{	
			for( j=0; j<m_br; j++)
			{	
				phc[i*m_ar+j] += pha[i*m_ar+k] * phb[k*m_br+j]; 
			}
			
		}
	}

	//Stoping time
    Time2 = omp_get_wtime();

    //Freeing memory used for matrixes
    free(pha);
    free(phb);
    free(phc);
	
	return Time2 - Time1;;
}

void OutputToFile(int lin, int col, int inc, int limit)
{
	int i;
	double temp;
	ofstream myfile;
    myfile.open ("matrixMultResult.csv");
    myfile << "i,Algoritmo a,Algoritmo b\n";
	for(i=lin;i <= limit; i=i+inc)
	{
		temp=OnMult(i,i);
		myfile << i << "," << temp << ",";
		temp=OnMultLine(i,i);
		myfile << temp << "\n";
	}
	myfile.close();
}




float produtoInterno(float *v1, float *v2, int col)
{
	int i;
	float soma=0.0;	

	for(i=0; i<col; i++)
		soma += v1[i]*v2[i];
	
	return(soma);

}

int main (int argc, char *argv[])
{
	int lin, col, inc, limit;
	int x=stoi(argv[3]);
	int op = stoi(argv[1]);
	lin = col = stoi(argv[2]);
	
		switch (op){
			case 1: 
				cout << OnMult(lin, col)<< endl;
				break;
			case 2:
				cout << OnMultLine(lin, col)<<endl;
				break;
			case 3:
				OutputToFile(lin, col, inc, limit);
				break;
			case 4: 
				cout << OnMultThreading(lin, col,x)<< endl;
				break;
			case 5: 
				cout << OnMultLineThreading(lin, col,x)<< endl;
				break;
			case 6: 
				cout << OnMultKremlin(lin, col,x)<< endl;
				break;
			case 7: 
				cout << OnMultLineKremlin(lin, col,x)<< endl;
				break;
		}
	return 0;
}