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

#include "Timer.h"
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
    Timer t;
    double elapsed;
public:
    Screen();
    ~Screen();
    void render();
    void drawScene();
    void setup();
    void resize(int w, int h);
    
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
    elapsed = t.elapsed();
}

Screen::~Screen()
{
}


void Screen::render()
{
    
    double iniRender = t.elapsed();
    const Options options = Screen::getOptions();
    const std::vector<Objeto *> objects = this->getObjects();
    Vec3f *framebuffer = new Vec3f[options.width * options.height];
    Vec3f *pix = framebuffer;
    float scale = tan(Calculos().deg2rad(options.fov * 0.5));
    float imageAspectRatio = options.width / (float)options.height;
    Vec3f orig, dir;
    options.cameraToWorld.multVecMatrix(Vec3f(0), orig);
    Ray ray = Ray();
    
    for (uint32_t j = 0; j < options.height; ++j) {
        for (uint32_t i = 0; i < options.width; ++i) {
            float x = (2 * (i + 0.5) / (float)options.width - 1) * imageAspectRatio * scale;
            float y = (1 - 2 * (j + 0.5) / (float)options.height) * scale;
            Vec3f dir = {0,0,0};
            options.cameraToWorld.multDirMatrix(Vec3f(x, y, -1), dir);
            dir.normalize();
            *(pix++) = ray.castRay(orig, dir, objects);
            
        }
    }
    
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