#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H    

#include <vector>
#include "Objeto.h"
#include "Esfera.h"

/*
    Classe para criar os objetos necessários para formação
    do "sistema solar", neste momento, estamos considerando todos 
    os corpos celestes como planetas (classe Esfera)
    posteriormente pensar em desmebrar tais corpos:
    por exemplo, satélites naturais, cometas, satélites comuns etc
*/
class SolarSystem
{
   
public:
    vector<Objeto *> planets;
    SolarSystem(){
       build();
    }
    
    vector<Objeto *>  getPlanets(){
        return this->planets;
    }
    void build(){
    Vec3f pos = {0,0,0}; // sol inicia na origem do nosso sistema de coordenadas
    float radius = 0.9; 
    
    
    Esfera *sun = new Esfera(pos, radius);
    (*sun).setNome("sol"); 
    (*sun).setColor(Vec3f(1,0.5,0));
    planets.push_back(sun); // sun

    // abaixo definimos vários planetas cada um com sua característica
    pos = {pos.x + 1.7f, pos.y,pos.z};
    radius = 0.3;
    Esfera *mercury = new Esfera(pos, radius);
    (*mercury).setSpeed(16);
    (*mercury).setMoving(true); // gatilho pra movimento
    (*mercury).setColor(Vec3f(0.7,0.5,0));
    (*mercury).setNome("mercury"); 

    planets.push_back(mercury); // Mercury


    pos = {pos.x + 1.4f, pos.y,pos.z};
    radius = 0.25;
    Esfera *venus = new Esfera(pos, radius);
    (*venus).setColor(Vec3f(1,0.9,1));
    (*venus).setSpeed(24);
    (*venus).setMoving(true); // gatilho pra movimento
    (*venus).setNome("venus"); 

    planets.push_back(venus); // Venus

    pos = {pos.x + 1.5f, pos.y,pos.z};
    radius = 0.2;
    Esfera *earth = new Esfera(pos, radius);
    (*earth).setColor(Vec3f(0.1,0.5,0.8));
    (*earth).setSpeed(32);
    (*earth).setMoving(true); // gatilho pra movimento
    (*earth).setNome("terra"); 
    planets.push_back(earth); // earth

    pos = {pos.x + 0.3f, pos.y + 0.2f, pos.z};
    radius = 0.08;
    Esfera *moon = new Esfera(pos, radius);
    (*moon).setSpeed(32);
    (*moon).setMoving(true); // gatilho pra movimento
    (*moon).setColor(Vec3f(1,0.9,0.7));
    (*moon).setNome("lua"); 
    
    planets.push_back(moon); // moon

    pos = {pos.x + 1.9f, pos.y,pos.z};
    radius = 0.35;
    Esfera *mars = new Esfera(pos, radius);
    (*mars).setColor(Vec3f(1,0.3,0));
    (*mars).setSpeed(30);
    (*mars).setMoving(true); // gatilho pra movimento
    (*mars).setNome("marte"); 
    planets.push_back(mars); // mars

    pos = {pos.x + 2.7f, pos.y,pos.z};
    radius = 0.60;
    Esfera *jupiter = new Esfera(pos, radius);
    (*jupiter).setColor(Vec3f(0.7,0.8,0.5));
    (*jupiter).setSpeed(18);
    (*jupiter).setMoving(true); // gatilho pra movimento
    (*jupiter).setNome("jupiter");
    planets.push_back(jupiter); // Jupiter

    // luas de jupiter
    pos = {pos.x + 0.6f, pos.y + 0.4f, pos.z};
    radius = 0.07;
    Esfera *lua1 = new Esfera(pos, radius);
    (*lua1).setSpeed(18);
    (*lua1).setMoving(true); // gatilho pra movimento
    (*lua1).setColor(Vec3f(1,0.9,0.7));
    (*lua1).setNome("lua1"); 
    planets.push_back(lua1);

    pos = {pos.x, pos.y - 0.7f, pos.z};
    radius = 0.08;
    Esfera *lua2 = new Esfera(pos, radius);
    (*lua2).setSpeed(18);
    (*lua2).setMoving(true); // gatilho pra movimento
    (*lua2).setColor(Vec3f(1,0.9,0.7));
    (*lua2).setNome("lua2"); 
    planets.push_back(lua2);

    pos = {pos.x -1.3f, pos.y, pos.z-0.3f};
    radius = 0.06;
    Esfera *lua3 = new Esfera(pos, radius);
    (*lua3).setSpeed(18);
    (*lua3).setMoving(true); // gatilho pra movimento
    (*lua3).setColor(Vec3f(1,0.9,0.7));
    (*lua3).setNome("lua3"); 
    planets.push_back(lua3);

    pos = {pos.x + 3.1f, pos.y,pos.z};
    radius = 0.45;
    Esfera *saturn = new Esfera(pos, radius);
    (*saturn).setColor(Vec3f(0.7,0.8,0.7));
    (*saturn).setSpeed(36);
    (*saturn).setMoving(true); // gatilho pra movimento
    (*saturn).setNome("saturno");
    planets.push_back(saturn); // Saturn

    pos = {pos.x + 3.38f, pos.y,pos.z};
    radius = 0.25;
    Esfera *uranus = new Esfera(pos, radius);
    (*uranus).setColor(Vec3f(0.1,0.5,1));
    (*uranus).setSpeed(18);
    (*uranus).setMoving(true); // gatilho pra movimento
    (*uranus).setNome("uranus");
    planets.push_back(uranus); // Uranus

    }

};
#endif