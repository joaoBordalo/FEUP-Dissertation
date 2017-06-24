//#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
//#include <papi.h>
#include <fstream>
#include <chrono>

using namespace std;

#define SYSTEMTIME clock_t
/*
double OnMultLineThreading(int m_ar, int m_br,int x) 
{
	double Time1, Time2;
	
	char st[100];
	double temp;
	int i, j, k;

	double *pha, *phb, *phc;
	

		
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;



	for(i=0; i<m_br; i++)
		for(j=0; j<m_br; j++)
			phb[i*m_br + j] = (double)(i+1);

	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			phc[i*m_ar + j] = (double)0.0;



    Time1 = omp_get_wtime();

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


    Time2 = omp_get_wtime();
	//sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1));
	//cout << st;

	/*cout << "Result matrix: " << endl;
	for(i=0; i<min(10,m_ar); i++)
	{	for(j=0; j<min(10,m_br); j++)
			cout << phc[j] << " ";
	}
	cout << endl;*/
/*
    free(pha);
    free(phb);
    free(phc);
	return (double)(Time2 - Time1);
    
}*/
/*
double OnMultThreading(int m_ar, int m_br,int x) 
{
	
	double Time1, Time2;
	
	char st[100];
	double temp;
	int i, j, k;

	double *pha, *phb, *phc;
	

		
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;



	for(i=0; i<m_br; i++)
		for(j=0; j<m_br; j++)
			phb[i*m_br + j] = (double)(i+1);



    Time1 = omp_get_wtime();
	
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


    Time2 = omp_get_wtime();
	//sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1));
	//cout << st;

	/*cout << "Result matrix: " << endl;
	for(i=0; i<1; i++)
	{	for(j=0; j<min(10,m_br); j++)
			cout << phc[j] << " ";
	}
	cout << endl;*/
/*
    free(pha);
    free(phb);
    free(phc);
	return (double)(Time2 - Time1);
	
}*/
 
double OnMult(int m_ar, int m_br) 
{
	
	//double Time1, Time2;
	
	char st[100];
	double temp;
	int i, j, k;

	double *pha, *phb, *phc;
	

		
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;



	for(i=0; i<m_br; i++)
		for(j=0; j<m_br; j++)
			phb[i*m_br + j] = (double)(i+1);



    //Time1 = omp_get_wtime();
	auto Time1 = std::chrono::high_resolution_clock::now();
	
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


    //Time2 = omp_get_wtime();
	auto Time2 = std::chrono::high_resolution_clock::now();
	//sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1));
	//cout << st;

	/*cout << "Result matrix: " << endl;
	for(i=0; i<1; i++)
	{	for(j=0; j<min(10,m_br); j++)
			cout << phc[j] << " ";
	}
	cout << endl;*/

    free(pha);
    free(phb);
    free(phc);
	auto time = Time2-Time1;
	return (double) std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
	
}


double OnMultLine(int m_ar, int m_br)
{
    //double Time1, Time2;
	
	char st[100];
	double temp;
	int i, j, k;

	double *pha, *phb, *phc;
	

		
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;



	for(i=0; i<m_br; i++)
		for(j=0; j<m_br; j++)
			phb[i*m_br + j] = (double)(i+1);

	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			phc[i*m_ar + j] = (double)0.0;



    //Time1 = omp_get_wtime();
	auto Time1 = std::chrono::high_resolution_clock::now();

	for(i=0; i<m_ar; i++)
	{	for( k=0; k<m_ar; k++)
		{	
			for( j=0; j<m_br; j++)
			{	
				phc[i*m_ar+j] += pha[i*m_ar+k] * phb[k*m_br+j]; 
			}
			
		}
	}


    //Time2 = omp_get_wtime();
	auto Time2 = std::chrono::high_resolution_clock::now();
	//sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1));
	//cout << st;

	/*cout << "Result matrix: " << endl;
	for(i=0; i<min(10,m_ar); i++)
	{	for(j=0; j<min(10,m_br); j++)
			cout << phc[j] << " ";
	}
	cout << endl;*/

    free(pha);
    free(phb);
    free(phc);
	auto time = Time2-Time1;
	return (double) std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
    
}

