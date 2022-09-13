#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>

// gcc boneco_neve.c -lglut -lGL -lGLU -lm -o boneco_neve && ./boneco_neve

static GLfloat ROTACAO_Y = 0.0f;
static GLfloat ROTACAO_X = 0.0f;

void ChangeSize(int comprimento, int altura){  
    GLfloat fAspect; 
    if(altura == 0)  
        altura = 1;  
    glViewport(0, 0, comprimento, altura);  
    fAspect = (GLfloat)comprimento/(GLfloat)altura;  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();   
    gluPerspective(35.0f, fAspect, 1.0, 40.0);  
  
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();  
}  

void SetupRC(){  
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };  
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };  
    GLfloat  lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };  
  
    glEnable(GL_DEPTH_TEST);    // Hidden surface removal  
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out  
    glEnable(GL_CULL_FACE);     // Do not calculate inside  
  
    // Enable lighting  
    glEnable(GL_LIGHTING);  
  
    // Setup and enable light 0  
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);  
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);  
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);  
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);  
    glEnable(GL_LIGHT0);  
  
    // Enable color tracking  
    glEnable(GL_COLOR_MATERIAL);  
      
    // Set Material properties to follow glColor values  
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  
  
    // Black blue background  
    glClearColor(0.25f, 0.25f, 0.50f, 1.0f);  

}  
//inputs
void SpecialKeys(int key, int x, int y){  
    if(key == GLUT_KEY_LEFT)  
        ROTACAO_Y -= 5.0f;  
  
    if(key == GLUT_KEY_RIGHT)  
        ROTACAO_Y += 5.0f;  
    
    if(key == GLUT_KEY_UP)
        ROTACAO_X += 5.0f;

    if(key == GLUT_KEY_DOWN)
        ROTACAO_X -= 5.0f;

    ROTACAO_Y = (GLfloat)((const int)ROTACAO_Y % 360);  
    ROTACAO_X = (GLfloat)((const int)ROTACAO_X % 360);  
  
    // Refresh the Window  
    glutPostRedisplay();  
}

