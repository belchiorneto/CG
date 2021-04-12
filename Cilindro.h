#ifndef CILINDRO_H
#define CILINDRO_H    

#include <cstdlib>
#include "Calculos.h"
#include "Objeto.h"

class Cilindro : public Objeto
{
   
public:
    Cilindro(Vec3f &b, float &r, float &h, Vec3f &d) : 
    radius(r), radius2(r *r ), base(b), height(h), dirCilindro(d) 
    {
       
    }
    virtual void move(float speed)
    {
        
       
    }

    
    bool intersect(const Vec3f &orig, const Vec3f &dir, float &t) const
    {
        float t0, t1; // solutions for t if the ray intersects
        Vec3f L = orig - base;
        Vec3f u = dirCilindro;
        Vec3f w = dir - (dir.dotProduct(u)) * u;
        Vec3f v = L - (u.dotProduct(L)) * u;

        float a = w.dotProduct(w);
        float b = 2 * v.dotProduct(w);
        float c = v.dotProduct(v) - radius2;
        bool resposta = Calculos().baskara(a, b, c, t0, t1);

        if (!resposta) return false;
        if (t0 > t1) std::swap(t0, t1);

        if (t0 < 0) {
            t0 = t1; 
            if (t0 < 0 || t0 > u.dotProduct(L)) return false; 
        }

        t = t0;
        return true;
    }
    virtual void move(vector<Objeto *> objects)
    {
        
    }
    void getSurfaceData(const Vec3f &Phit, Vec3f &Nhit, Vec2f &tex) const
    {
        Nhit = Phit - base;
        Nhit.normalize();
        tex.x = Nhit.x;
        tex.y = Nhit.y;
    }
    float radius, radius2, height;
    Vec3f base, dirCilindro;
};

#endif