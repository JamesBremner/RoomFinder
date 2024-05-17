#include "cBuilding.h"

void cBuild::selectHull(cxyz ap)
{
    mySelectTriangles.clear();

    // Loop over rays from starting point in all directions
    for (cxyz r : destRays(ap))
    {
        double mindist2 = DBL_MAX;
        cTriangle tmin;

        // loop over triangles
        for (auto &t : myTriangles)
        {

            // check for intersection
            cxyz ip = cxyz::intersectLineTriangle(ap, r, t.myP);
            if (!ip.isValid())
                continue;

            // check for closest intersection with this ray
            double dist2 = ap.dist2(ip);
            if (dist2 < mindist2)
            {
                tmin = t;
                mindist2 = dist2;
            }
        }

        if (mindist2 != DBL_MAX)
        {
            bool found = false;
            for (auto &t : mySelectTriangles)
            {
                if (tmin == t)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
                mySelectTriangles.push_back(tmin);
        }
        // if (std::find(
        //         mySelectTriangles.begin(), mySelectTriangles.end(), tmin) == mySelectTriangles.end())
        //     mySelectTriangles.push_back(tmin);
    }
}

std::vector<cxyz> cBuild::destRays(cxyz ap)
{
    const double dist = 1e6;
    std::vector<cxyz> ret;

    double inc = M_PI / 4;

    for (double alpha = 0; alpha < 2 * M_PI; alpha += inc)
    {
        for (double polar = 0; polar < 2 * M_PI; polar += inc)
        {
            // cxyz p = cxyz::polar2cart(dist, alpha, polar) + ap;
            // std::cout << alpha << " " << polar
            //           << " => " << p.x << " " << p.y << " " << p.z << "\n";

            ret.push_back(cxyz::polar2cart(dist, alpha, polar));
        }
        //std::cout << "\n";
    }

    return ret;
}
std::string cBuild::textRoom() const
{
    std::stringstream ss;
    for( auto& t : mySelectTriangles )
        ss << t.text() << "\n";
    return ss.str();
}
bool cBuild::unitTest()
{
    if (!cxyz::unitTest())
        return false;

    // construct double wall
    cBuild B;
    B.add({cxyz(0, 0, 1), cxyz(1, 0, 1), cxyz(1, 1, 1)});
    B.add({cxyz(0, 0, 10), cxyz(1, 0, 10), cxyz(1, 1, 10)});

    B.selectHull(cxyz(0, 0, 0));

    // check that nearest wall surface selected
    if (!B.mySelectTriangles.size())
        return false;
    if (B.mySelectTriangles[0].myP[0].z != 1)
        return false;

    B.selectHull(cxyz(0, 0, 100));

    // check that nearest wall surface selected
    if (!B.mySelectTriangles.size())
        return false;
    if (B.mySelectTriangles[0].myP[0].z != 10)
        return false;

    return true;
}