
#include <cfloat>
#include <set>

/// @brief 3D point or vector
class cxyz
{
public:
    double x, y, z;

    // default constructor creates invalid point
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
            x * other.y - y * other.x);
    }

    double dot(const cxyz &other)
    {
        return x * other.x +
               y * other.y +
               z * other.z;
    }
    double dist2(const cxyz &other) const
    {
        double dx = x - other.x;
        double dy = y - other.y;
        double dz = z - other.z;
        return dx * dx + dy * dy + dz * dz;
    }

    /// @brief intersection point between line segment and triangle
    /// @param la line point
    /// @param lb line point
    /// @param p0 triangle point
    /// @param p1 traingle point
    /// @param p2 trianglr point
    /// @return intersection point, invalid if no intersection
    /// https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection#Parametric_form
    static cxyz intersectLineTriangle(
        const cxyz &la, const cxyz &lb,
        const cxyz &p0, const cxyz &p1, const cxyz &p2)
    {
        cxyz crossall = p0.vect(p1).cross(p0.vect(p2));
        cxyz crossu = p0.vect(p2).cross(lb.vect(la));
        cxyz crossv = lb.vect(la).cross(p0.vect(p1));
        cxyz lap0(la.x - p0.x, la.y - p0.y, la.z - p0.z);
        double divisor = lb.vect(la).dot(crossall);
        double t = crossall.dot(lap0) / divisor;
        double u = crossu.dot(lap0) / divisor;
        double v = crossv.dot(lap0) / divisor;

        // check that line intersects triangle
        if (t >= 0 && t <= 1)
            if (u >= 0 && u <= 1)
                if (v >= 0 && v <= 1)
                    if (u + v <= 1)

                        return cxyz(
                            la.x + t * (lb.x - la.x),
                            la.y + t * (lb.y - la.y),
                            la.z + t * (lb.z - la.z));

        // no intersection, return default, invalid point
        return cxyz();
    }

    bool operator==(const cxyz &other) const
    {
        const double delta = 1;
        return (
            fabs(x - other.x) < delta &&
            fabs(y - other.y) < delta &&
            fabs(z - other.z) < delta);
    }
    bool operator<(const cxyz &other) const
    {
        if (*this == other)
            return false;
        const double delta = 0.1;
        if (
            other.x - x > delta &&
            other.y - y > delta &&
            other.z - z > delta)
            return true;
        return false;
    }

    std::string text() const
    {
        std::stringstream ss;
        ss << x << " " << y << " " << z;
        return ss.str();
    }

    /// @brief convert polar to cartesian coords
    /// @param r distance from origin
    /// @param alpha angle from X in XY plane
    /// @param polar angle from XY plane
    /// @return cartesian
    ///
    /// X-axis points to left
    /// Y-axis points to top
    /// Z-axis points to distance behind XY plane
    ///
    /// start with V0 ,vector on X-axis
    /// rotate V0 clockwise for alpha radians, viewed from Y, towards Z staying in XZ plane to get V1 vector
    /// rotate V1 towards Y, away from XZ plane to get VP vector
    /// point is r distance along VP from origin

    static cxyz polar2cart(double r, double alpha, double polar)
    {
        return cxyz(
            r * cos(polar) * cos(alpha),
            r * cos(polar) * sin(alpha),
            r * sin(polar));
    }

    static bool unitTest();
    
};