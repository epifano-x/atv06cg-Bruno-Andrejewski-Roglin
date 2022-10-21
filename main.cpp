#include <GL/gl.h> 					//biblioteca que permite todas as chamadas da API openGL
#include <GL/glut.h> 				//biblioteca que permite a manipulação de janelas

static float moveponto = 89; //para mover o ponto em incrementais (1 em 1)
static float movex = -50;
GLint direcao = 1;   // para saber a direção do ponto no eixo y (+ ou -)
static float escopo = 90;
static float controle = 0;

void timerPonto(int passo){
    if (direcao == 1){
        moveponto+=0.8;
        movex+=0.1+controle;
        if(moveponto >= escopo){
            direcao = -1;
            if(escopo> 20){
                escopo = escopo/2;
            controle +=0.05;
            }else if(escopo >1){
                escopo = escopo/1.5;
                controle +=0.1;
            }else{
            direcao=3;
            }
        }
    }
    else if(direcao == -1){
        moveponto-=1;
        movex+=0.1+controle;
        if(moveponto <= 3){
            direcao = 1;
        }
    }
    glutPostRedisplay();                 //chama a função desenha toda vez que for necessária
    glutTimerFunc(10,timerPonto,1);      //precisamos chamar a função timer toda vez, Ele executa essa função timer e entra aqui novamente. Até eu querer sair da função timer (neste caso, não queremos sair)
}

void cartesiano(){
    glLineWidth(1);               //adiciona espessura a linha desenhada
    glColor3f(0,0,0);             //adiciona cor às linhas
    glBegin(GL_LINES);            //lBegin e glEnd delimitam os vértices que definem uma primitiva ou um grupo de primitivas semelhantes (definida como parâmetro).
        glVertex2f(-100.0, 0.0);   //desenha uma linha no eixo -50x até o ponto do eixo 50x
        glVertex2f(100, 0.0);
    glEnd();
}

void pontoY(){
    glPointSize(20);                   //adiciona espessura do ponto
    glBegin(GL_POINTS);                //glBegin e glEnd delimitam os vértices que definem uma primitiva ou um grupo de primitivas semelhantes (definida como parâmetro).
        glColor3f(0,1,0);              //adiciona cor
        glVertex2f(movex,moveponto);       //desenha um ponto na coordenada x, y, onde y vai ser a variável que criamos para deslocar o ponto neste eixo
    glEnd();
}


void desenhaObjetos(void){
    glClear(GL_COLOR_BUFFER_BIT);      //buffer padrão (limpa a tela toda vez que a função é chamada)

	glMatrixMode(GL_PROJECTION);       //projeção dos pontos definidos no plano cartesiano
    glLoadIdentity();                  //carrega a projeção
    gluOrtho2D(-100,100,-100,100);     // define o tamanho do plano cartesiano
    glMatrixMode(GL_MODELVIEW);        // projeção do tipo modelo
    glLoadIdentity();                  // carrega a identidade de projeção de modelo

    glPushMatrix();                    //insere a matriz de transformação corrente na pilha
        pontoY();                       //chama a função que desenha o ponto
    glPopMatrix();                     //retira a matriz do topo da pilha e torna esta última a matriz de transformação corrente

        glPushMatrix();       //insere a matriz de transformação corrente na pilha
        cartesiano();     //chama a função que desenha o plano cartesiano
    glPopMatrix();        //retira a matriz do topo da pilha e torna esta última a matriz de transformação corrente


	glutSwapBuffers();                 //Executa uma troca de buffer na camada em uso para a janela atual (para que consiga trabalhar com dois buffers de)
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
        case 'a':
            glutTimerFunc(10,timerPonto,1);
            break;
        case 'A':
            glutTimerFunc(10,timerPonto,1);
            break;

    }

    glutPostRedisplay();
}


int main(void){
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);                    //double buffer, pois single ficaria piscando, uma vez que ele tem que desenhar e redesenhar | sistema de cores RGB
    glutInitWindowSize(800,600);                                    //define o tamanho da janela
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-960)/2,
                           (glutGet(GLUT_SCREEN_HEIGHT)-540)/2);    //medidas usadas para posicionar a janela no meio da tela - isso depende da resolução do monitor
	glutCreateWindow("Exemplo Timer");                              //permite a criação de uma janela
    glutDisplayFunc(desenhaObjetos);                                //função de callback - chama a função desenhaObjetos
                glutKeyboardFunc(key);                      // três valores disponíveis (tempo (milissegundos) a o nome da função e valor padrão para retorno)
    glClearColor(1,1,1,0);                                          //informa a cor de fundo da tela (branco)
    glutMainLoop();                                                 //loop infinito - escuta as informações do sistema até encerrar a aplicação
    return 0;                                                       //retorna zero
}
