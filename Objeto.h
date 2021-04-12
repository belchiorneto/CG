#ifndef OBJETO_H
#define OBJETO_H

#include "geometry.h"
#include "Objeto.h"
#include <limits>
#include <random>
#include <vector>   

using namespace std;

/*
    Função genérica para armazenar as informações de 
    um objeto a ser printado na tela usando ray-trace
*/
const float kInfinity = std::numeric_limits<float>::max();
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0, 1);
class Objeto
{
 public:
    Objeto() : color(dis(gen), dis(gen), dis(gen)) {}
    virtual ~Objeto() {}
    virtual bool intersect(const Vec3f &, const Vec3f &, float &) const = 0;
    virtual void getSurfaceData(const Vec3f &, Vec3f &, Vec2f &) const = 0;
    virtual void move(vector<Objeto *> objects) = 0;
    
    Vec3f color, center;
    char *nome;
    float speed;
};
#endif