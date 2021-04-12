#ifndef PLANE_H
#define PLANE_H    

#include <cstdlib>
#include <cmath>
#include "Calculos.h"
#include "Objeto.h"

class Plane : public Objeto
{
   
public:
    Plane(Vec3f &center, Vec3f &n){
       this->center = center;
       this->planeNormal = n;
    }
    virtual void move(vector<Objeto *> objects)
    {
       
    }

    virtual void rotate(float angle)
    {    }

    void setCenter(Vec3f c);
    void setPivo(Plane *p);
    void setNome(char *n);
    void setDir(Vec3f d);
    void setColor(Vec3f c);
    void setSpeed(float s);
    void setMoving(bool move);
    
    bool intersect(const Vec3f &orig, const Vec3f &dir, float &t) const
    {
        Vec3f diff = orig - center;
        double denominator = dir.dotProduct(planeNormal);
        if (denominator > 1e-6) { 
            Vec3f dist = orig - center; 
            t = dist.dotProduct(planeNormal) / denominator; 
        }
        return (t >= 0); 
    }
    
    void getSurfaceData(const Vec3f &Phit, Vec3f &Nhit, Vec2f &tex) const
    {
        Nhit = Phit - center;
        Nhit.normalize();
        tex.x = Nhit.x;
        tex.y = Nhit.y;
    }
    Vec3f getCenter(){
        return center;
    }
    bool moving = false;
    Vec3f planeNormal;
    
};
void Plane:: setCenter(Vec3f center){
    this->center = center;
}
void Plane:: setSpeed(float speed){
    this->speed = speed;
}
void Plane:: setMoving(bool move){
    this->moving = move;
}
void Plane:: setNome(char * nome){
    this->nome = nome;
}
void Plane::setColor(Vec3f color){
    this->color = color;
}
#endif