void OutputToFile(int lin, int col, int inc, int limit/*, char* filename*/)
{
	int i;
	double temp;
	ofstream myfile;
    myfile.open (/*filename*/"matrixMultResult.csv");
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
/*)
void handle_error (int retval)
{
  printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
  exit(1);
}

void init_papi() {
  int retval = PAPI_library_init(PAPI_VER_CURRENT);
  if (retval != PAPI_VER_CURRENT && retval < 0) {
    printf("PAPI library version mismatch!\n");
    exit(1);
  }
  if (retval < 0) handle_error(retval);

  std::cout << "PAPI Version Number: MAJOR: " << PAPI_VERSION_MAJOR(retval)
            << " MINOR: " << PAPI_VERSION_MINOR(retval)
            << " REVISION: " << PAPI_VERSION_REVISION(retval) << "\n";
}*/


int main (int argc, char *argv[])
{

	char c;
	int lin, col, nt=1, inc, limit,x;
	int op;
	char* filename;
	//int EventSet = PAPI_NULL;
  	long long values[2];
  	int ret;
	/*
	cout << "Numero de processadores: " << omp_get_num_procs() << endl;
	ret = PAPI_library_init( PAPI_VER_CURRENT );
	if ( ret != PAPI_VER_CURRENT )
		std::cout << "FAIL" << endl;


	ret = PAPI_create_eventset(&EventSet);
		if (ret != PAPI_OK) cout << "ERRO: create eventset" << endl;


	ret = PAPI_add_event(EventSet,PAPI_L1_DCM);
	if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_DCM" << endl;


	ret = PAPI_add_event(EventSet,PAPI_L2_DCM);
	if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_DCM" << endl;
	
	*/

	
	op=1;
	do {
		cout << endl;
		cout << "1. Multiplication" << endl;
		cout << "2. Line Multiplication" << endl;
		cout << "3. outputToFile" << endl;
		cout << "4. multithreading on Multiplication" << endl;
		cout << "5. multithreading on LineMultiplication" << endl;
		cout << "Selection?: ";
		
		cin >>op;
		if (op == 0)
			break;
			
		printf("Dimensions: lins cols ? ");
   		cin >> lin >> col;
   		
   		
		if(op == 3)
		{
			printf("Dimensional increment: inc ? ");
			cin >> inc;
			printf("Limit: limit ? ");
			cin >> limit;
			/*printf("outputFile: filename.csv (must be an existing file) ? ");
			cin >> filename;*/
		}
		/*if(op == 4 || op == 5)
		{
			printf("Number of threads: x");
			cin >> x;
		}*/
		

		// Start counting
		/*ret = PAPI_start(EventSet);
		if (ret != PAPI_OK) cout << "ERRO: Start PAPI" << endl;
*/
		switch (op){
			case 1: 
				cout << OnMult(lin, col)<< endl;
				break;
			case 2:
				cout << OnMultLine(lin, col)<<endl;
				break;
			case 3:
				OutputToFile(lin, col, inc, limit/*, filename*/);
				break;
			/*case 4: 
				cout << OnMultThreading(lin, col,x)<< endl;
				break;
			case 5: 
				cout << OnMultLineThreading(lin, col,x)<< endl;
				break;*/
		}

  		/*ret = PAPI_stop(EventSet, values);
  		if (ret != PAPI_OK) cout << "ERRO: Stop PAPI" << endl;
  		printf("L1 DCM: %lld \n",values[0]);
  		printf("L2 DCM: %lld \n",values[1]);
		ret = PAPI_reset( EventSet );
		if ( ret != PAPI_OK )
			std::cout << "FAIL reset" << endl; */



	}while (op != 0);
/*
		ret = PAPI_remove_event( EventSet, PAPI_L1_DCM );
		if ( ret != PAPI_OK )
			std::cout << "FAIL remove event" << endl; 

		ret = PAPI_remove_event( EventSet, PAPI_L2_DCM );
		

		ret = PAPI_destroy_eventset( &EventSet );
		if ( ret != PAPI_OK )
			std::cout << "FAIL destroy" << endl;
		*/

}
