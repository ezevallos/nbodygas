#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>
#define N 20
#define RADIO 9.0
// GENERACION DE LA DATA DEL GAS IDEAL !!!
/* GRUPO LOS TUCANES:
1)KATIA SUSAN COTAQUISPE MENDOZA
2)ENRIQUE ZEVALLOS LABARTHE
3)FRANCO NAJARRO MALLQUI
4)LUIS TRUJILLO VERA
5)NOE TAZA
typedef struct Particula
{
  double pos[N][3];
  double vel[N][3];
  double m[N];

} Particula;

//OPERACIONES CON VECTORES EN R3

void mostrar_vector(double*vector,char* nombre){
int i=0;
for(i=0;i<3;i++)
printf("%s[%d] = %lf\n",nombre,i,vector[i]);
printf("\n");
}

double * suma(double * vector1 , double * vector2){
double* result_suma=(double*)malloc(sizeof(double)*3);
int i=0;
for(i=0;i<3;i++)
result_suma[i]=vector1[i]+vector2[i];
return result_suma;
}

double * resta(double * vector1 , double * vector2){
double* result_resta=(double*)malloc(sizeof(double)*3);
int i=0;
for(i=0;i<3;i++)
result_resta[i]=vector1[i]-vector2[i];
return result_resta;
}
double * multiplicacion_escalar(double * vector1 , double escalar){
double* result=(double*)malloc(sizeof(double)*3);
int i=0;
for(i=0;i<3;i++)
result[i]=vector1[i]*escalar;
return result;
}

double producto_punto(double* vector1, double* vector2){
double result=0;
int i=0;
for(i=0;i<3;i++)
result=result + vector1[i]*vector2[i];
return result;
}

double modulo_vector(double* vector){
double modulo=0;
int i=0;
for(i=0;i<3;i++)
modulo=modulo + vector[i]*vector[i];
return pow(modulo,0.5);
}

double* componente_paralela(double*vector , double*vector_ref){
return multiplicacion_escalar( vector_ref,producto_punto(vector,vector_ref)/pow(modulo_vector(vector_ref),2.0) );
}

double* componente_perpendicular(double*vector , double*vector_ref){
return resta( vector ,multiplicacion_escalar( vector_ref,producto_punto(vector,vector_ref)/pow(modulo_vector(vector_ref),2.0) ));
}



void init(Particula* gas)
{
    int i,j;
    time_t t;
    srand(time(&t));

    for(j=0;j<N;j++)
    {
      
	for(i=0;i<3;i++)
        {
         gas->pos[j][i]=((double)rand()/RAND_MAX)*(200.0-2.0*RADIO)-100.0+RADIO;
         gas->vel[j][i]=((double)rand()/RAND_MAX)*(100.0) + 300.0;
        }
	gas->m[j]=(double)0.000000001;
    }


}
void choque(double* vel1 , double* vel2,double* pos1,double *pos2 ){
double * vel1_parall, * vel1_perp;
double * vel2_parall, * vel2_perp;
vel1_parall=componente_paralela(vel1,resta(pos2,pos1) );
vel1_perp=componente_perpendicular(vel1,resta(pos2,pos1) );
vel2_parall=componente_paralela(vel2,resta(pos1,pos2) );
vel2_perp=componente_perpendicular(vel2,resta(pos1,pos2) );
double* vel1_aux=suma(vel1_perp,vel2_parall);
double* vel2_aux=suma(vel2_perp,vel1_parall);
int i=0;
for(i=0;i<3;i++){
vel1[i]=vel1_aux[i];
vel2[i]=vel2_aux[i];
}
}//END CHOQUE !!!!

void force(int n,double pos[N][3],double vel[N][3],double m[N],double dt,int num_archivo)
{
    int i,j;
    double r_x,r_y,r_z,d,a_x,a_y,a_z;
char name_arch[20];
memset(name_arch,0,20);
sprintf(name_arch,"%d.dat",num_archivo);//ARCHIVOS DE  SALIDA PARA LA GRAFICA DE LAS N-PARTICULAS EN EL ESPACIO CUBICO !!!
FILE*arch=fopen(name_arch,"a+t");

    for(i=0;i<n;i++)
    {
	
	//int detector=0;
        //for(j=0;(j<n) && (!detector);j++)
	for(j=i+1;(j<n);j++)
        {
		if( (modulo_vector(resta(pos[j],pos[i]) )<=2.0*RADIO) ) {
			choque(vel[i],vel[j],pos[i],pos[j]);			
			//detector=1;
		}
        }
       
	//aqui verificamos si hubo un choque con las paredes !!!
	
	
// HACE FALTA UN DETECTOR DE CHOQUES DE LAS PARTICULAS DEL GAS !!!
}

for(i=0;i<n;i++){

	if( ( (pos[i][0]>=(100.0-RADIO)) || (pos[i][0]<=(-100.0+RADIO)) ) && ((pos[i][1]<=(100.0-RADIO)) && (pos[i][1]>=(-100.0+RADIO)) ) && ( (pos[i][2]<=(100.0-RADIO)) && (pos[i][2]>=(-100.0+RADIO))))

//if(pos[0][i]<=-100)
		  vel[i][0] =(-1.0)*vel[i][0];
	if(( (pos[i][1]>=(100.0-RADIO)) || (pos[i][1]<=(-100.0+RADIO)) ) && ((pos[i][0]<=(100.0-RADIO)) && (pos[i][0]>=(-100.0+RADIO))) && ((pos[i][2]<=(100.0-RADIO)) && (pos[i][2]>=(-100.0+RADIO))))
		  vel[i][1] =(-1.0)*vel[i][1];
	if( ((pos[i][2]>=(100.0-RADIO)) || (pos[i][2]<=(-100.0+RADIO))) &&  ((pos[i][1]<=(100.0-RADIO)) && (pos[i][1]>=(-100.0+RADIO))) && ((pos[i][0]<=(100.0-RADIO)) && (pos[i][0]>=(-100.0+RADIO))) )
		  vel[i][2] =(-1.0)*vel[i][2];
        //Actualizamos las posicicones
        pos[i][0] += vel[i][0]*dt;
        pos[i][1] += vel[i][1]*dt;
        pos[i][2] += vel[i][2]*dt;
      
fprintf(arch,"%lf %lf %lf\n",pos[i][0],pos[i][1],pos[i][2]);

    }
fclose(arch);
}

void integr(Particula* gas,double dt,int num_archivo)
{
    force(N,gas->pos,gas->vel,gas->m,dt,num_archivo); 
}

int main()
{

  double t,dt;
  dt=0.0001;

  Particula Gas;
  init(&Gas);
 
int i=0;
  for(t=0;t<20;t=t+dt)
  {
    integr(&Gas,dt,i);
i++;
  }
return 0;
}
