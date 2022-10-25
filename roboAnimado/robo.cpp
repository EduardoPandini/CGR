// g++ robo.cpp -lglut -lGL -lGLU -lm -o robo && ./robo

/*
- Usar "voltar para a posição inicia" para cancelar 
algum movimento ou voltar ao original, se não pode bugar
- Não abaixar o braço sem levantá-lo, pois levanta a perna
- Acenar depois de pedir carona faz bugar o sistema
- Pular é o único que funciona com o sistema bugado
*/

#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>

using namespace std;

#define ombroRaio 0.8
#define cabecaAltura 1.5
#define cabecaRaio 1.0
#define pescocoAltura 1.2
#define pescocoRaio 0.4
#define corpoAltura 8.0
#define corpoRaio 2.0
#define bracoAltura 4.0
#define bracoRaio 0.5
#define antebracoAltura 3.0
#define antebracoRaio 0.5
#define pernaAltura 5.0
#define pernaRaio 0.6
#define canelaAltura 4.0
#define canelaRaio 0.5
#define cotoveloRaio 0.6
#define joelhoRaio 0.7
#define maoRaio 0.6
#define peRaio 0.7
#define passo 0.5
#define NULL 0

int opcao = -1;
int animacao = -3;
int done = 0;
double rotate = 0;
double horizontal = 0;

void cabeca();
void corpo();
void bracoEsquerdo();
void bracoDireito();
void pernaEsquerda();
void pernaDireita();


typedef float point[3];

typedef struct no
{
	GLfloat m[16];
	void (*f)();
	struct no *sibling;
	struct no *child;
} no;

typedef no *t_ptr;

static GLfloat theta[13] = {0.0, 0.0, 0.0, 180.0, 0.0, 180.0, 0.0,
							180.0, 0.0, 180.0, 0.0, 45.0, 90.0}; /* angulos iniciais */

static GLint angle = 2;

GLUquadricObj *t, *h, *lua, *lla, *rua, *rla, *lll, *rll, *rul, *lul;
GLUquadricObj *relb, *lelb, *rknee, *lknee, *nk, *lhand, *rhand, *lfoot, *rfoot, *rsh, *lsh;

double size = 1.0;

no corpo_node, cabeca_node, lua_node, rua_node, lll_node, rll_node,
	lla_node, rla_node, rul_node, lul_node,
	relb_node, lelb_node, rknee_node, lknee_node, nk_node, lhand_node, rhand_node, lfoot_node, rfoot_node,
	rsh_node, lsh_node;

void traverse(no *root)
{
	if (root == NULL)
		return;
	glPushMatrix();
	glMultMatrixf(root->m);
	root->f();
	if (root->child != NULL)
		traverse(root->child);
	glPopMatrix();
	if (root->sibling != NULL)
		traverse(root->sibling);
}

void corpo()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(t, corpoRaio / 1.2, corpoRaio, corpoAltura, 10, 10);
	glPopMatrix();
}

void cabeca()
{
	glPushMatrix();
	glTranslatef(0.0, cabecaAltura, 0.0);
	glScalef(cabecaRaio, cabecaAltura, cabecaRaio);
	gluSphere(h, cabecaRaio, 10, 10);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0f, -0.4f, -0.15f);
	gluCylinder(h, 0.9 * cabecaRaio, 0.9 * cabecaRaio, cabecaAltura / 5, 10, 10);
	glPopMatrix();
}

void pescoco()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(nk, pescocoRaio, pescocoRaio, pescocoAltura, 10, 10);
	glPopMatrix();
}

void ombroDireito()
{
	glPushMatrix();
	gluSphere(relb, ombroRaio, 10, 10);
	glPopMatrix();
}

void ombroesquerdo()
{
	glPushMatrix();
	gluSphere(lelb, ombroRaio, 10, 10);
	glPopMatrix();
}

void cotoveloDireito()
{
	glPushMatrix();
	gluSphere(relb, cotoveloRaio, 10, 10);
	glPopMatrix();
}

void cotoveloEsquerdo()
{
	glPushMatrix();
	gluSphere(lelb, cotoveloRaio, 10, 10);
	glPopMatrix();
}

