#ifndef RAY_H
#define RAY_H

#include <math.h>
#include <vector>
#include <memory>
#include "geometry.h"
#include "Objeto.h"
#include "Calculos.h"

class Ray
{
private:
    /* data */
public:
    Ray(/* args */);
    ~Ray();
    Vec3f castRay(
        const Vec3f &orig, const Vec3f &dir,
        const std::vector<Objeto *> &objetos);
    bool trace(
        const Vec3f &orig, 
        const Vec3f &dir, 
        const std::vector<Objeto *> &objects, 
        float &tNear, 
        const Objeto *&hitObject);
};

Ray::Ray(/* args */)
{
}

Ray::~Ray()
{
}
Vec3f Ray::castRay(
    const Vec3f &orig, const Vec3f &dir,
    const std::vector<Objeto *> &objetos)
{
    
    Vec3f hitColor = 0;
    const Objeto *hitObject = nullptr; // this is a pointer to the hit object
    float t; // this is the intersection distance from the ray origin to the hit point
    
    if (trace(orig, dir, objetos, t, hitObject)) {
        Vec3f Phit = orig + dir * t;
        Vec3f Nhit;
        Vec2f tex;
        
        hitObject->getSurfaceData(Phit, Nhit, tex);
        
        float scale = 0.5;
        float pattern = (fmodf(tex.x * scale, 1) > 0.5) ^ (fmodf(tex.y * scale, 1) > 0.5);
        hitColor = 
            std::max(0.f, 
            Nhit.dotProduct(-dir)) * Calculos().mix(hitObject->color, 
            hitObject->color * 0.8, 
            pattern);
        /*
        hitColor = 
            std::max(0.f, 
            Nhit.dotProduct(-dir)) * Calculos().mix(hitObject->color, 
            hitObject->color * 0.8, 
            pattern);
            */
    }
    
    return hitColor;

}

bool Ray::trace(
    const Vec3f &orig, 
    const Vec3f &dir, 
    const std::vector<Objeto *> &objects, 
    float &tNear, 
    const Objeto *&hitObject)
{
    
    tNear = kInfinity;
    
    for (Objeto * ob: objects) {
        float t = kInfinity;
        
        if (ob->intersect(orig, dir, t) && t < tNear) {
            hitObject = ob;
            tNear = t;
            return true;
        }
        
    }
    //for (; iter != objects.end(); ++iter) {
        //float t = kInfinity;
        /*
        if ((*iter)->intersect(orig, dir, t) && t < tNear) {
            hitObject = iter->get();
            tNear = t;
            return true;
        }
        */
       
    //}
    
    return (hitObject != nullptr);
}


#endif