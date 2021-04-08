#ifndef ESFERA_H
#define ESFERA_H    

#include <cstdlib>
#include <cmath>
#include "Calculos.h"
class Sphere : public Objeto
{
   
public:
    Sphere(Vec3f &c, float &r) : radius(r), radius2(r *r ){
       this->center = c;
    }
    virtual void move(vector<Objeto *> objects)
    {
        if(moving){
            // gambiarra pra lua
            Vec3f pivo;
            if(nome == "lua"){
                for (Objeto * ob: objects) {
                    if (ob->nome == "terra") {
                        pivo = ob->center;   
                    }
                    
                }
                
            }else{
                for (Objeto * ob: objects) {
                    if (ob->nome == "sol") {
                        pivo = ob->center;                        
                    }
                    
                }
            } 
            double angle = -M_PI / speed;
            float s = sin(angle);
            float c = cos(angle);

            // translate point back to origin:
            center.x -= pivo.x;
            center.y -= pivo.y;
            
            
            // rotate point
            float xnew = center.x * c - center.y * s;
            float ynew = center.x * s + center.y * c;
            

            // translate point back:
            center.x = xnew + pivo.x;
            center.y = ynew + pivo.y;
            if(nome == "lua"){
                cout<<"centro lua: " << center <<"Centro Terra: "<< pivo<<"\n";
            }
          
        }
    }

    virtual void rotate(float angle)
    {    }

    void setCenter(Vec3f c);
    void setPivo(Sphere *p);
    void setNome(char *n);
    void setDir(Vec3f d);
    void setColor(Vec3f c);
    void setSpeed(float s);
    void setMoving(bool move);
    bool intersect(const Vec3f &orig, const Vec3f &dir, float &t) const
    {
        float t0, t1; // solutions for t if the ray intersects
        Vec3f L = orig - center;
        float a = dir.dotProduct(dir);
        float b = 2 * dir.dotProduct(L);
        float c = L.dotProduct(L) - radius2;
        bool resposta = Calculos().baskara(a, b, c, t0, t1);

        if (!resposta) return false;
        if (t0 > t1) std::swap(t0, t1);

        if (t0 < 0) {
            t0 = t1; // if t0 is negative, let's use t1 instead
            if (t0 < 0) return false; // both t0 and t1 are negative
        }

        t = t0;

        return true;
    }
    
    void getSurfaceData(const Vec3f &Phit, Vec3f &Nhit, Vec2f &tex) const
    {
        Nhit = Phit - center;
        Nhit.normalize();
        tex.x = (1 + atan2(Nhit.z, Nhit.x) / M_PI) * 0.5;
        tex.y = acosf(Nhit.y) / M_PI;
    }
    Vec3f getCenter(){
        return center;
    }
    
    float radius, radius2, speed;
    Vec3f dir;
    bool moving = false;
    
};
void Sphere:: setCenter(Vec3f c){
    this->center = c;
}
void Sphere:: setDir(Vec3f dir){
    this->dir = dir;
}
void Sphere:: setSpeed(float s){
    this->speed = s;
}
void Sphere:: setMoving(bool move){
    this->moving = move;
}
void Sphere:: setNome(char * n){
    this->nome = n;
}
void Sphere::setColor(Vec3f c){
    this->color = c;
}
#endif