
#ifndef _UTK_SAMPLER_BASE
#define _UTK_SAMPLER_BASE

#include "../pointsets/Pointset.hpp"

namespace utk
{

    class SamplerBase {
    protected:
    public:
        uint D = 0;

        virtual bool generateSamples(Pointset& arg_pts, unsigned long long int arg_points) = 0;

    protected:
    };

} //end namespace utk


#endif
