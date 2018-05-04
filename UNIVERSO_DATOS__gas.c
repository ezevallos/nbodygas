#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include<string.h>
#define N 200
//BY:FRANCO NAJARRO MALLQUI
static double G=0.0000000000667384;
typedef struct cuerpoCeleste
{
  double pos[3][N];
  double vel[3][N];
  double m[N];

} cuerpoCeleste;

void init(cuerpoCeleste* galaxia)
{
    int i,j;
    time_t t;
    srand(time(&t));

    for(j=0;j<N;j++)
    {
      
	for(i=0;i<3;i++)
        {
         galaxia->pos[i][j]=((double)rand()/RAND_MAX)*(200.0)-100;
         galaxia->vel[i][j]=((double)rand()/RAND_MAX)*(10.0)+200.0;
        }
	galaxia->m[j]=(double)0.000000001;
    }


}

void force(int n,double pos[3][N],double vel[3][N],double m[N],double dt,int num_archivo)
{
    int i,j;
    double r_x,r_y,r_z,d,a_x,a_y,a_z;
char name_arch[20];
memset(name_arch,0,20);
sprintf(name_arch,"%d.dat",num_archivo);//ARCHIVOS DE  SALIDA PARA LA GRAFICA DE LOS N-CUERPOS EN EL ESPACIO !!!
FILE*arch=fopen(name_arch,"a+t");

    for(i=0;i<n;i++)
    {
        r_x=pos[0][i];
        r_y=pos[1][i];
        r_z=pos[2][i];

        a_x=0;a_y=0;a_z=0;

        for(j=0;j<n;j++)
        {
            if(j!=i)
            {
                d=pos[0][j]-r_x;
                if(d!=0)
                {
                    if(d>=0) a_x += G*m[j]/(d*d);
                    else     a_x += -(G*m[j]/(d*d));
                }

                d=pos[1][j]-r_y;
                if(d!=0)
                {
                    if(d>=0) a_y += G*m[j]/(d*d);
                    else     a_y += -(G*m[j]/(d*d));
                }

                d=pos[2][j]-r_z;
                if(d!=0)
                {
                    if(d>=0) a_z += G*m[j]/(d*d);
                    else     a_z += -(G*m[j]/(d*d));
                }
            }

        }
        //Actualizamos las velocidades
        vel[0][i] += a_x*dt;
        vel[1][i] += a_y*dt;
        vel[2][i] += a_z*dt;
	//aqui verificamos si hubo un choque con las paredes !!!
	if(pos[0][i]>=100 || pos[0][i]<=-100)
		  vel[0][i] =(-1.0)*vel[0][i];
	if(pos[1][i]>=100 || pos[1][i]<=-100)
		  vel[1][i] =(-1.0)*vel[1][i];
	if(pos[2][i]>=100 || pos[2][i]<=-100)
		  vel[2][i] =(-1.0)*vel[2][i];

        //Actualizamos las posicicones
        pos[0][i] += vel[0][i]*dt;
        pos[1][i] += vel[1][i]*dt;
        pos[2][i] += vel[2][i]*dt;
       // printf("i:%d aceleracion: %lf velocidad: %lf y posicion: %lf\n",i,a_x,vel[0][i],pos[0][i]);
fprintf(arch,"%lf %lf %lf\n",pos[0][i],pos[1][i],pos[2][i]);

    }
fclose(arch);
}

void integr(cuerpoCeleste* galaxia,double dt,int num_archivo)
{
   

    force(N,galaxia->pos,galaxia->vel,galaxia->m,dt,num_archivo);

  
}

int main()
{

  double t,dt;
  dt=0.001;

  cuerpoCeleste Galaxy;
  init(&Galaxy);
 
int i=0;
  for(t=0;t<10;t=t+dt)
  {
    integr(&Galaxy,dt,i);
i++;
  }
return 0;
}
