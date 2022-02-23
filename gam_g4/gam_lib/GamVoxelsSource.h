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

namespace py = pybind11;

class GamVoxelsSource : public GamGenericSource {

public:
    GamVoxelsSource();

    virtual ~GamVoxelsSource();

    virtual void PrepareNextRun();

    std::string sampler_type;

    GamSPSVoxelsPosDistribution *GetSPSVoxelPosDistribution() { return fVoxelPositionGenerator; }

protected:
    void InitializePosition(py::dict user_info);
    void InitializeDirection(py::dict user_info);

    GamSPSVoxelsPosDistribution * fVoxelPositionGenerator;
    GamSPSVoxelsAngDistribution * fVoxelDirectionGenerator;


};

#endif // GamVoxelsSource_h
