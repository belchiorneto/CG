#ifndef ESFERA_H
#define ESFERA_H    

#include <cstdlib>
#include <cmath>
#include "Calculos.h"
class Esfera : public Objeto
{
   
public:
    Esfera(Vec3f &c, float &r) : radius(r), radius2(r *r ){
       this->center = c;
    }
    virtual void move(vector<Objeto *> objects)
    {
        if(moving){
            Objeto *pivo;
            for (Objeto * ob: objects) {
                if (ob->nome == "sol") {
                    pivo = ob;                        
                }
                
            }
            
            /* // tentativa fracassada de calcular a orbita da lua em relação ao sol
            if(nome == "lua"){
                if(curva > 0.4){
                    curva = 0.4;
                    multiplicador = multiplicador * -1;
                }else if(curva < -0.4){
                    curva = -0.4;
                    multiplicador = multiplicador * -1;
                }
                curva = curva + 0.1f * multiplicador;
                float angle = -M_PI / speed;
                float s = sin(angle);
                float c = cos(angle);

                center.x = pivo->center.x + curva;
                center.y = pivo->center.y + curva;
                
                // rotate point
                float xnew = center.x * c - center.y * s + curva;
                float ynew = center.x * s + center.y * c + curva;
                

                // translate point back:
                //center.x = xnew + pivo->center.x;
                //center.y = ynew + pivo->center.y;

                /*
                // distancia terra-sol
                float d1 = sqrt(
                    (pivo->center.x - psun.x) * (pivo->center.x - psun.x) +
                    (pivo->center.y - psun.y) * (pivo->center.y - psun.y)
                );
                
                // distancia lua-terra
                float d2 = sqrt(
                    (center.x - pivo->center.x) * (center.x - pivo->center.x) +
                    (center.y - pivo->center.y) * (center.y - pivo->center.y)
                );
                float xnew, ynew;
                if(pivo->center.x > 0 && pivo->center.y > 0){
                    xnew = d1 * cos(angle) + d2 * cos(angleEarth);
                    ynew = d1 * sin(angle) + d2 * sin(angleEarth);
                }else if(pivo->center.x < 0 && pivo->center.y > 0){
                    xnew = d1 * -cos(angle) + d2 * -cos(angleEarth);
                    ynew = d1 * sin(angle) + d2 * sin(angleEarth);
                }else if(pivo->center.x < 0 && pivo->center.y < 0){
                    xnew = d1 * -cos(angle) + d2 * -cos(angleEarth);
                    ynew = d1 * -sin(angle) + d2 * -sin(angleEarth);
                }else if(pivo->center.x > 0 && pivo->center.y < 0){
                    xnew = d1 * cos(angle) + d2 * cos(angleEarth);
                    ynew = d1 * -sin(angle) + d2 * -sin(angleEarth);
                }
                
                // translate point back:
                
                center.x = xnew;
                center.y = ynew;

                cout<<"novo x:" << center <<"\n";
                cout<<"novo x:" << pivo->center <<"\n";
                

            }else{
                */
            float angle = -M_PI / speed;
            float s = sin(angle);
            float c = cos(angle);

            center.x -= pivo->center.x;
            center.y -= pivo->center.y;
            
            // rotate point
            float xnew = center.x * c - center.y * s;
            float ynew = center.x * s + center.y * c;
            

            // translate point back:
            center.x = xnew + pivo->center.x;
            center.y = ynew + pivo->center.y;
                
           // }
          
        }
    }

    virtual void rotate(float angle)
    {    }

    void setCenter(Vec3f c);
    void setPivo(Esfera *p);
    void setNome(char *n);
    void setDir(Vec3f d);
    void setColor(Vec3f c);
    void setSpeed(float s);
    void setMoving(bool move);
    // funcao principal pra calcular a interseção raio-esfera
    /*
        a.t² + 2.b.t + c = 0
    */

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
    
    float radius, radius2, curva;
    Vec3f dir;
    bool moving = false;
    int multiplicador = 1;
    
};
void Esfera:: setCenter(Vec3f c){
    this->center = c;
}
void Esfera:: setDir(Vec3f dir){
    this->dir = dir;
}
void Esfera:: setSpeed(float s){
    this->speed = s;
}
void Esfera:: setMoving(bool move){
    this->moving = move;
}
void Esfera:: setNome(char * n){
    this->nome = n;
}
void Esfera::setColor(Vec3f c){
    this->color = c;
}
#endif