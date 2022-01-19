/*
 * Reference-matching code for LDBN in the paper:
 *      Ahmed, Perrier, Coeurjolly, Ostromoukhov, Guo, Yan, Huang, and Deussen
 *      Low-Discrepancy Blue Noise Sampling
 *      SIGGRAPH Asia 2016
 *
 * Coded by Abdalla G. M. Ahmed, 2016-09-19.
 * Copyright (c) 2016, Abdalla G. M. Ahmed
 * All rights reserved.
 *
 * Refactoring by David Coeurjolly 2018-11-22
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the LDBN project.
 */
#ifndef _UTK_SAMPLER_LDBN_
#define _UTK_SAMPLER_LDBN_

#include "../pointsets/Pointset.hpp"
#include <cstdlib>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "../utils.hpp"

namespace utk
{
	
/*static float radicalInverse_VdC(uint bits) {
	bits = (bits << 16u) | (bits >> 16u);
	bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
	bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
	bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
	bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
	return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}*/

void XY_from_i(uint i, uint& x, uint& y)
{
	x = i%128;
	y = i/128;
}

void i_from_XY(uint& i, uint x, uint y)
{
	i = y*128 + x;
}

class SamplerLDBN
{
protected:
public:

	SamplerLDBN() { 
		setTileSize(128);
		setChunkSize(16);
		srand(time(NULL));
	}

	void setTileSize(uint arg_tile)
	{
		tablesize = arg_tile;
		tablebit = log2(tablesize);
		maxval = 1u << (tablebit+10);
		one=tablesize*tablesize;
		scl = 1.0 / (double)maxval;
	}
	void setChunkSize(uint arg_chunk)
	{
		chunksize = arg_chunk;
	}
	void setPermutFile(std::string arg_filename)
	{
		permut_filename = arg_filename;
		
		std::ifstream permut_table(permut_filename);
		if(!permut_table.is_open() || !permut_table.good())
		{
			char msg[1000]; 
			sprintf(msg, "SamplerLDBN::generateSamples couldn't open permutation file %s", permut_filename.c_str());
			ERROR(msg);
		}
		O.resize(one);
		for (unsigned int i = 0; i < one; i++)
		{
			permut_table >> O[i].pos()[0] >> O[i].pos()[1];
		}
		
		tabulate();
		permut_table.close();
	}

	template<unsigned int D, typename T, typename P>
	bool generateSamples(Pointset<D, T, P>& arg_pts, unsigned long long int arg_points)
	{
		if(permut_filename.empty())
		{
			std::stringstream ss_tilesize;
			ss_tilesize << std::setfill('0') << std::setw(3) << tablesize;
			
			std::stringstream ss_chunksize;
			ss_chunksize << std::setfill('0') << std::setw(3) << chunksize;

			std::string permut_file=std::string(UTK_DATA_PATH)+"/LDBN/tables_BlueNoise/tilesize_" + ss_tilesize.str() + "/chunksize_m" + ss_chunksize.str() + ".dat";
			setPermutFile(permut_file);
		}
			
		
		if (!arg_pts.empty())
		{
			WARNING("SamplerLDBN::generateSamples the pointset to fill is not empty, clearing it ...");
			arg_pts.clear();
		}
		if(D != 2)
		{
			ERROR("SamplerLDBN::generateSamples is only defined in 2D");
			return false;
		}
		
		unsigned int n = sqrt(arg_points);
		if(arg_points != n*n)
		{
			char msg[1000]; 
			sprintf(msg, "SamplerLDBN::generateSamples Number of points is not a perfect square. Rounded up to %d", n*n);
			WARNING(msg);
		}
		
		arg_points = n*n;
		s.resize(n*n);
		generate(n);
		
		
		arg_pts.toricity = 0;
		arg_pts.resize(arg_points);
		
		int pmax = ceil((double)(log(arg_points)/log(2)));
		int smax = pow(2, pmax);
			
		if(isIntegerType<T>())
		{	
			//load domain
			for(uint d=0; d<D; d++)
			{
				arg_pts.domain.pMin.pos()[d] = 0;
				arg_pts.domain.pMax.pos()[d] = smax;
			}
			for(uint i=0; i<arg_points; i++)
			{
				for(uint d=0; d<D; d++)
					arg_pts[i].pos()[d] = s[i].pos()[d]*smax;
			}
		}
		else if (isFloatingType<T>())
		{
			//load domain
			for(uint d=0; d<D; d++)
			{
				arg_pts.domain.pMin.pos()[d] = 0;
				arg_pts.domain.pMax.pos()[d] = 1;
			}
			for(uint i=0; i<arg_points; i++)
			{
				for(uint d=0; d<D; d++)
					arg_pts[i].pos()[d] = s[i].pos()[d];
			}
		}
		else
		{
			ERROR("SamplerLDBN::generateSamples coordinates must be of numeric value");
			return false;
		}

		return true;
	};

protected:
	std::vector< Point<2, double> > O, s;
	
	uint chunksize;
	uint tablesize;
	uint tablebit;
	uint maxval;
	uint one;
	double scl;
	
	std::string permut_filename;

	unsigned mirror[1024];  // 10 bits
	
	void tabulate() 
	{
		for (unsigned i = 0; i < 512; i++) {
			mirror[i] = (i >> 9) + ((i >> 7) & 2) + ((i >> 5) & 4) + ((i >> 3) & 8)
			+ ((i >> 1) & 16) + ((i << 1) & 32) + ((i << 3) & 64)
			+ ((i << 5) & 128) + ((i << 7) & 256) + ((i << 9) & 512);
		}
		/*
		for (unsigned i = 0; i < 256; i++) {
			mirror[i] = (i >> 7) + ((i >> 5) & 2) + ((i >> 3) & 4) + ((i >> 1) & 8)
			+ ((i << 1) & 16) + ((i << 3) & 32) + ((i << 5) & 64) + ((i << 7) & 128);
		}
		*/
	}
	
	void generate(unsigned int n) 
	{
		double inv = 1.0 / n;
		int i = 0;
		/*for (unsigned Y = 0; Y < n; Y++) {
			double x = scl * mirror[Y >> 7];
			unsigned id0 = ((Y & 127) << 7);
			for (unsigned X = 0; X < n; X++) {
				double y = scl * mirror[X >> 7];
				unsigned id = id0 + (X & 127);
				s[i].x = inv * (X + O[id].x + x);
				s[i++].y = inv * (Y + O[id].y + y);
			}
		}*/
		for (unsigned int Y = 0; Y < n; Y++) {
			double x = scl * mirror[Y >> tablebit];
			unsigned id0 = ((Y & (tablesize-1)) << tablebit);
			//std::cout << "id0 " << id0 << std::endl;
			for (unsigned int X = 0; X < n; X++) {
				double y = scl * mirror[X >> tablebit];
				unsigned id = id0 + (X & (tablesize-1));
				//std::cout << "id " << id << std::endl;
				s[i].pos()[0] = inv * (X + O[id].pos()[0] + x);
				s[i++].pos()[1] = inv * (Y + O[id].pos()[1] + y);
			}
		}
	}
};

} //end namespace utk


#endif
