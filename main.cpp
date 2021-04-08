#include <GL/glew.h>
#include <GL/freeglut.h>

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstdint>
#include <cmath>

#include <chrono>

#include "geometry.h"
#include "Objeto.h"
#include "Esfera.h"
#include "Cilindro.h"
#include "Ray.h"
#include "Options.h"
#include "Screen.h"
#include "Timer.h"

using namespace std;
using namespace std::chrono;

vector<Objeto *> objects;
Options options;
Screen tela;
void animate(double speed);
Timer t = Timer();

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
int main(int argc, char **argv)
{   
    
    options.title = "CG 2021";
    options.width = 640;
    options.height = 480;
    
    
    Vec3f pos = {-12,-2,0};
    float radius = 1.5;
    
    Sphere *sun = new Sphere(pos, radius);
    (*sun).setNome("sol"); // gambiarrinha ;(
    (*sun).setColor(Vec3f(1,0.7,0));
    objects.push_back(sun); // sun

    pos = {-4.69,-2,0};
    radius = 0.09;
    Sphere *mercury = new Sphere(pos, radius);
    (*mercury).setDir(Vec3f(0,1,0));
    (*mercury).setSpeed(16);
    (*mercury).setMoving(true); // gatilho pra movimento
    (*mercury).setColor(Vec3f(1,0.7,0));
    (*mercury).setNome("mercury"); 

    objects.push_back(mercury); // Mercury


    pos = {-5.1,-2,0};
    radius = 0.15;
    Sphere *venus = new Sphere(pos, radius);
    (*venus).setDir(Vec3f(0,1,0));
    (*venus).setSpeed(24);
    (*venus).setMoving(true); // gatilho pra movimento
    (*venus).setNome("venus"); 

    objects.push_back(venus); // Venus

    pos = {-6.0,-2,0};
    radius = 0.20;
    Sphere *earth = new Sphere(pos, radius);
    (*earth).setDir(Vec3f(0,1,0));
    (*earth).setSpeed(32);
    (*earth).setMoving(true); // gatilho pra movimento
    (*earth).setColor(Vec3f(0,0.2,1));
    (*earth).setNome("terra"); 
    
    objects.push_back(earth); // earth

    pos = {-6.0,-2.5,0};
    radius = 0.061;
    Sphere *moon = new Sphere(pos, radius);
    (*moon).setDir(Vec3f(0,1,0));
    (*moon).setSpeed(16);
    (*moon).setMoving(true); // gatilho pra movimento
    (*moon).setColor(Vec3f(1,0.9,0.7));
    (*moon).setNome("lua"); 
    
    objects.push_back(moon); // moon

    pos = {-6.8,-2,0};
    radius = 0.25;
    Sphere *mars = new Sphere(pos, radius);
    (*mars).setDir(Vec3f(0,1,0));
    (*mars).setSpeed(30);
    (*mars).setMoving(true); // gatilho pra movimento
    (*mars).setNome("marte"); 
    objects.push_back(mars); // mars

    pos = {-3.1,-2,0};
    radius = 0.56;
    Sphere *jupiter = new Sphere(pos, radius);
    (*jupiter).setDir(Vec3f(0,1,0));
    (*jupiter).setSpeed(18);
    (*jupiter).setMoving(true); // gatilho pra movimento
    (*jupiter).setNome("jupiter");

    objects.push_back(jupiter); // Jupiter
    
    pos = {-1,-2,0};
    radius = 0.40;
    Sphere *saturn = new Sphere(pos, radius);
    (*saturn).setDir(Vec3f(0,1,0));
    (*saturn).setSpeed(36);
    (*saturn).setMoving(true); // gatilho pra movimento
    (*saturn).setNome("saturno");
    objects.push_back(saturn); // Saturn

    pos = {4.4,-2,0};
    radius = 0.15;
    Sphere *uranus = new Sphere(pos, radius);
    (*uranus).setDir(Vec3f(0,1,0));
    (*uranus).setSpeed(18);
    (*uranus).setMoving(true); // gatilho pra movimento
    (*uranus).setNome("uranus");
    objects.push_back(uranus); // Uranus

    

    uint32_t numSpheres = 10;
    uint32_t numCilindros = 3;
    gen.seed(0);
    for (uint32_t i = 0; i < numSpheres; ++i) {
        Vec3f randPos((0.5 - dis(gen)) * 15, (0.5 - dis(gen)) * 15, (0.5 + dis(gen) * 15));
        float randRadius = (0.8 - dis(gen) * 1.3);
        //objects.push_back(new Sphere(randPos, randRadius));
        
    }
    for (uint32_t i = 0; i < numCilindros; ++i) {
        Vec3f dirCilindro = {1,0,0};
        Vec3f randPos((0.5 - dis(gen)) * 10, (0.5 - dis(gen)) * 10, (0.5 + dis(gen) * 10));
        float randRadius = (0.8 - dis(gen) * 0.5);
        float height = (0.8 - dis(gen) * 0.2);
        //objects.push_back(new Cilindro(randPos, randRadius, height, dirCilindro));
    }

    tela = Screen();
    tela.setObjects(objects);
    tela.setOptions(options);
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(options.width, options.height);
	glutInitWindowPosition(10, 10);
	glutCreateWindow(options.title);
	init();
	glutDisplayFunc(draw);
    glutTimerFunc(33, timerCB, 33);             // redraw only every given millisec
    
	glutMainLoop(); 
    
   
}