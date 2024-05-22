#define _USE_MATH_DEFINES
#include <cmath>
#include "cxyz.h"

double cxyz::length()
{
    return sqrt(x * x + y * y + z * z);
}
void cxyz::normal()
{
    double l = length();
    x /= l;
    y /= l;
    z /= l;
}

void cCamera::set(
    const cxyz &position,
    const cxyz &target,
    const cxyz &up)
{
https: // en.wikipedia.org/wiki/Graphics_pipeline#Camera_Transformation

    myPosition = position;

    // Z-axis
    Matrix[2] = (target - position);
    Matrix[2].normal();

    // X-axis
    Matrix[0] = up;
    Matrix[0] = Matrix[0].cross(Matrix[2]);
    Matrix[0].normal();

    // Y-axis
    Matrix[1] = Matrix[2].cross(Matrix[0]);

}

cxyz cCamera::view(const cxyz &p)
{
    cxyz ret;

    ret.x = Matrix[0].x * p.x + Matrix[1].x * p.y + Matrix[2].x * p.z - myPosition.x;
    ret.y = Matrix[0].y * p.x + Matrix[1].y * p.y + Matrix[2].y * p.z - myPosition.y;
    ret.z = Matrix[0].z * p.x + Matrix[1].z * p.y + Matrix[2].z * p.z - myPosition.z;

    return ret;
}
bool cCamera::unitTest()
{
    cCamera C;
    C.set(
        cxyz(0, 0, 0), cxyz(0, 0, 10), cxyz(0, 10, 0));
    cxyz ret = C.view(cxyz(0.5, 0.5, 0.5));

    C.set(
        cxyz(10, 0, 0), cxyz(10, 0, 10), cxyz(0, 10, 0));
    ret = C.view(cxyz(0.5, 0.5, 0.5));

    C.set(
        cxyz(0, 0, 0), cxyz(-10, 0, 10), cxyz(0, 10, 0));
    ret = C.view(cxyz(0.5, 0.5, 0.5));

    return false;
}