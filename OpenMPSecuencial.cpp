#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

using namespace std;
int Intentos;

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
	
//Multiplicar matrices

void matmul(int **A, int **B, int **C, int n){
  int i,j,k;
  	for (i = 0; i < n; ++i) {
		for(j = 0; j < n; j++) {
			C[i][j] = 0; 
        		for(k = 0; k < n; k++) {
         	   		C[i][j] += A[i][k]*B[j][k]; 
       			}
    	}
    }
}
//Mostrar resultado

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
  int Intentos=(int)atoi(argv[2]);   
  int i, j;    
  srand(time(NULL));

  int **A, **B, **C, **D; 
  A = new int* [n], B = new int* [n], C = new int* [n], D = new int* [n];
  for(j=0; j<n; j++){
    A[j] = new int [n], B[j] = new int [n], C[j] = new int [n],  D[j] = new int [n];
  }

  //Lectura de matrices
  create_mat(A, n);
  create_mat(B, n); 
  struct timeval start;
  struct timeval end;
  double milisecs;
  long seconds, useconds;
  ofstream file;
  file.open("ResultadosSecuencial.txt",ios::app);
  file<<"Resultados para n="<<n<<endl;
  cout<<"Resultados para n="<<n<<endl;
  for(int i=0;i<Intentos;i++)
  {
	  gettimeofday(&start, 0);
	  //Realizar la multiplicacion
	  matmul(A, D, C, n); 
	  gettimeofday(&end, 0);
	  //Impresión de resultado
	  seconds  = end.tv_sec  - start.tv_sec;
	  useconds = end.tv_usec - start.tv_usec;
	  milisecs = ((seconds) * 1000 + useconds/1000.0);
	  cout << "Tardo: "<<milisecs/1000 <<" segundos "<<endl; 
	  file<<Convert(milisecs/1000)<<";\n";
  }
	file.close();
  delete [] A, B, C, D; 

  return 0;
}



