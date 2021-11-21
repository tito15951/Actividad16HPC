#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>

using namespace std;
int Hilos;

string Convert (float number){
    std::ostringstream buff;
    buff<<number;
    return buff.str();}

//Crear una matriz aleatorio
void create_mat(int **A, int n){
  int i,j;
  for(i = 0; i < n; i++){
      for(j = 0; j < n; j++){
       A[i][j] = rand() % 9; 
      }
   }
}

//Transpuesta

void transponer(int **D, int **B, int n) {
int i, j ; 
  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++){
      D[j][i] = B[i][j]; 
    }
  }
}
void matmulTraspuesta(int **A, int **B, int **C, int n){
  	omp_set_num_threads(Hilos);
	int ICol,FCol,i,j,k;
  	#pragma omp parallel shared(A,B,C) private(ICol,FCol,i,j,k)
  	{
	  	FCol=n/Hilos*(omp_get_thread_num()+1);
	  	ICol=n/Hilos*omp_get_thread_num();	
	  	for (i=ICol; i < FCol; i++) {
			for(j = 0; j < n; j++) {
				C[i][j] = 0; 
	        		for(k = 0; k < n; k++) {
	         	   		C[i][j] += A[i][k]*B[j][k]; 
	       			}
	    	}
	    }
	}
}
	
//Multiplicar matrices
void matmul(int **A, int **B, int **C, int n){
  	omp_set_num_threads(Hilos);
	int ICol,FCol,i,j,k;
  	#pragma omp parallel shared(A,B,C) private(ICol,FCol,i,j,k)
  	{
	  	FCol=n/Hilos*(omp_get_thread_num()+1);
	  	ICol=n/Hilos*omp_get_thread_num();	
	  	for (i=ICol; i < FCol; i++) {
			for(j = 0; j < n; j++) {
				C[i][j] = 0; 
	        		for(k = 0; k < n; k++) {
	         	   		C[i][j] += A[i][k]*B[k][j]; 
	       			}
	    	}
	    }
	}
}
void print_result(int **A, int n){
  int i,j;
  for(i = 0; i < n; i++){
      for(j = 0; j < n; j++){ 
         cout << A[i][j] << " ";
       }
      cout << endl;
   }
  cout << endl; 
}


int main(int argc, char* argv[]){
  int n=(int)atoi(argv[1]);   
  int Intentos=(int)atoi(argv[3]);   
  Hilos=(int)atoi(argv[2]);    
  srand(time(NULL));
  int **A, **B, **C, **D; 
  A = new int* [n], B = new int* [n], C = new int* [n], D = new int* [n];
  for(int j=0; j<n; j++){
    A[j] = new int [n], B[j] = new int [n], C[j] = new int [n],  D[j] = new int [n];
  }
  create_mat(A, n);
  create_mat(B, n);
  transponer(D,B,n);
  struct timeval start;
  struct timeval end;
  double milisecs;
  long seconds, useconds;
  ofstream fileSin,fileCon;
  fileSin.open("ResultadosParalelizadoSin.txt",ios::app);
  fileCon.open("ResultadosParalelizadoCon.txt",ios::app);
  fileSin<<"Resultados para n="<<n<<" con "<<Hilos<< " hilos sin trasponer:\n"<<endl;
  cout<<"Resultados para n="<<n<<" con "<<Hilos<< " hilos sin trasponer:"<<endl;
  for(int i=0;i<Intentos;i++)
  {
  		gettimeofday(&start, 0);
	  	matmul(A, B, C, n); 
	  	gettimeofday(&end, 0);	
	  	seconds  = end.tv_sec  - start.tv_sec;
	  	useconds = end.tv_usec - start.tv_usec;
	  	milisecs = ((seconds) * 1000 + useconds/1000.0);
	  	cout << "Para n="<<n <<", con "<<Hilos<<" hilos tarda: "<<milisecs/1000<<" segundos"<<endl; 
	  	fileSin<<Convert(milisecs/1000)<<";\n";
	  	//print_result(C,n);
  }
  //Mutiplicacion transpuesta
  cout<<endl<<"Resultados para n="<<n<<" con "<<Hilos<< " hilos con trasponer:\n"<<endl;
  fileCon<<"Resultados para n="<<n<<" con "<<Hilos<< " hilos con trasponer:"<<endl;
  for(int i=0;i<Intentos;i++)
  {
  		gettimeofday(&start, 0);
	  	matmulTraspuesta(A, D, C, n); 
	  	gettimeofday(&end, 0);	
	  	seconds  = end.tv_sec  - start.tv_sec;
	  	useconds = end.tv_usec - start.tv_usec;
	  	milisecs = ((seconds) * 1000 + useconds/1000.0);
	  	cout << "Para n="<<n <<", con "<<Hilos<<" hilos tarda: "<<milisecs/1000<<" segundos"<<endl; 
	  	fileCon<<Convert(milisecs/1000)<<";\n";
	  	//print_result(C,n);
  }
  fileSin.close();
  fileCon.close();
  delete [] A, B, C, D; 
  return 0;
}



