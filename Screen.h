#ifndef SCREEN_H
#define SCREEN_H

#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>
#include <utility>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <cmath>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Objeto.h"
#include "Options.h"
#include "Calculos.h"
#include "Ray.h"

using namespace std;


class Screen
{
private:
    std::vector<int> matrizCores;
    Options options;
    std::vector<Objeto *> objects;
    double elapsed;
    Vec3f camOrigin, camDirection;
    
public:
    Matrix44f cameraToWorld = 
    Matrix44f(
    0.94 , 0 , -0.32, 0, 
    -0.17, 0.83, -0.52, 0, 
    0.27 , 0.55, 0.78  , 0, 
    8.20 , 8.37, 17.93, 1
    ); 
    Screen();
    ~Screen();
    void render();
    void drawScene();
    void setup();
    void resize(int w, int h);
    
    void setCamOrigin(Vec3f camOrigin){
        this->camOrigin = camOrigin;
    }
    void setCamDirection(Vec3f camDir){
        this->camDirection = camDir;
    }

    Vec3f getCamOrigin(){
        return this->camOrigin;
    }
    Vec3f getCamDirection(){
        return this->camDirection;
    }
    void setMatricCores(std::vector<int> matrizCores){
        this->matrizCores = matrizCores;
    }
    std::vector<int> getMatrizCores(){
        return this->matrizCores;
    }
    void setOptions(Options op){
        this->options = op;
    }
    Options getOptions(){
        return this->options;
    }
    std::vector<Objeto *> getObjects(){
        return this->objects;
    }
    void setObjects(std::vector<Objeto *> &ob){
        this->objects = ob;
    }
};

Screen::Screen()
{

}

Screen::~Screen()
{
}


void Screen::render()
{
    const std::vector<Objeto *> objects = this->getObjects(); // registra os objetos
    Vec3f *framebuffer = new Vec3f[options.width * options.height]; // cria o buffer
    Vec3f *pix = framebuffer; // copia o buffer aqui
    float scale = tan(Calculos().deg2rad(options.fov * 0.5)); // escala pra montar a tela
    float imageAspectRatio = options.width / (float)options.height; // aqui pra manter aspecto
    cameraToWorld.multVecMatrix(Vec3f(0), camOrigin); // transformação da camera
    Ray ray = Ray(); // cria o raio
    
    for (uint32_t j = 0; j < options.height; ++j) { // varre as linhas
        for (uint32_t i = 0; i < options.width; ++i) { // varre as colunas
            float x = (2 * (i + 0.5) / (float)options.width - 1) * imageAspectRatio * scale;
            float y = (1 - 2 * (j + 0.5) / (float)options.height) * scale;
            cameraToWorld.multDirMatrix(Vec3f(x, y, -1), camDirection);
            camDirection.normalize();
            *(pix++) = ray.castRay(camOrigin, camDirection, objects); // dispara em cada pixel
        }
    }
    // loop pra pintar a tela
    glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
        int x = 1;
        int y = 1; 
      
        for (uint32_t i = 0; i <= options.width * options.height; i++) {
            if((framebuffer[i].x + framebuffer[i].y + framebuffer[i].z) > 0){
                float r = (Calculos().clamp(0, 1, framebuffer[i].x));
                float g = (Calculos().clamp(0, 1, framebuffer[i].y));
                float b = (Calculos().clamp(0, 1, framebuffer[i].z));
                glColor3f(r, g, b);
                glVertex2i(x, y);
            }else{
                glColor3f(0, 0, 0);
                glVertex2i(x, y);
            }
            if(x == options.width){
                x = 1;
                y++;
            }else{
                x++;
            }
        }
     
    glEnd();

	glFlush();

    delete[] framebuffer;
    
    
}

void Screen::setup(void) 
{
   //glClearColor(1.0, 1.0, 1.0, 0.0); 
}

void Screen::resize(int w, int h)
{
   glViewport(0, 0, w, h); 
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, 500, 0, 500, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
#endif