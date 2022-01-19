#ifndef _UTK_SAMPLER_FPO_
#define _UTK_SAMPLER_FPO_

#include "SamplerFPO/sampler-fpoT2.hpp"
#include "../pointsets/Pointset.hpp"
#include <cstdlib>
#include <random>
#include <chrono>

#include "../utils.hpp"

namespace utk
{

class SamplerFPO
{
protected:
public:

	SamplerFPO() { setRandomSeedTime(); }

	void setRandomSeed( long unsigned int arg_seed ) { m_mersenneTwister.seed(arg_seed); }
	void setRandomSeedTime() { m_mersenneTwister.seed(std::chrono::system_clock::now().time_since_epoch().count()); }

	template<unsigned int D, typename T, typename P>
	bool generateSamples(Pointset<D, T, P>& arg_pts, unsigned int arg_points)
	{
		if (!arg_pts.empty())
		{
			WARNING("SamplerFPO::generateSamples the pointset to fill is not empty, clearing it ...");
			arg_pts.clear();
		}

		if (!isFloatingType<T>())
		{
			ERROR("SamplerFPO::generateSamples generates samples in [0, 1]^d, can only run with points of type float or double");
			return false;
		}

		//load domain & toricity
		for(uint d=0; d<D; d++)
		{
			arg_pts.domain.pMin.pos()[d] = 0;
			arg_pts.domain.pMax.pos()[d] = 1;
		}
		arg_pts.toricity = 1;
		//arg_pts.resize(arg_points);
		
		fpoSampler(arg_pts, arg_points);
		
		return true;
	};

protected:
    std::mt19937 m_mersenneTwister;
    double getRandom01()
    {
        return (double)m_mersenneTwister()/(double)m_mersenneTwister.max();
    }
};

} //end namespace utk


#endif