void joelhoDireito()
{
	glPushMatrix();
	gluSphere(rknee, joelhoRaio, 10, 10);
	glPopMatrix();
}

void joelhoEsquerdo()
{
	glPushMatrix();
	gluSphere(lknee, joelhoRaio, 10, 10);
	glPopMatrix();
}

void peEsquerdo()
{
	glPushMatrix();
	gluSphere(lknee, peRaio, 10, 10);
	glPopMatrix();
}

void peDireito()
{
	glPushMatrix();
	gluSphere(lknee, peRaio, 10, 10);
	glPopMatrix();
}

void rightHand()
{
	glPushMatrix();
	gluSphere(lknee, maoRaio, 10, 10);
	glPopMatrix();
}

void leftHand()
{
	glPushMatrix();
	gluSphere(lknee, maoRaio, 10, 10);
	glPopMatrix();
}

void bracoEsquerdo()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(lua, bracoRaio, bracoRaio - 0.1, bracoAltura, 10, 10);
	glPopMatrix();
}

void left_lower_arm()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(lla, antebracoRaio - 0.1, antebracoRaio - 0.15, antebracoAltura, 10, 10);
	glPopMatrix();
}

void bracoDireito()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(rua, bracoRaio, bracoRaio - 0.1, bracoAltura, 10, 10);
	glPopMatrix();
}

void right_lower_arm()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(rla, antebracoRaio - 0.1, antebracoRaio - 0.15, antebracoAltura, 10, 10);
	glPopMatrix();
}

void pernaEsquerda()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(lul, pernaRaio, pernaRaio - 0.1, pernaAltura, 10, 10);
	glPopMatrix();
}

void left_lower_leg()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(lll, canelaRaio - 0.1, canelaRaio - 0.2, canelaAltura, 10, 10);
	glPopMatrix();
}

void pernaDireita()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(rul, pernaRaio, pernaRaio - 0.1, pernaAltura, 10, 10);
	glPopMatrix();
}

void right_lower_leg()
{
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(rll, canelaRaio - 0.1, canelaRaio - 0.2, canelaAltura, 10, 10);
	glPopMatrix();
}

void display(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15, 15, -15, 15, -15, 15);
	glRotatef(rotate, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(0.4, 0.4, 0.4);
	traverse(&corpo_node);
	glutSwapBuffers();
}

