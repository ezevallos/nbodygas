#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define PI 3.141592654
//#define N=1000;
/***************************************
      *     Inicializacion de variables     *
      ***************************************/

      GLdouble pos[200][3];
GLdouble rd[200];
      GLdouble posx=0,posz=0;
int num_arch=0;
     /*******************************************************
      *     Inicializacion de variables para iluminacion    *
      *******************************************************/

      GLfloat mat_diffuse [] = {0.0, 0.0, 0.0, 1.0};
      GLfloat mat_specular [] = {0.5, 0.5, 0.5, 1.0};
      GLfloat mat_shininess [] = {50};
      GLfloat mat_emission [] = {0.5, 0.2, 0.2, 1.0};

/**********************************************************************/
/**********************************************************************/

float posCam[3]; //posicion de  la camera 
float at[3];
float up[3];  // para la direccion ortogonal de la camera 
float dir[3];
int angH;
int angV;
float mod; // camera !!
/*********************************************************************
**********************************/

void init(){
//gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);
// gluLookAt(posCam[0],posCam[1],posCam[2],at[0],at[1],at[2],up[0],up[1],up[2]); // x,y,z

	glClearColor(0.0,0.0,0.0,1.0);
	//Habilita el color
	glEnable(GL_COLOR_MATERIAL);
	
	//Asigna el Color al material
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	// Posicion de la camera
	posCam[0] = 1.0; //x
	posCam[1] = 1.0;  //y
	posCam[2] = 1.0; //z
	// Para voltear a la izquierda o derecha
	angH = 0.0;
	// Para voltear a arriba o abajo
	angV = 0.0;
	// Direccion ortogonal a donde esta viendo
	up[0] = 0.0; 
	up[1] = 1.0;
	up[2] = 0.0;
	//glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
}
void resize(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);//matriz de proyeccion
    glLoadIdentity();//cargamos la matriz identidad
    glOrtho(-5000,5000,-5000,5000,-5000,5000);
    glMatrixMode(GL_MODELVIEW);//matriz de modelado
    glLoadIdentity();//matriz identidad
    glEnable(GL_DEPTH_TEST);//activamos el Test de profundidad
    glDepthFunc(GL_LEQUAL);//funcion de borrrado buffer depth

}

     /***********************
      *      iluminacion    *
      ***********************/

void iluminacion ()
{
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
glLightfv(GL_LIGHT0,GL_POSITION, light_position);

glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
glEnable (GL_LIGHTING);
glEnable (GL_LIGHT0);
glEnable(GL_COLOR_MATERIAL);

}




     /****************************
      *   EJES DE COORDENADAS    *
      ****************************/


void ejes()
{
       glColor3f(1,1,1);
       glBegin(GL_LINES);
            glVertex3f(-200,0,0);
            glVertex3f(200,0,0);
            glVertex3f(0,-200,0);
            glVertex3f(0,200,0);
            glVertex3f(0,0,-200);
            glVertex3f(0,0,200);

       glEnd();

}

    /************************************
     *     CREACION DE LOS PLANETAS     *
     ************************************/
void astro(int i)
{
glColor3f(i*0.005,i*0.0008,i*0.00014);
glutSolidSphere(rd[i],60,60);
}

  /*********************************
     *     CREACION DE LA ESCENA     *
 
    *********************************/




void display()
{

//abriendo el archivo correspondiente!!
char * name_arch=(char*)malloc(sizeof(char)*50);
memset(name_arch,0,50);
sprintf(name_arch,"%d.dat",num_arch);
FILE* arch=fopen(name_arch,"r+t");
int cont=0;
for(cont=0;cont<200;cont++)
{
fscanf(arch,"%lf %lf %lf",&pos[cont][0],&pos[cont][1],&pos[cont][2]);
}
fclose(arch);

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0,1.2,1.0,1500.0);  //esto fue modificado !!!
    glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
//camera !!!

     //gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);
