#ifndef CONE_H
#define CONE_H    

#include <cstdlib>
#include "Calculos.h"
#include "Objeto.h"

class Cone : public Objeto
{
   
public:
    Cone(Vec3f &b, float &r, float &h, Vec3f &d) : 
    radius(r), base(b), height(h), dirCone(d) 
    {
        float tm = 1;
        phiMax = Calculos().deg2rad( Calculos().clamp( tm, 0.0f, 360.0f ) );
    }
    virtual void move(float speed)
    {
        
       
    }

    
    bool intersect(const Vec3f &orig, const Vec3f &dir, float &t) const
    {
        // Compute quadratic cone coefficients
        float k = radius / height;
        k = k*k;
        float A = dir.x * dir.x + dir.y * dir.y -
        k * dir.z * dir.z;
        float B = 2 * (dir.x * orig.x + dir.y * orig.y -
        k * dir.z * (orig.z-height) );
        float C = orig.x * orig.x + orig.y * orig.y -
        k * (orig.z -height) * (orig.z-height);
        
        float t0, t1;
        if (!Calculos().baskara(A, B, C, t0, t1))
            return false;
        
        // Compute intersection distance along ray
        if (t0 > t1) std::swap(t0, t1);

        if (t0 < 0) {
            t0 = t1; // if t0 is negative, let's use t1 instead
            if (t0 < 0) return false; // both t0 and t1 are negative
        }

        t = t0;
 
     
     return true;
        
    }
    virtual void move(vector<Objeto *> objects)
    {
        
    }
    void getSurfaceData(const Vec3f &Phit, Vec3f &Nhit, Vec2f &tex) const
    {
        float phi;
        phi = atan2f(Phit.y, Phit.x);
        if (phi < 0.) phi += 2.f*M_PI;
        Nhit = Phit - base;
        Nhit.normalize();
        tex.x = Nhit.x;
        tex.y = Nhit.y;
        
    }
    float radius, height, phiMax;
    Vec3f base, dirCone;
    
};

#endif