void inverterCinematica()
{
	switch (animacao)
	{
	case '0':
		if (theta[5] < 180.0)
		{
			theta[5] += passo;
			theta[3] += passo;
			theta[1] -= 0.2 * passo;
		}
		else
			animacao = opcao;

		glPushMatrix();

		glLoadIdentity();
		glTranslatef(0, 0, 0.0);
		glRotatef(theta[5], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, rua_node.m);

		glLoadIdentity();
		glTranslatef(0, 0, 0.0);
		glRotatef(theta[3], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, lua_node.m);

		glLoadIdentity();
		glTranslatef(0.0, corpoAltura - 0.25 * pescocoAltura, 0.0);
		glRotatef(theta[1], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, nk_node.m);

		glPopMatrix();
		break;

	case '1':
		if (theta[9] < 180.0)
		{
			theta[9] += passo;
			theta[10] -= passo;
		}
		else
			animacao = opcao;

		glPushMatrix();

		glLoadIdentity();
		glTranslatef(corpoRaio / 2, 0.1 * pernaAltura, 0.0);
		glRotatef(theta[9], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, rul_node.m);

		glLoadIdentity();
		glTranslatef(0.0, pernaAltura, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, rknee_node.m);

		glLoadIdentity();
		glTranslatef(0.0, joelhoRaio / 2, 0.0);
		glRotatef(theta[10], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, rll_node.m);

		glPopMatrix();
		break;

	case '3':
	case '-2':
		if (theta[9] < 180.0)
		{
			theta[9] += passo;
			theta[10] -= passo;
			theta[7] += passo;
			theta[8] -= passo;
			theta[5] -= passo;
			theta[6] += passo;
			theta[3] += passo;
			theta[4] -= passo;
			horizontal -= 0.03 * passo;
		}
		else
			animacao = opcao;

		glPushMatrix();

		glLoadIdentity();
		glTranslatef(0, 0, 0.0);
		glRotatef(theta[5], 0.0, 0.0, 1.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, rua_node.m);

		glLoadIdentity();
		glTranslatef(0, 0, 0.0);
		glRotatef(theta[6], 0.0, 0.0, 1.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, rla_node.m);

		glLoadIdentity();
		glTranslatef(0, 0, 0.0);
		glRotatef(theta[3], 0.0, 0.0, 1.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, lua_node.m);

		glLoadIdentity();
		glTranslatef(0, 0, 0.0);
		glRotatef(theta[4], 0.0, 0.0, 1.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, lla_node.m);

		glLoadIdentity();
		glTranslatef(corpoRaio / 2, 0.1 * pernaAltura, 0.0);
		glRotatef(theta[9], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, rul_node.m);

		glLoadIdentity();
		glTranslatef(0.0, joelhoRaio / 2, 0.0);
		glRotatef(theta[10], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, rll_node.m);

		glLoadIdentity();
		glTranslatef(-corpoRaio / 2, 0.1 * pernaAltura, 0.0);
		glRotatef(theta[7], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, lul_node.m);

		glLoadIdentity();
		glTranslatef(0.0, joelhoRaio / 2, 0.0);
		glRotatef(theta[8], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, lll_node.m);

		glLoadIdentity();
		glTranslatef(0, -horizontal, -horizontal);
		glGetFloatv(GL_MODELVIEW_MATRIX, corpo_node.m);

		glPopMatrix();
		break;

	case '4':
	case '-1':
		if (theta[5] < 180.0)
		{
			theta[5] += passo;
			theta[3] += passo;
			theta[1] -= 0.2 * passo;
		}
		else
			animacao = opcao;

		glPushMatrix();

		glLoadIdentity();
		glTranslatef(0, 0, 0.0);
		glRotatef(theta[3], 0.0, 0.0, 1.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, lua_node.m);

		glPopMatrix();
		break;

	case '5':
	case '-5':
		if (theta[12] < 90.0)
		{
			theta[12] += passo;
			theta[3] += passo;
			theta[1] -= 0.2 * passo;
			theta[11] += passo;
		}
		else
			animacao = opcao;

		glPushMatrix();

		glLoadIdentity();
		glTranslatef(0, 0, 0.0);
		glRotatef(theta[3], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, rua_node.m);

		glLoadIdentity();
		glTranslatef(0, 0, 0.0);
		glRotatef(theta[6], 0.0, 0.0, 1.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, rla_node.m);

		glPopMatrix();
		break;

	default:
		animacao = opcao;
	}
}