mod = sqrt(dir[0]*dir[0] + dir[2]*dir[2]);
	dir[0] = cos(PI*angH/180.0)/100;
	dir[2] = sin(PI*angH/180.0)/100;
	at[0] = posCam[0]+dir[0];
	at[1] = posCam[1]+mod*sin(PI*angV/180.0);
	at[2] = posCam[2]+dir[2];

  gluLookAt(posCam[0],posCam[1],posCam[2],at[0],at[1],at[2],up[0],up[1],up[2]); // x,y,z


     iluminacion ();
     ejes();
int i;
for(i=0;i<200;i++){
 glPushMatrix();
     //glRotatef(rot[i],0,1,0);
     glTranslatef(pos[i][0],pos[i][1],pos[i][2]); 
     astro(i);
     glPopMatrix();
}

num_arch++;
     glutSwapBuffers();
}



    /*************************************
     *          MANEJO DE CAMARA         *
     *************************************/
/*******keyboard de movimiento de camera****/
void Keyboard_1(unsigned char key, int x,int y){
	int i,j,k;
	switch(key){
		case 'w': //Tecla para avanzar
			posCam[0]+=dir[0]*150;
			posCam[2]+=dir[2]*150;
			break; 
		case 's':  // Tecla para retroceder
			posCam[0]-=dir[0]*150;
			posCam[2]-=dir[2]*150;
			break;
	        case 'd': // Tecla para subir
			
			       posCam[1]+=1; 
			break;
		case 'a': // Tecla para bajar
			
			    posCam[1]-=1;
			break;
		case 27:
			exit(0);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void Keyboard_2(int key, int x,int y){
	switch(key){ // Tecla para alzar la vista del angulo 
		case GLUT_KEY_UP:
			angV+=2; 
			break; 
		case GLUT_KEY_DOWN:   // Tecla para bajar la vista del angulo 
			angV-=2;
			break; 
		case GLUT_KEY_LEFT:   //Tecla para girar a la izquierda 
			angH-=2;
			if(angH<0){
			angH+=360;
			}
			break; 
		case GLUT_KEY_RIGHT:   //Tecla para girar a la derecha 
			angH = (angH + 2)%360;
			break; 
		default:
			break;
	}
	glutPostRedisplay();
}


void key(unsigned char key, int x, int y)    //funcion para uso del teclado
{
    switch(key)
    {
          case 27 :
            exit(0);
            break;
        default:
            break;
    }

glutPostRedisplay();    //redibuja el display
}


void idle()
{
    glutPostRedisplay();//redibuja el display
}


    /*************************************
     *          FUNCION PRINCIPAL        *
     *************************************/

int main (int argc, char *argv[])
{
int i;

for(i=0;i<200;i++){
//rd[i]=(double)(rand()%(4))+2.0;
rd[i]=(double)3.0;
}
/*for (i=0;i<10 ;i++){
rot[i]=rand()%200;
}
for (i=0;i<100;i++)
pos[i]=rand()%100;*/

    glutInit(&argc, argv);//inicializacion del glut
    glutInitWindowSize(800,800);//tamaño de la ventana
    glutInitWindowPosition(400,100);//posicion de la ventana en el monitor
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);//modo de visualizacion inicial
    glutCreateWindow("BIG BANG : LA GRAN EXPLOSION");//nombre de la ventana
	init();
    glClearColor(0,0,0,0);//especificar valores claros para el color del buffer
    glutReshapeFunc(resize);//control de ventanas
gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);
    glutDisplayFunc(display);//establece la devolución de llamada de visualización de la ventana actual
        glutKeyboardFunc(Keyboard_1);
	glutSpecialFunc(Keyboard_2);  
glutFullScreen();
    glutIdleFunc(idle);//funcion de animacion

   // char soundfile[20] ="C:\planeta.wav";//sonido
    //PlaySound((LPCSTR)soundfile, NULL, SND_FILENAME | SND_ASYNC );//sonido

    glutMainLoop();//bucle de procesamiento de eventos de GLUT
    return 0;
}
