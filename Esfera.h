#ifndef ESFERA_H
#define ESFERA_H    

#include <cstdlib>
#include <cmath>
#include "Calculos.h"

/*
    Esta classe irá servir para qualquer objeto esférico, 
    herda as características definidas na classe "Objeto"
    nesse trabalho usaremos pra representar planetas e 
    luas no sistema solar, bem como o próprio sol
*/
class Esfera : public Objeto
{
   
public:
    Esfera(Vec3f &c, float &r) : radius(r), radius2(r *r ){
       this->center = c;
    }
    virtual void move(vector<Objeto *> objects)
    {
        if(moving){ // inicialmente parado, só se move se for acionado esse gatilho
            Objeto *pivo; // definimos um obketo como sendo o pivo a qual este irá se mover em volta
            for (Objeto * ob: objects) {
                if (ob->nome == "sol") { // nesse trabalho, todos os objetos vão girar em torno do sol
                    pivo = ob;                        
                }
                
            }
            
            /*
            Aqui eu perdi quase metade do tempo do trabalho, infelizmente não consegui
            concluir, deixo comentado aqui pra tentar terminar nas férias 
            // tentativa fracassada de calcular a orbita da lua em relação ao sol
            
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
            float s = sin(angle); // guardando o seno aqui
            float c = cos(angle); // e o coseno aqui

            center.x -= pivo->center.x; // voltanso à posição anterior
            center.y -= pivo->center.y;
            
            // rotate point
            float xnew = center.x * c - center.y * s; // rotaciona 
            float ynew = center.x * s + center.y * c;
            

            // translate point back:
            center.x = xnew + pivo->center.x; //e finalmente move para a nova posição
            center.y = ynew + pivo->center.y;
                
           // }
          
        }
    }

    virtual void rotate(float angle)
    {  
        /*
            implementar futuramente a rotação em volta do proprio eixo
        */
    }

    // setters
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
        Vec3f L = orig - center; // distancia da camera
        float a = dir.dotProduct(dir); // a²
        float b = 2 * dir.dotProduct(L); // 2.b.t
        float c = L.dotProduct(L) - radius2; // c
        // devolve o resultado de baskara em t0 e t1 ou falso
        bool resposta = Calculos().baskara(a, b, c, t0, t1); 

        if (!resposta) return false;
        if (t0 > t1) std::swap(t0, t1);

        if (t0 < 0) {
            t0 = t1; // se t0 negativo, usamos t1
            if (t0 < 0) return false; // os dois são negativos, termina aqui
        }

        t = t0; // seta a distancia onde o raio acertou

        return true; // intersectou
    }
    
    /*
        função para calculo a posição dos pixels a serem pintados
    */
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
void Esfera::setNome(char * n){
    this->nome = n;
}
void Esfera::setColor(Vec3f c){
    this->color = c;
}
#endif