void idle()
{
	switch (opcao)
	{
	case '0':
		if (animacao != opcao)
			inverterCinematica();
		else if (!done)
		{
			if (theta[5] > 30.0)
			{
				theta[5] -= passo;
				theta[3] -= passo;
				theta[1] += 0.2 * passo;
			}
			else
				done = 1;

			glPushMatrix();

			glLoadIdentity();
			glTranslatef(0, 0, 0.0);
			glRotatef(theta[5], 1.0, 0.0, 0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, rua_node.m);

			glLoadIdentity();
			glTranslatef(0, 0, 0.0);
			glRotatef(theta[3], 1.0, 0.0, 0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, lua_node.m);

			glLoadIdentity();
			glTranslatef(0.0, corpoAltura - 0.25 * pescocoAltura, 0.0);
			glRotatef(theta[1], 1.0, 0.0, 0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, nk_node.m);

			glPopMatrix();
		}
		break;

	case '1':
		if (animacao != opcao)
			inverterCinematica();
		else if (!done)
		{
			if (theta[9] > 110.0)
			{
				theta[9] -= passo;
				theta[10] += passo;
			}
			else
				done = 1;

			glPushMatrix();

			glLoadIdentity();
			glTranslatef(corpoRaio / 2, 0.1 * pernaAltura, 0.0);
			glRotatef(theta[9], 1.0, 0.0, 0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, rul_node.m);

			glLoadIdentity();
			glTranslatef(0.0, joelhoRaio / 2, 0.0);
			glRotatef(theta[10], 1.0, 0.0, 0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, rll_node.m);

			glLoadIdentity();
			glTranslatef(0, -horizontal, -horizontal);
			glGetFloatv(GL_MODELVIEW_MATRIX, corpo_node.m);

			glPopMatrix();
		}
		break;

	case '2':
		inverterCinematica();
		break;

	case '3':
		if (animacao != opcao)
			inverterCinematica();
		else
		{
			if (theta[9] > 130.0)
			{
				theta[9] -= passo;
				theta[10] += passo;
				theta[7] -= passo;
				theta[8] += passo;
				theta[5] += passo;
				theta[6] -= passo;
				theta[3] -= passo;
				theta[4] += passo;
				horizontal += 0.03 * passo;
			}
			else
				animacao = '-2';

			glPushMatrix();

			glLoadIdentity();
			glTranslatef(0, 0, 0.0);
			glRotatef(theta[5], 0.0, 0.0, 1.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, rua_node.m);

			glLoadIdentity();
			glTranslatef(0, 0, 0.0);
			glRotatef(theta[6], 0.0, 0.0, 1.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, rla_node.m);

			glLoadIdentity();
			glTranslatef(0, 0, 0.0);
			glRotatef(theta[3], 0.0, 0.0, 1.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, lua_node.m);

			glLoadIdentity();
			glTranslatef(0, 0, 0.0);
			glRotatef(theta[4], 0.0, 0.0, 1.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, lla_node.m);

			glLoadIdentity();
			glTranslatef(corpoRaio / 2, 0.1 * pernaAltura, 0.0);
			glRotatef(theta[9], 1.0, 0.0, 0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, rul_node.m);

			glLoadIdentity();
			glTranslatef(0.0, joelhoRaio / 2, 0.0);
			glRotatef(theta[10], 1.0, 0.0, 0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, rll_node.m);

			glLoadIdentity();
			glTranslatef(-corpoRaio / 2, 0.1 * pernaAltura, 0.0);
			glRotatef(theta[7], 1.0, 0.0, 0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, lul_node.m);

			glLoadIdentity();
			glTranslatef(0.0, joelhoRaio / 2, 0.0);
			glRotatef(theta[8], 1.0, 0.0, 0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, lll_node.m);

			glLoadIdentity();
			glTranslatef(0, -horizontal, -horizontal);
			glGetFloatv(GL_MODELVIEW_MATRIX, corpo_node.m);

			glPopMatrix();
		}
		break;

	case '4':
		if (animacao != opcao)
			inverterCinematica();
		else if (!done)
		{
			if (theta[5] > 30.0)
			{
				theta[5] -= passo;
				theta[3] -= passo;
				theta[1] += 0.2 * passo;
			}
			else
				done = 1;

			glPushMatrix();

			glLoadIdentity();
			glTranslatef(0, 0, 0.0);
			glRotatef(theta[3], 0.0, 0.0, 1.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, lua_node.m);

			glPopMatrix();
		}
		break;

	case '5':
		if (animacao != opcao)
			inverterCinematica();
		else if (!done)
		{
			if (theta[12] > 30.0)
			{
				theta[12] -= passo;
				theta[3] -= passo;
				theta[1] += 0.2 * passo;
				theta[11] -= passo;
			}
			else
				done = 1;

			glPushMatrix();

			glLoadIdentity();
			glTranslatef(0, 0, 0.0);
			glRotatef(theta[12], 1.0, 0.0, 0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, rua_node.m);

			glLoadIdentity();
			glTranslatef(0, -horizontal, -horizontal);
			glGetFloatv(GL_MODELVIEW_MATRIX, rua_node.m);

			glLoadIdentity();
			glTranslatef(0, 0, 0.0);
			glRotatef(theta[11], 0.0, 0.0, 1.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, rla_node.m);

			glPopMatrix();
		}
		break;
	}
	glutPostRedisplay();
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-10.0, 10.0, -10.0 * (GLfloat)h / (GLfloat)w,
				10.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-10.0 * (GLfloat)w / (GLfloat)h,
				10.0 * (GLfloat)w / (GLfloat)h, 0.0, 10.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myinit()
{

	glEnable(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.2, 0.2, 0.2, 1.0);

	//INICIALIZANDO ROBO
	h = gluNewQuadric();
	gluQuadricDrawStyle(h, GLU_FILL);
	t = gluNewQuadric();
	gluQuadricDrawStyle(t, GLU_FILL);
	lua = gluNewQuadric();
	gluQuadricDrawStyle(lua, GLU_FILL);
	lelb = gluNewQuadric();
	gluQuadricDrawStyle(lelb, GLU_FILL);
	lla = gluNewQuadric();
	gluQuadricDrawStyle(lla, GLU_FILL);
	rua = gluNewQuadric();
	gluQuadricDrawStyle(rua, GLU_FILL);
	rla = gluNewQuadric();
	gluQuadricDrawStyle(rla, GLU_FILL);
	lul = gluNewQuadric();
	gluQuadricDrawStyle(lul, GLU_FILL);
	lll = gluNewQuadric();
	gluQuadricDrawStyle(lll, GLU_FILL);
	rul = gluNewQuadric();
	gluQuadricDrawStyle(rul, GLU_FILL);
	rll = gluNewQuadric();
	gluQuadricDrawStyle(rll, GLU_FILL);
	rknee = gluNewQuadric();
	gluQuadricDrawStyle(rknee, GLU_FILL);
	lknee = gluNewQuadric();
	gluQuadricDrawStyle(lknee, GLU_FILL);
	relb = gluNewQuadric();
	gluQuadricDrawStyle(relb, GLU_FILL);
	nk = gluNewQuadric();
	gluQuadricDrawStyle(nk, GLU_FILL);
	rhand = gluNewQuadric();
	gluQuadricDrawStyle(rhand, GLU_FILL);
	lhand = gluNewQuadric();
	gluQuadricDrawStyle(lhand, GLU_FILL);
	lfoot = gluNewQuadric();
	gluQuadricDrawStyle(lfoot, GLU_FILL);
	rfoot = gluNewQuadric();
	gluQuadricDrawStyle(rfoot, GLU_FILL);
	rsh = gluNewQuadric();
	gluQuadricDrawStyle(rsh, GLU_FILL);
	lsh = gluNewQuadric();
	gluQuadricDrawStyle(lsh, GLU_FILL);

	//INÍCIO INICIALIZAÇÃO ÁRVORE
	glLoadIdentity();
	glRotatef(theta[0], 0.0, 1.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, corpo_node.m);
	corpo_node.f = corpo;
	corpo_node.sibling = NULL;
	corpo_node.child = &nk_node;

	glLoadIdentity();
	glTranslatef(0.0, corpoAltura - 0.25 * pescocoAltura, 0.0);
	glRotatef(theta[1], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, nk_node.m);
	nk_node.f = pescoco;
	nk_node.sibling = &lsh_node;
	nk_node.child = &cabeca_node;

	glLoadIdentity();
	glTranslatef(-(corpoRaio + bracoRaio), 0.9 * corpoAltura, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, lsh_node.m);
	lsh_node.f = ombroesquerdo;
	lsh_node.sibling = &rsh_node;
	lsh_node.child = &lua_node;

	glLoadIdentity();
	glTranslatef(corpoRaio + bracoRaio, 0.9 * corpoAltura, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, rsh_node.m);
	rsh_node.f = ombroDireito;
	rsh_node.sibling = &lul_node;
	rsh_node.child = &rua_node;

	glLoadIdentity();
	glTranslatef(0.0, 0.45 * pescocoAltura, 0.0);
	glRotatef(theta[2], 0.0, 1.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, cabeca_node.m);
	cabeca_node.f = cabeca;
	cabeca_node.sibling = NULL;
	cabeca_node.child = NULL;

	glLoadIdentity();
	glTranslatef(0, 0, 0.0);
	glRotatef(theta[3], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, lua_node.m);
	lua_node.f = bracoEsquerdo;
	lua_node.sibling = NULL;
	lua_node.child = &lelb_node;

	glLoadIdentity();
	glTranslatef(0.0, bracoAltura, 0.0);
	glRotatef(theta[4], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, lelb_node.m);
	lelb_node.f = cotoveloEsquerdo;
	lelb_node.sibling = NULL;
	lelb_node.child = &lla_node;

	glLoadIdentity();
	glTranslatef(0, 0, 0.0);
	glRotatef(theta[5], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, rua_node.m);
	rua_node.f = bracoDireito;
	rua_node.sibling = NULL;
	rua_node.child = &relb_node;

	glLoadIdentity();
	glTranslatef(0.0, bracoAltura, 0.0);
	glRotatef(theta[4], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, relb_node.m);
	relb_node.f = cotoveloDireito;
	relb_node.sibling = NULL;
	relb_node.child = &rla_node;

	glLoadIdentity();
	glTranslatef(-corpoRaio / 2, 0.1 * pernaAltura, 0.0);
	glRotatef(theta[7], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, lul_node.m);
	lul_node.f = pernaEsquerda;
	lul_node.sibling = &rul_node;
	lul_node.child = &lknee_node;

	glLoadIdentity();
	glTranslatef(corpoRaio / 2, 0.1 * pernaAltura, 0.0);
	glRotatef(theta[9], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, rul_node.m);
	rul_node.f = pernaDireita;
	rul_node.sibling = NULL;
	rul_node.child = &rknee_node;

	glLoadIdentity();
	glTranslatef(0.0, cotoveloRaio / 2, 0.0);
	glRotatef(theta[4], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, lla_node.m);
	lla_node.f = left_lower_arm;
	lla_node.sibling = NULL;
	lla_node.child = &lhand_node;

	glLoadIdentity();
	glTranslatef(0.0, cotoveloRaio / 2, 0.0);
	glRotatef(theta[4], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, rla_node.m);
	rla_node.f = right_lower_arm;
	rla_node.sibling = NULL;
	rla_node.child = &rhand_node;

	glLoadIdentity();
	glTranslatef(0.0, antebracoAltura, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, rhand_node.m);
	rhand_node.f = rightHand;
	rhand_node.sibling = NULL;
	rhand_node.child = NULL;

	glLoadIdentity();
	glTranslatef(0.0, antebracoAltura, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, lhand_node.m);
	lhand_node.f = leftHand;
	lhand_node.sibling = NULL;
	lhand_node.child = NULL;

	glLoadIdentity();
	glTranslatef(0.0, pernaAltura, 0.0);
	glRotatef(theta[10], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, lknee_node.m);
	lknee_node.f = joelhoEsquerdo;
	lknee_node.sibling = NULL;
	lknee_node.child = &lll_node;

	glLoadIdentity();
	glTranslatef(0.0, joelhoRaio / 2, 0.0);
	glRotatef(theta[8], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, lll_node.m);
	lll_node.f = left_lower_leg;
	lll_node.sibling = NULL;
	lll_node.child = &lfoot_node;

	glLoadIdentity();
	glTranslatef(0.0, canelaAltura, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, lfoot_node.m);
	lfoot_node.f = peEsquerdo;
	lfoot_node.sibling = NULL;
	lfoot_node.child = NULL;

	glLoadIdentity();
	glTranslatef(0.0, pernaAltura, 0.0);
	glRotatef(theta[10], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, rknee_node.m);
	rknee_node.f = joelhoDireito;
	rknee_node.sibling = NULL;
	rknee_node.child = &rll_node;

	glLoadIdentity();
	glTranslatef(0.0, joelhoRaio / 2, 0.0);
	glRotatef(theta[10], 1.0, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, rll_node.m);
	rll_node.f = right_lower_leg;
	rll_node.sibling = NULL;
	rll_node.child = &rfoot_node;

	glLoadIdentity();
	glTranslatef(0.0, canelaAltura, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, rfoot_node.m);
	rfoot_node.f = peDireito;
	rfoot_node.sibling = NULL;
	rfoot_node.child = NULL;

	glLoadIdentity();
}
//FIM INICIALIZAÇÃO ÁRVORE

void keyboard(unsigned char key, int x, int y)
{
	opcao = key;
}

int main(int argc, char **argv)
{
	//Menu de operações
	printf("MENU:\n");
	printf("0 - Levantar o braço.\n");
	printf("1 - Abaixar o braço.\n");
	printf("2 - Voltar para a posição inicial.\n");
	printf("3 - Pular.\n");
	printf("4 - Levantar braço lateral.\n");
	printf("5 - Acenar.\n");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 400);
	glutCreateWindow("Revolucao das maquinas");
	myinit();
	glutReshapeFunc(myReshape);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}