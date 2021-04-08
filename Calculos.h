#ifndef CALCULOS_H
#define CALCULOS_H

#include <math.h>

class Calculos
{
private:
    /* data */
public:
    Calculos(/* args */);
    ~Calculos();
    bool baskara(const float &a, const float &b, const float &c, float &x0, float &x1);
    Vec3f mix(const Vec3f &a, const Vec3f& b, const float &mixValue);
    float clamp(const float &lo, const float &hi, const float &v);
    float deg2rad(const float &deg);


};

Calculos::Calculos(/* args */)
{
}

Calculos::~Calculos()
{
}
 bool Calculos::baskara(const float &a, const float &b, const float &c, float &x0, float &x1){
     float discr = b * b - 4 * a * c;
        if (discr < 0) return false;
        else if (discr == 0) {
            x0 = x1 = - 0.5 * b / a;
        }
        else {
            float q = (b > 0) ?
                -0.5 * (b + sqrt(discr)) :
                -0.5 * (b - sqrt(discr));
            x0 = q / a;
            x1 = c / q;
        }

        return true;
 }

inline
Vec3f Calculos::mix(const Vec3f &a, const Vec3f& b, const float &mixValue)
{ return a * (1 - mixValue) + b * mixValue; }

inline
float Calculos::clamp(const float &lo, const float &hi, const float &v)
{ return std::max(lo, std::min(hi, v)); }

inline
float Calculos::deg2rad(const float &deg)
{ return deg * M_PI / 180; }

#endif