/// @brief 3D point or vector
#include <cfloat>
class cxyz
{
public:
    double x, y, z;

    cxyz()
        : x(-DBL_MAX),
          y(-DBL_MAX),
          z(-DBL_MAX)
    {
    }
    cxyz(double X, double Y, double Z)
        : x(X), y(Y), z(Z)
    {
    }

    /// @brief vector from this point to other
    /// @param other
    /// @return
    cxyz vect(const cxyz &other) const
    {
        return cxyz(
            other.x - x,
            other.y - y,
            other.z - z);
    }

    static cxyz plane(
        const cxyz &p0,
        const cxyz &p1,
        const cxyz &p2)
    {
        cxyz p01 = p0.vect(p1);
        cxyz p02 = p0.vect(p2);
        return cxyz(
            p0.x + p01.x + p02.x,
            p0.y + p01.y + p02.y,
            p0.z + p01.z + p02.z);
    }

    cxyz cross(const cxyz &other)
    {
        return cxyz(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.z);
    }

    double dot(const cxyz &other)
    {
        return x * other.x +
               y * other.y +
               z * other.z;
    }

    /// @brief intersection point between line and triangle
    /// @param la
    /// @param lb
    /// @param plane
    /// @return intersection point
    /// https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection#Parametric_form

    static cxyz intersectLineTriangle(
        const cxyz &la, const cxyz &lb,
        const cxyz &p0, const cxyz &p1, const cxyz &p2)
    {
        cxyz crossall = p0.vect(p1).cross(p0.vect(p2));
        cxyz crossu = p0.vect(p2).cross(lb.vect(la));
        cxyz crossv = lb.vect(la).cross(p0.vect(p1));
        cxyz lap0(la.x - p0.x, la.y - p0.y, la.z - p0.x);
        double divisor = lb.vect(la).dot(crossall);
        double t = crossall.dot(lap0) / divisor;
        double u = crossu.dot(lap0) / divisor;
        double v = crossv.dot(lap0) / divisor;

        std::cout 
            << "t " << t
            << " u " << u
            << " v " << v
            << "\n";

        // check that line intersects triangle
        if (t >= 0 && t <= 1)
            if (u >= 0 && u <= 1)
                if (v >= 0 && v <= 1)
                    if (u + v <= 1)

                        return cxyz(
                            la.x + t * (lb.x - la.x),
                            la.y + t * (lb.y - la.y),
                            la.z + t * (lb.z - la.z));

        std::cout << "NO intersection\n";
        return cxyz();
    }
};