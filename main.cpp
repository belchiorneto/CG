/*
    Trabalho para nota do semestre 2020.2
    Disciplila: Computação Gráfica
    Professor: Dr. Creto Augusto Vidal (UFC)
    
    Equipe:
    Belchior Neto - Matricula: 384343
    UBIRATAN JUNIOR - Matricula: 397322
*/
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstdint>

#include "geometry.h"
#include "Objeto.h"
#include "solarSystem.h"
#include "Cilindro.h"
#include "Ray.h"
#include "Options.h"
#include "Screen.h"

using namespace std;

// vetor de ponteiros para objetos para guardar tudo o que vai aparcer na tela
vector<Objeto *> objects; 
// algumas opções iniciais
Options options;
// classe principal da tela, onde serão chamadas as funções de raycast e renderização
Screen tela;

void init(); // incializa o Open GL
void setup(void); // configura o open GL com as opções iniciais
void draw(); // mostra a tela
void resize(int w, int h); // redimensiona a tela
/*
    para a animação, executa a cada x milisegundos
    obs.: não consegui resolver o problema com o framerate, 
    imagino que seja uma incompatibilidade com a função interna do 
    openGL (animate())
*/
void timerCB(int millisec); 

/*
    funçãozinha para movimentar a camera 
    (a,d, w,s, q,e) movimenta posição nos eixos x,y,z
    (4,6, 8,2, 7,9) movimenta direção nos eixos x,y,z
*/
void MovimetoCamera(unsigned char key, int x, int y);

int main(int argc, char **argv)
{   
    /*
     loop principal para carregar os objetos da classe SolarSystem
     no vetor de ponteiros objects
    */
    for (Objeto * planeta: SolarSystem().getPlanets()) {
        objects.push_back(planeta);
    }
    
    /*
        esta seção não estará ativa na apresentação, mas basicamente carrega algumas
        esferas em posições aleatorias com tamanhos aleatórios
    */
    uint32_t numSpheres = 10;
    gen.seed(0);
    for (uint32_t i = 0; i < numSpheres; ++i) {
        Vec3f randPos((0.5 - dis(gen)) * 15, (0.5 - dis(gen)) * 15, (0.5 + dis(gen) * 15));
        float randRadius = (0.8 - dis(gen) * 1.3);
        //objects.push_back(new Sphere(randPos, randRadius));
        
    }

    /*
        esta seção não estará ativa na apresentação, a idéia era printar na tela
        alguns cilindros em posições aleatórias com tamanhos aleatórios
        não consegui concluir a classe a tempo
    */
    uint32_t numCilindros = 3;
    for (uint32_t i = 0; i < numCilindros; ++i) {
        Vec3f dirCilindro = {1,0,0};
        Vec3f randPos((0.5 - dis(gen)) * 10, (0.5 - dis(gen)) * 10, (0.5 + dis(gen) * 10));
        float randRadius = (0.8 - dis(gen) * 0.5);
        float height = (0.8 - dis(gen) * 0.2);
        //objects.push_back(new Cilindro(randPos, randRadius, height, dirCilindro));
    }

    tela = Screen(); // carrega a tela
    tela.setObjects(objects); // seta os objetos
    tela.setOptions(options); // seta as opções
    // abaixo variáveis do glut
    glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(options.width, options.height);
	glutInitWindowPosition(10, 10);
	glutCreateWindow(options.title);
	init();
	glutDisplayFunc(draw);
    glutTimerFunc(33, timerCB, 33); // para a animacao
    glutKeyboardFunc(MovimetoCamera);
    glutMainLoop(); 
    
   
}

void draw(){
    tela.render();
}
void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
}
void setup(void){
    tela.setup();
}

void resize(int w, int h){
    tela.setup();
}

void timerCB(int millisec)
{
    glutTimerFunc(millisec, timerCB, millisec);
    for (auto& ob : objects)
    {
        ob->move(objects); // change object position here
    }
    glutPostRedisplay();
}

void MovimetoCamera(unsigned char key, int x, int y)
{

    switch (key) {
            case 'w':
                    tela.cameraToWorld.x[3][1] += 0.4f; // sobe (origem.y ++)
                    break;
            case 's':
                    tela.cameraToWorld.x[3][1] -= 0.4f; // desce (origem.y --)
                    break;
            case 'a':
                    tela.cameraToWorld.x[3][0] += 0.4f; // esquerda (origem.x ++)
                    break;
            case 'd':
                    tela.cameraToWorld.x[3][0] -= 0.4f; // direita (origem.x --)
                    break;
            case 'q':
                    tela.cameraToWorld.x[3][2] += 0.4f; // zoom in (origem.x ++)
                    break;
            case 'e':
                    tela.cameraToWorld.x[3][2] -= 0.4f; // zoom out (origem.z --)
                    break;
            case '4':
                    tela.cameraToWorld.x[2][0] -= 0.03f; // gira para esquerda (dir.x ++)
                    break;
            case '6':
                    tela.cameraToWorld.x[2][0] += 0.03f; // gira para direita (dir.x --)
                    break;
            case '8':
                    tela.cameraToWorld.x[2][1] += 0.03f; // gira para cima (dir.y ++)
                    break;
            case '2':
                    tela.cameraToWorld.x[2][1] -= 0.03f; // gira para baixo (dir.y --)
                    break;
            case '7':
                    tela.cameraToWorld.x[2][2] += 0.03f; // (dir.z ++)
                    break;
            case '9':
                    tela.cameraToWorld.x[2][2] -= 0.03f; //(dir.z --)
                    break;
            
    }
    
}