#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>

static GLfloat ROTACAO_Y = 0.0f;
static GLfloat ROTACAO_X = 0.0f;
float coordenadaX = 0.9f;
float coordenadaZ = 1.5f;

void ChangeSize(int comprimento, int altura){  
    GLfloat fAspect;  
  
    // Prevent a divide by zero  
    if(altura == 0)  
        altura = 1;  
  
    // Set Viewport to window dimensions  
    glViewport(0, 0, comprimento, altura);  
  
    fAspect = (GLfloat)comprimento/(GLfloat)altura;  
  
    // Reset coordinate system  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
  
    // Produce the perspective projection  
    gluPerspective(35.0f, fAspect, 1.0, 40.0);  
  
    glMatrixMode(GL_MODELVIEW);
    // Applies subsequent matrix operations to the modelview matrix stack. 
    glLoadIdentity();  
}  

void SetupRC(){  

    // Light values and coordinates  
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

void SpecialKeys(int key, int x, int y){  
    // lida com o input de teclas do teclado
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

    GLUquadricObj *ObjetoPrincipal;  // Cria um objeto quádrico
      
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
	ObjetoPrincipal = gluNewQuadric();  
	gluQuadricNormals(ObjetoPrincipal, GLU_SMOOTH);  
    glColor3f(1.0f, 1.0f, 1.0f);

    // chao
    glColor3f(0.6f,1.0f,0.6f);
    glPushMatrix();
        glTranslatef(0.0f, 0.125f, -4.0f); 
        glRotatef(90, 0.0f, 0.0f, 1.0f);
        gluCylinder(ObjetoPrincipal, 2.0f, 2.0f, 5.0f, 2, 1);
    glPopMatrix();
    

    // Torre esquerda, fundo 
    glColor3f(0.5f,0.5f,0.5f);
    glPushMatrix();
        glTranslatef(-1.0, 0.625f, -1.5);
        glRotatef(90,1,0,0);             // rotaciona
        glTranslatef(0.0f, 0.0f, 0.0f); // para que esteja orientado no eixo y
        gluCylinder(ObjetoPrincipal, 0.15f, 0.15f, 0.5f, 30, 15);
    glPopMatrix();

        // Telhado da torre
        glColor3f(0.7f,0.4f,0.4f);
        glPushMatrix();
            glTranslatef(-1.0f, 0.625f, -1.5f);
            glRotatef(-90,1,0,0);             // rotaciona
            glTranslatef(0.0f, 0.0f, 0.0f); // para que esteja orientado no eixo y
            gluCylinder(ObjetoPrincipal, 0.18f, 0.0f, 0.35f, 30, 15);
        glPopMatrix();

    // Parede entre torre esquerda atras e torre esquerda frente
    glColor3f(0.5f,0.5f,0.5f);
    glPushMatrix();
        glTranslatef(-1.0f, 0.28f, -1.5f); 
        gluCylinder(ObjetoPrincipal, 0.175f, 0.175f, 1.5f, 2, 1);
    glPopMatrix();

    // Torre direita, fundo 
    glColor3f(0.5f,0.5f,0.5f);
    glPushMatrix();
        glTranslatef(1.0, 0.625f, -1.5);
        glRotatef(90,1,0,0);             // rotaciona
        glTranslatef(0.0f, 0.0f, 0.0f); // para que esteja orientado no eixo y
        gluCylinder(ObjetoPrincipal, 0.15f, 0.15f, 0.5f, 30, 15);
    glPopMatrix();

        // Telhado da torre
        glColor3f(0.7f,0.4f,0.4f);
        glPushMatrix();
            glTranslatef(1.0f, 0.625f, -1.5f);
            glRotatef(-90,1,0,0);             // rotaciona
            glTranslatef(0.0f, 0.0f, 0.0f); // para que esteja orientado no eixo y
            gluCylinder(ObjetoPrincipal, 0.18f, 0.0f, 0.35f, 30, 15);
        glPopMatrix();

    // Parede entre torre esquerda atras e torre esquerda frente
    glColor3f(0.5f,0.5f,0.5f);
    glPushMatrix();
        glTranslatef(1.0f, 0.28f, -1.5f); 
        gluCylinder(ObjetoPrincipal, 0.175f, 0.175f, 1.5f, 2, 1);
    glPopMatrix();

    // Parede entre torre esquerda atras e torre esquerda frente
    glColor3f(0.5f,0.5f,0.5f);
    glPushMatrix();
        glTranslatef(-1.0f, 0.28f, -1.5f); 
        glRotatef(90, 0, 1, 0);
        gluCylinder(ObjetoPrincipal, 0.175f, 0.175f, 2.0f, 2, 1);
    glPopMatrix();

    // Torre frente esquerda
    glColor3f(0.5f,0.5f,0.5f);
    glPushMatrix();
        glTranslatef(-1.0f, 0.625f, 0.0f);
        glRotatef(90,1,0,0);             // rotaciona
        glTranslatef(0.0f, 0.0f, 0.0f); // para que esteja orientado no eixo y
        gluCylinder(ObjetoPrincipal, 0.15f, 0.15f, 0.5f, 30, 15);
    glPopMatrix();

        // Telhado da Torre
        glColor3f(0.7f,0.4f,0.4f);
        glPushMatrix();
            glTranslatef(-1.0f, 0.625f, 0.0f);
            glRotatef(-90,1,0,0);             // rotaciona
            glTranslatef(0.0f, 0.0f, 0.0f); // para que esteja orientado no eixo y
            gluCylinder(ObjetoPrincipal, 0.18f, 0.0f, 0.35f, 30, 15);
        glPopMatrix();

    // Parede entre torre frente esquerda e porta e torre frente direita
    glColor3f(0.5f,0.5f,0.5f);
    glPushMatrix();
        glTranslatef(-0.0f, 0.125f, -0.0f); 
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        glRotatef(-90, 0.0f, 0.0f, 1.0f);
        //glTranslatef(0.10f,0.22f,-0.75f); // -0.5 pois agora essa retângulo está de cabeiça p/ baixo
        gluCylinder(ObjetoPrincipal, 1.0f, 1.0f, 0.35f, 2, 1);
    glPopMatrix();



    // porta
    // torre 5
    glColor3f(0.5f,0.5f,0.5f);
    glPushMatrix();
        glTranslatef(-1.0f, 0.625f, 0.0f);
        glRotatef(90,1,0,0);
        glTranslatef(1.0f, 0.0f, 0.0f);
        gluCylinder(ObjetoPrincipal, 0.2f, 0.2f, 0.5f, 4, 2);
    glPopMatrix();

        // Telhado porta
        glColor3f(0.7f,0.4f,0.4f);
        glPushMatrix();
            glTranslatef(-1.0f, 0.625f, 0.0f);
            glRotatef(-90,1,0,0);
            glTranslatef(1.0f, 0.0f, 0.0f);
            gluCylinder(ObjetoPrincipal, 0.2f, 0.0f, 0.25f, 4, 2);
        glPopMatrix();

    

    // Torre da Direita
    glColor3f(0.5f,0.5f,0.5f);
    glPushMatrix();
        glTranslatef(1.0f, 0.625f, 0.0f);
        glRotatef(90,1,0,0);             // rotaciona
        glTranslatef(0.0f, 0.0f, 0.0f); // para que esteja orientado no eixo y
        gluCylinder(ObjetoPrincipal, 0.15f, 0.15f, 0.5f, 30, 15);
    glPopMatrix();

    // Telhado da Torre
        glColor3f(0.7f,0.4f,0.4f);
        glPushMatrix();
            glTranslatef(1.0f, 0.625f, 0.0f);
            glRotatef(-90,1,0,0);           // rotaciona
            glTranslatef(0.0f, 0.0f, 0.0f); // para que esteja orientado no eixo y
            gluCylinder(ObjetoPrincipal, 0.18f, 0.0f, 0.35f, 30, 15);
        glPopMatrix();


    // Restore the matrix state  
    glPopMatrix();  
    // Buffer swap  
    glutSwapBuffers();  

}  

int main(int argc, char *argv[]){

    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // define o modo de display
    glutInitWindowSize(1300, 700);  // inicializa a janela, com tamanho sendo o argumento passado
    glutCreateWindow("Castelo");  // cria a janela
    glutReshapeFunc(ChangeSize);  // da resize na janela, se necessário
    glutSpecialFunc(SpecialKeys); // define o que fazer ao receber um input
    glutDisplayFunc(RenderScene); // cria a cena e renderiza ela
    SetupRC();  
    glutMainLoop();  
    
    return 0;
}

