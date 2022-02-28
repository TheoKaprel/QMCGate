/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#ifndef GamVoxelsSource_h
#define GamVoxelsSource_h

#include <pybind11/stl.h>
#include "GamGenericSource.h"
#include "GamSingleParticleSource.h"
#include "GamSPSVoxelsPosDistribution.h"
#include "GamSPSVoxelsAngDistribution.h"

#include <pointsets/Point.hpp>
#include <pointsets/Pointset.hpp>
#include <samplers/SamplerBase.hpp>
#include <samplers/SamplerWhitenoise.hpp>
#include <samplers/SamplerHalton.hpp>
#include <scrambling/ScramblingCranleyPatterson.hpp>
#include <io/fileIO.hpp>


namespace py = pybind11;

using namespace utk;

class GamVoxelsSource : public GamGenericSource {

public:
    GamVoxelsSource();

    virtual ~GamVoxelsSource();

    virtual void PrepareNextRun();

    std::string sampler_type;

    void GenerateSamplesPointset(unsigned long long int nb_initial_pts);

    GamSPSVoxelsPosDistribution *GetSPSVoxelPosDistribution() { return fVoxelPositionGenerator; }

protected:
    void InitializePosition(py::dict user_info);
    void InitializeDirection(py::dict user_info);

    GamSPSVoxelsPosDistribution * fVoxelPositionGenerator;
    GamSPSVoxelsAngDistribution * fVoxelDirectionGenerator;

    SamplerBase * sampler;

    Pointset generated_pts;

    ScramblingCranleyPatterson * scramblerCP;

    void SetSamplerType(std::string sampler_type);



};

#endif // GamVoxelsSource_h
