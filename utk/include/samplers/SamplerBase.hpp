
#ifndef _UTK_SAMPLER_BASE
#define _UTK_SAMPLER_BASE

#include "../pointsets/Pointset.hpp"

namespace utk
{

    class SamplerBase {
    protected:
    public:

//        uint D = Point::D;

        SamplerBase() {};

        virtual bool generateSamples(Pointset& arg_pts, unsigned long long int arg_points)
        {
            std::cout << "WRONG PLACE TO GENERATE SAMPLES " << std::endl;
            return true;
        };

    protected:
    };

} //end namespace utk


#endif
