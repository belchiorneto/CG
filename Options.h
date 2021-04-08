#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>
#include <string>
#include "geometry.h"

using namespace std;

struct Options
{
    uint32_t width;
    uint32_t height;
    float fov = 50.45;
    Matrix44f cameraToWorld = 
    Matrix44f(0.945519, 0, -0.325569, 0, -0.179534, 0.834209, -0.521403, 0, 0.271593, 0.551447, 0.78876, 0, 4.208271, 8.374532, 17.932925, 1); 
 

    char* title;
};

#endif