#include <string>
#include <iostream>
#include <sstream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "cxyz.h"

bool cxyz::unitTest()
    {
        cxyz t1(0, 0, 0), t2(1, 0, 0), t3(1, 1, 0);
        cxyz ap(0.7, 0.7, 0.5), outer(0.7, 0.7, -10);
        cxyz intersect = cxyz::intersectLineTriangle(
            ap, outer,
            t1, t2, t3);
        if (fabs(0.7 - intersect.x) > 0.01)
            return false;
        if (fabs(0.7 - intersect.y) > 0.01)
            return false;
        if (fabs(0 - intersect.z) > 0.01)
            return false;

        cxyz p = polar2cart(1, 0, 0);
        if (!(cxyz(1, 0, 0) == p))
            return false;
        p = polar2cart(1, 0, M_PI / 4);
        if (!(cxyz(0.707107, 0, 0.707107) == p))
            return false;
        p = polar2cart(1, 0, M_PI / 2);
        if (!(cxyz(0, 0, 1) == p))
            return false;

        return true;
    }