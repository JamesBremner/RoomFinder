

typedef std::vector<cxyz> triangle_t;

class cBuild
{
public:
    std::vector<triangle_t> myTriangles;       // all the triangles
    std::vector<triangle_t> mySelectTriangles; // triangles selected for hull

    void add(const triangle_t &t)
    {
        myTriangles.push_back(t);
    }

    void selectHull(cxyz ap)
    {
        // loop over triangles

        for (auto &t : myTriangles)
        {
            // Loop over rays from starting point in all directions

            for (cxyz r : destRays(ap))
            {
                // check for intersection
                if (cxyz::intersectLineTriangle(
                        ap, r,
                        t[0], t[1], t[2])
                        .isValid())
                {
                    mySelectTriangles.push_back(t);
                    break;
                }
            }
        }
    }

private:
    std::vector<cxyz> destRays(cxyz ap)
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
            std::cout << "\n";
        }

        return ret;
    }
};
