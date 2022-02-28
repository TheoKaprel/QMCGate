/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#ifndef GamSPSVoxelsPosDistribution_h
#define GamSPSVoxelsPosDistribution_h

#include <utility>

#include "G4ParticleDefinition.hh"
#include "GamSPSPosDistribution.h"
#include "itkImage.h"
#include <fstream>

#include <pointsets/Point.hpp>
#include <pointsets/Pointset.hpp>
#include <samplers/SamplerBase.hpp>
#include <samplers/SamplerWhitenoise.hpp>
#include <samplers/SamplerHalton.hpp>
#include <scrambling/ScramblingCranleyPatterson.hpp>
#include <io/fileIO.hpp>

using namespace utk;

class GamSPSVoxelsPosDistribution : public GamSPSPosDistribution {

public:

    GamSPSVoxelsPosDistribution();

    virtual ~GamSPSVoxelsPosDistribution();

    // Cannot inherit from GenerateOne
    virtual G4ThreeVector VGenerateOne();

    // typedef for vector of vector
    typedef std::vector<double> VD;
    typedef std::vector<VD> VD2;
    typedef std::vector<std::vector<VD>> VD3;

    void SetCumulativeDistributionFunction(VD vz, VD2 vy, VD3 vx);

    Pointset generated_pts;

    void SetPointSet(Pointset ptset);


    typedef itk::Image<float, 3> ImageType;

    // The image is accessible from py side
    ImageType::Pointer cpp_image;

    G4ThreeVector fGlobalTranslation;
    G4RotationMatrix fGlobalRotation;

    int iter;

protected:

    VD3 fCDFX;
    VD2 fCDFY;
    VD fCDFZ;


};

#endif // GamSPSVoxelsPosDistribution_h
