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
/*
    Funcao principal, aqui chamamos os objetos e detnro de cada objeto tem sua
    função específica de cálculo de cor, checagem de interseção e também
    cálculo da distancia entre a origem e o ponto de interseção
*/
Vec3f Ray::castRay(
    const Vec3f &orig, const Vec3f &dir,
    const std::vector<Objeto *> &objetos)
{
    
    Vec3f hitColor = 0; // inicia um vetor de cores zerado (preto)
    const Objeto *hitObject = nullptr; // ponteiro para o objeto "acertado"
    float t; // Distancia da origem para a interseção
    
    /*
        Aqui chamamos a função principal que faz uma varredura na
        lista de objetos até acertar em algum, setando-o como hitObject
        e a distancia do ponto acertado
    */
    if (trace(orig, dir, objetos, t, hitObject)) { 
        Vec3f Phit = orig + dir * t; // setando as coordenadas do ponto acertado
        Vec3f Nhit; // para ser usada na coloração
        Vec2f tex;
        
        hitObject->getSurfaceData(Phit, Nhit, tex); // grava a coordenada do pixel em tex
        
        float scale = 0.5; // para dar um efeito quadriculado
        float pattern = (fmodf(tex.x * scale, 1) > 0.5) ^ (fmodf(tex.y * scale, 1) > 0.5); // mistura as cores
        hitColor = 
            std::max(0.f, 
            Nhit.dotProduct(-dir)) * Calculos().mix(hitObject->color, 
            hitObject->color * 0.8, 
            pattern); // calculo final da cor
        
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
    
    tNear = kInfinity; // assume que não acertou nenhum objeto ainda
    
    for (Objeto * ob: objects) { // loop nos objetos
        float t = kInfinity; // distancia começa no infinito
        if (ob->intersect(orig, dir, t) && t < tNear) { // se intersecta, "t" assume a distancia
            hitObject = ob; // grava o objeto intersectado
            tNear = t; //mais proximo
            return true; // sai do loop quando intersecta
        }
        
    }
    return (hitObject != nullptr); // retorna o objeto se intersectado
}


#endif