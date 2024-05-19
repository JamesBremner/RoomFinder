#include <fstream>
#include "cBuilding.h"

    bool cTriangle::operator==(const cTriangle &other) const
    {
        return (
            myP[0] == other.myP[0] &&
            myP[1] == other.myP[1] &&
            myP[2] == other.myP[2]);
    }
    std::string cTriangle::text() const
    {
        if (myP.size() < 3)
            return "";
        std::stringstream ss;
        ss << myP[0].text() << ", "
           << myP[1].text() << ", "
           << myP[2].text();
        return ss.str();
    }
    std::string cTriangle::dxf() const
    {
        const std::string LWPOLYLINE =
            "0\n"
            "LWPOLYLINE\n"
            "5\n"
            "7C\n"
            "330\n"
            "1F\n"
            "100\n"
            "AcDbEntity\n"
            "8\n"
            "freze1\n"
            "100\n"
            "AcDbPolyline\n"
            " 90\n"
            "4\n" // vertex count
            " 70\n"
            "1\n" // closed
            " 43\n"
            "0.0\n";

        if (myP.size() < 3)
            return "";
        std::stringstream ss;
        ss
            << LWPOLYLINE
            << " 10\n"
            << myP[0].x << "\n"
            << " 20\n"
            << myP[0].y << "\n"
            << " 10\n"
            << myP[1].x << "\n"
            << " 20\n"
            << myP[1].y << "\n"
            << " 10\n"
            << myP[2].x << "\n"
            << " 20\n"
            << myP[2].y << "\n";
        return ss.str();
    }

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

    double inc = M_PI / 8;

    for (double alpha = 0; alpha < 2 * M_PI; alpha += inc)
    {
        for (double polar = 0; polar < 2 * M_PI; polar += inc)
        {
            // cxyz p = cxyz::polar2cart(dist, alpha, polar) + ap;
            // std::cout << alpha << " " << polar
            //           << " => " << p.x << " " << p.y << " " << p.z << "\n";

            ret.push_back(cxyz::polar2cart(dist, alpha, polar));
        }
        // std::cout << "\n";
    }

    return ret;
}
std::string cBuild::textRoom() const
{
    std::stringstream ss;
    for (auto &t : mySelectTriangles)
        ss << t.text() << "\n";
    return ss.str();
}
std::string cBuild::dxfRoom() const
{
    std::stringstream ss;
    ss << "2\n"
          "ENTITIES\n";

    for (auto &t : mySelectTriangles)
    {
        ss << t.dxf();
    }

    ss << "ENDSEC\n"
          "0\n"
          "EOF\n";

    return ss.str();
}

void cBuild::genOrthoPanel(const cxyz &p1, const cxyz &p2)
{
    const double delta = 0.01;
    if (fabs(p1.x - p2.x) < delta)
    {
        add({cxyz(p1.x, p1.y, p1.z), cxyz(p1.x, p1.y, p2.z), cxyz(p1.x, p2.y, p2.z)});
        add({cxyz(p1.x, p1.y, p1.z), cxyz(p1.x, p2.y, p1.z), cxyz(p1.x, p2.y, p2.z)});
    }
    else if (fabs(p1.y - p2.y) < delta)
    {
        add({cxyz(p1.x, p1.y, p1.z), cxyz(p1.x, p1.y, p2.z), cxyz(p2.x, p1.y, p2.z)});
        add({cxyz(p1.x, p1.y, p1.z), cxyz(p2.x, p1.y, p1.z), cxyz(p2.x, p1.y, p2.z)});
    }
    else if (fabs(p1.z - p2.z) < delta)
    {
        add({cxyz(p1.x, p1.y, p1.z), cxyz(p1.x, p2.y, p1.z), cxyz(p2.x, p2.y, p1.z)});
        add({cxyz(p1.x, p1.y, p1.z), cxyz(p2.x, p1.y, p1.z), cxyz(p2.x, p2.y, p1.z)});
    }
    else
    {
        throw std::runtime_error(
            "cBuild::genOrthoPanel bad parameter");
    }
}

void cBuild::genDoubleWalledUnitCube()
{
    myTriangles.clear();

    // front wall
    genOrthoPanel(cxyz(0, 0, 0), cxyz(1, 1, 0));
    genOrthoPanel(cxyz(0, 0, -0.1), cxyz(1, 1, -0.1));

    // back wall
    genOrthoPanel(cxyz(0, 0, 1), cxyz(1, 1, 1));
    genOrthoPanel(cxyz(0, 0, 1.1), cxyz(1, 1, 1.1));

    // side walls
    genOrthoPanel(cxyz(0, 0, 0), cxyz(0, 1, 1));
    genOrthoPanel(cxyz(-0.1, 0, 0), cxyz(-0.1, 1, 1));
    genOrthoPanel(cxyz(1, 0, 0), cxyz(1, 1, 1));
    genOrthoPanel(cxyz(1.1, 0, 0), cxyz(1.1, 1, 1));

    // floor
    genOrthoPanel(cxyz(0, 0, 0), cxyz(1, 0, 1));

    // ceiling
    genOrthoPanel(cxyz(0, 1, 0), cxyz(1, 1, 1));
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

    B.genDoubleWalledUnitCube();
    B.selectHull(cxyz(.5, .5, .5));
    // B.textRoom();

    // check that every cube face selected exactly once
    // cube has 6 faces, each face has 2 triangles
    if (B.mySelectTriangles.size() != 12)
        return false;

    // check that nearest wall surface always selected
    for (auto &t : B.mySelectTriangles)
    {
        for (int it = 0; it < 3; it++)
        {
            if ((int)(t.myP[it].x * 100) % 100)
                return false;
            if ((int)(t.myP[it].y * 100) % 100)
                return false;
            if ((int)(t.myP[it].y * 100) % 100)
                return false;
        }
    }

    std::ofstream ofs("room.dxf");
    ofs << B.dxfRoom();

    return true;
}