#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <string>
#include <iostream>

using namespace std;

GLenum tradutor(int a) {
	switch (a) {
		case 0:
			return GL_LINES;
			break;
		case 1:
			return GL_LINE_STRIP;
			break;
		case 2:
			return GL_LINE_LOOP;
			break;
		case 3:
			return GL_POLYGON;
			break;
		case 4:
			return GL_TRIANGLES;
			break;
		case 5:
			return GL_TRIANGLE_STRIP;
			break;
		case 6:
			return GL_TRIANGLE_FAN;
			break;
		case 7:
			return GL_QUADS;
			break;
		case 8:
			return GL_QUAD_STRIP;
			break;
	}
}

//armazena os vértices de um objeto
struct VERTEX
{
	int x;
	int y;
	int z;
};

//armazena a descrição geométrica de um objeto
struct OBJECT
{
	VERTEX *vertices;
	int nrvertices;
	int begin;
};

GLfloat angle, fAspect;

struct LISTOFOBJECTS {
	OBJECT *objetos;
	int nrobjetos;
};

LISTOFOBJECTS *listadeobjetos; //objeto global que será desenhado

OBJECT *create_object_initial()
{
	OBJECT *obj = (OBJECT *)malloc(sizeof(OBJECT));
	obj->nrvertices = 24;
	obj->begin = 7;
	obj->vertices = (VERTEX *)malloc(obj->nrvertices * sizeof(VERTEX));

	//front

	obj->vertices[0].x = 50;
	obj->vertices[0].y = 250;
	obj->vertices[0].z = 150;

	obj->vertices[1].x = 100;
	obj->vertices[1].y = 250;
	obj->vertices[1].z = 150;

	obj->vertices[2].x = 100;
	obj->vertices[2].y = 300;
	obj->vertices[2].z = 150;

	obj->vertices[3].x = 50;
	obj->vertices[3].y = 300;
	obj->vertices[3].z = 150;

	//back

	obj->vertices[4].x = 100;
	obj->vertices[4].y = 250;
	obj->vertices[4].z = 200;

	obj->vertices[5].x = 100;
	obj->vertices[5].y = 250;
	obj->vertices[5].z = 200;

	obj->vertices[6].x = 100;
	obj->vertices[6].y = 300;
	obj->vertices[6].z = 200;

	obj->vertices[7].x = 50;
	obj->vertices[7].y = 300;
	obj->vertices[7].z = 200;

	//top

	obj->vertices[8].x = 50;
	obj->vertices[8].y = 300;
	obj->vertices[8].z = 150;


	obj->vertices[9].x = 100;
	obj->vertices[9].y = 300;
	obj->vertices[9].z = 150;


	obj->vertices[10].x = 100;
	obj->vertices[10].y = 300;
	obj->vertices[10].z = 200;

	obj->vertices[11].x = 50;
	obj->vertices[11].y = 300;
	obj->vertices[11].z = 200;

	//bottom

	obj->vertices[12].x = 50;
	obj->vertices[12].y = 250;
	obj->vertices[12].z = 150;


	obj->vertices[13].x = 100;
	obj->vertices[13].y = 250;
	obj->vertices[13].z = 150;


	obj->vertices[14].x = 100;
	obj->vertices[14].y = 250;
	obj->vertices[14].z = 200;

	obj->vertices[15].x = 50;
	obj->vertices[15].y = 250;
	obj->vertices[15].z = 200;

	//left

	obj->vertices[16].x = 50;
	obj->vertices[16].y = 250;
	obj->vertices[16].z = 150;


	obj->vertices[17].x = 50;
	obj->vertices[17].y = 250;
	obj->vertices[17].z = 200;


	obj->vertices[18].x = 50;
	obj->vertices[18].y = 300;
	obj->vertices[18].z = 200;

	obj->vertices[19].x = 50;
	obj->vertices[19].y = 300;
	obj->vertices[19].z = 200;

	//right

	obj->vertices[20].x = 100;
	obj->vertices[20].y = 250;
	obj->vertices[20].z = 150;


	obj->vertices[21].x = 100;
	obj->vertices[21].y = 250;
	obj->vertices[21].z = 200;


	obj->vertices[22].x = 100;
	obj->vertices[22].y = 300;
	obj->vertices[22].z = 200;

	obj->vertices[23].x = 100;
	obj->vertices[23].y = 300;
	obj->vertices[23].z = 150;



	return obj;
}