void RenderScene(void){  

    GLUquadricObj *pObj;  // Cria um objeto quádrico
      
    // Clear the window with current clearing color  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
    // Save the matrix state and do the rotations  
    glPushMatrix(); // salva a matriz de modelos 

	// Move object back and do in place rotation  
	glTranslatef(0.0f, -1.0f, -5.0f); // faz uma translação na matriz de modelos
	glRotatef(ROTACAO_Y, 0.0f, 1.0f, 0.0f);  // faz uma rotação na matriz de modelos
    glRotatef(ROTACAO_X, 1.0f, 0.0f, 0.0f);
    // essas operações só se aplicam aos modelos existentes, I guess

	// Desenha o objeto
	pObj = gluNewQuadric();  
	gluQuadricNormals(pObj, GLU_SMOOTH);  

	// Base
    glColor3f(1.0f, 1.0f, 1.0f);  
	glPushMatrix();
		glTranslatef(0.0f,0.0f,0.0f); // posiciona a esfera do corpo abaixo de todas (na origem)
		gluSphere(pObj, 0.48f, 26,13); // maior esfera
	glPopMatrix();

    // Botão  Baixo
    glColor3f(0.0f, 0.0f, 0.0f);  
    glPushMatrix();
		glTranslatef(0.0f,0.1f,0.48f);
		gluSphere(pObj, 0.025f, 26,13); 
	glPopMatrix();

	// Corpo
    glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		glTranslatef(0.0f,0.5f,0.0f); // posiciona a esfera em y = 0.5, portanto abaixo da cabeça, mas acima da base
		gluSphere(pObj, 0.36f, 26,13); // (cria uma esfera maior que a da cabeça)
	glPopMatrix();

    // Botão Corpo 
    glColor3f(0.0f, 0.0f, 0.0f);  
    glPushMatrix();
		glTranslatef(0.0f,0.6f,0.36f);
		gluSphere(pObj, 0.025f, 26,13); // (cria a maior esfera)
	glPopMatrix();

    // Braços
    // Braço Esquerdo
    glColor3f(0.588f, 0.23f, 0.09f);
    glPushMatrix();
        glTranslatef(-0.30f,0.6f,0.0f); // posiciona o braço na altura do corpo, a esquerda dele
        glRotatef(-90, -0.30f, 0.6f, 0.0f); // rotaciona o cilindro pra apontar para esquerda
        gluCylinder(pObj, 0.04f, 0.01f, 0.40f, 26, 13);
    glPopMatrix();

    // Braços
    // Braço Direito
    glPushMatrix();
        glTranslatef(0.30f,0.6f,0.0f); // posiciona o braço na altura do corpo, a esquerda dele
        glRotatef(90, 0.30f, 0.6f, 0.0f); // rotaciona o cilindro pra apontar para esquerda
        gluCylinder(pObj, 0.04f, 0.01f, 0.40f, 26, 13);
    glPopMatrix();

    

	// Cabeça
    glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix(); // save transform matrix state
		glTranslatef(0.0f, 1.0f, 0.0f); // rotaciona a matriz de modelos
		gluSphere(pObj, 0.24f, 26, 13); // cria uma esfera com raio .24, 
        //                                 26 linhas de longitude e 13 de latitude 
        //                                              (cima/baixo)      (esq/dir)
        // todas as transformações anteriores são aplicadas nessa esfera
	glPopMatrix(); // restaura a matriz, portanto garantindo que as transformações feitas só sejam
    // aplicadas na esfera que criou

    // Nariz 
	// define a cor da matriz como laranja (não altera a cor dos objetos que já existem)
	glColor3f(1.0f, 0.4f, 0.51f);  
	glPushMatrix();
		glTranslatef(0.0f, 1.0f, 0.2f); // 0.2f no z faz com que o cone apareça em frente a esfera da cabeça
		gluCylinder(pObj, 0.04f, 0.0f, 0.3f, 26, 13); // cria um cilindro com 0.04 raio de base
        //  0 raio de topo (portanto gera um cone) 0.3 altura 26 linhas de longitude e 13 de latitude         
	glPopMatrix();  

	// Olhos
    // Olho Direito
    glColor3f(0.0f,0.0f,0.0f);
    glPushMatrix();
        glTranslatef(0.1f,1.1f,0.2f); // criar duas esferas e posicionar deslocado do centro da cabeça
        gluSphere(pObj, 0.025f, 26, 13); // cria uma pequena esfera
    glPopMatrix();
    
    // Olho esquerdo
    glColor3f(0.0f,0.0f,0.0f);
    glPushMatrix();
        glTranslatef(-0.1f,1.1f,0.2f); // criar duas esferas e posicionar deslocado do centro da cabeça
        gluSphere(pObj, 0.025f, 26, 13); // cria uma pequena esfera
    glPopMatrix();

    // Borda Chapéu
    glPushMatrix();
        glTranslatef(0.0f,1.24f,0.0f); // posiciona a borda acima da cabeça
        glRotatef(90,1,0,0);             // rotaciona a borda
        glTranslatef(0.0f, 0.0f, 0.05f); // para que ela esteja orientada no eixo y
        gluDisk(pObj, 0.0f, .36f, 26, 13); // cria um disco de raio .36
    glPopMatrix();

	// Chapéu
    glPushMatrix();
        glTranslatef(0.0f,1.24f,0.0f); // posiciona
        glRotatef(90,1,0,0);              // rotaciona o chapéu 
        glTranslatef(0.0f, 0.0f, -0.45f); // para que ele esteja orientado no eixo y
        gluCylinder(pObj, 0.25f, 0.25f, 0.5f, 26,13); // cria um cilindro de raio .25 e altura .5
    glPopMatrix();
    //staff
        glColor3f(0.588f, 0.23f, 0.09f);
    glPushMatrix();
        glTranslatef(-0.7f,-0.3f,0.0f); 
        glRotatef(-90, 9.30f, 0.0f, 0.0f); // rotaciona o cilindro pra apontar para esquerda
        gluCylinder(pObj, 0.04f, 0.01f, 1.40f, 26, 13);
    glPopMatrix();

    // Restore the matrix state  
    glPopMatrix();  
    // Buffer swap  
    glutSwapBuffers();  

}  

int main(int argc, char *argv[]){

    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // define o modo de display
    glutInitWindowSize(800, 600);  // inicializa a janela, com tamanho sendo o argumento passado
    glutCreateWindow("Boneco de Neve");  // cria a janela
    glutReshapeFunc(ChangeSize);  // da resize na janela, se necessário
    glutSpecialFunc(SpecialKeys); // define o que fazer ao receber um input
    glutDisplayFunc(RenderScene); // cria a cena e renderiza ela
    SetupRC();  
    glutMainLoop();  
    
    return 0;
}

