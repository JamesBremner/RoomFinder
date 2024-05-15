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
        // Construct rays from starting point in all directions

        for( cxyz r : destRays() )
        {
            std::cout << r.x <<" "<< r.y <<" "<< r.z << "\n";
        }
    }

private:

    std::vector<cxyz> destRays()
    {
        const double dist = 1;
        std::vector<cxyz> ret;

        double inc = M_PI / 4;

        for (double alpha = 0; alpha < 2 * M_PI; alpha += inc)
        {
            for ( double polar = 0; polar < 2 * M_PI; polar += inc)
            {
                cxyz p = cxyz::polar2cart(dist,alpha,polar);
                std::cout << alpha <<" "<< polar 
                    <<" => "<<  p.x <<" "<< p.y <<" "<<p.z << "\n";

                ret.push_back( cxyz::polar2cart(dist,alpha,polar));
            }
            std::cout << "\n";
        }

        return ret;
    }

};