LISTOFOBJECTS *create_lista_initial()
{
	LISTOFOBJECTS *obj = (LISTOFOBJECTS *)malloc(sizeof(LISTOFOBJECTS));
	obj->nrobjetos = 1;
	obj->objetos = (OBJECT *)malloc(obj->nrobjetos * sizeof(OBJECT));

	obj->objetos[0] = *create_object_initial();
	
	return obj;
}


void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	listadeobjetos = create_lista_initial(); //cria o objeto
	angle = 45;
}

void EspecificaParametrosVisualizacao() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(angle, fAspect, 0.1, 500);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 0, 0, 150, 50, 0, 1, 0);
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if (h == 0) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w / (GLfloat)h;

	EspecificaParametrosVisualizacao();
}

void desenha(LISTOFOBJECTS* listobj, int opt)
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int i;
	for (i = 0; i < listobj->nrobjetos; i++) {

		OBJECT* obj = &listobj->objetos[i];

		int j;
		glBegin(tradutor(obj->begin)); //desenha uma linha
		
		for (j = 0; j < obj->nrvertices; j++)
		{
			if (opt == 0)
			{
				// Desenha sem alterações
				glVertex3f(obj->vertices[j].x, obj->vertices[j].y, obj->vertices[j].z);
			}
			if (opt == 1)
			{
				// Reflexao 0y
				glVertex3f(obj->vertices[j].x*-1, obj->vertices[j].y, obj->vertices[j].z);
			}
			if (opt == 2)
			{
				// Reflexao y=x
				glVertex3f(obj->vertices[j].y, obj->vertices[j].x, obj->vertices[j].z);
			}

		}
	}
	glEnd();
	// Executa os comandos OpenGL
	glutSwapBuffers();
}

void funcoesTeclado(unsigned char key, int x, int y)
{
	if (key == 65)
	{
		
	}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

void funcoesMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angle >= 10) angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angle <= 130) angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

void funcoesEspeciais(int a, int b, int c)
{
	if (a == GLUT_LEFT_BUTTON)
		if (b == GLUT_UP) {  // Zoom-in
		//	glutTimerFunc(10, Timer, 1);
		}
	if (a == GLUT_RIGHT_BUTTON)
		if (b == GLUT_UP) {  // Zoom-out
		//	CriaMenus();
		}
	//EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //desenha o fundo (limpa a janela)
	glClearDepth(1.0f);
	glColor3f(1.0, 0.0, 0.0); //altera o atributo de cor
	glMatrixMode(GL_MODELVIEW); //garante que a matrix seja a ModelView

	glPushMatrix();
	desenha(listadeobjetos, 0); //desenha a letra L
	glPopMatrix();

	// Exercicio 1, Reflexao 0y
	


	glFlush(); //processa as rotinas OpenGL o mais rápido possível
}

//int menu() {

	//system("cls");

	//printf("Menu");

	//int a;

	//scanf("%d", &a);

	//return a;
//}

//int optionSelected(int a) {
	//system("cls");

	//switch (a) {
	//case 0:
//		return 0;
		///break;

//	}

	//printf("Digite 1 para ir ao menu: ");

	//int b;

//	scanf("%d", &b);

	//return b;

//}

int main(int argc, char**argv)
{
	//glutInit(&argc, argv); // glutInit() obrigatorio no Linux
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("GLUT Didactic Editor");
	glutDisplayFunc(display); // registra a função de desenho
	glutReshapeFunc(AlteraTamanhoJanela);



	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutKeyboardFunc(funcoesTeclado);
	glutMouseFunc(funcoesMouse);
	glutSpecialFunc(funcoesEspeciais);

	init(); // inicialização (após a criação da janela)
	glutMainLoop(); // desenha tudo e espera por eventos

	//int i = 1;

	//while (i == 1) {

	//	i = optionSelected(menu());

	//}

	


	return EXIT_SUCCESS;
}