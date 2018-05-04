#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#include<string.h>
#include<math.h>


int nproc,rank;
FILE * arch_verificacion;


int main(){
MPI_Init(NULL,NULL);
	MPI_Comm_size( MPI_COMM_WORLD, &nproc );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank);
if(rank==0){
	
	
	system("gcc UNIVERSO_DATOS_gas.c -lm -o datos");
	system("./datos");
	
}

else if(rank==1)
{
system("g++ UNIVERSO_GRAFICA_gas.cpp -lGL -lGLU -lglut -lm -lfreeimage -o grafica");
do{
arch_verificacion=fopen("1.dat","r+t");
}while(arch_verificacion==NULL);

system("./grafica");
}
MPI_Finalize();
return 0;
}


