//
// Created by tkaprelian on 1/26/22.
//

#ifndef GamSPSVoxelsAngDistribution_h
#define GamSPSVoxelsAngDistribution_h

#include "GamSPSAngDistribution.h"
#include "G4ParticleMomentum.hh"
#include "G4SPSAngDistribution.hh"
#include "G4ThreeVector.hh"

#include <pointsets/Point.hpp>
#include <pointsets/Pointset.hpp>
#include <samplers/SamplerBase.hpp>
#include <samplers/SamplerWhitenoise.hpp>
#include <samplers/SamplerHalton.hpp>
#include <scrambling/ScramblingCranleyPatterson.hpp>
#include <io/fileIO.hpp>

#include "GamSPSVoxelsPosDistribution.h"

using namespace utk;

class GamSPSVoxelsAngDistribution : public GamSPSAngDistribution {
public:
    GamSPSVoxelsAngDistribution();

    virtual ~GamSPSVoxelsAngDistribution();

    void SetPosDistributionGamVox(GamSPSVoxelsPosDistribution * pg);

    void SetPointSet(Pointset ptset);

    virtual G4ParticleMomentum VGenerateOne();


private:
    G4double MinTheta, MaxTheta, MinPhi, MaxPhi;


    GamSPSVoxelsPosDistribution * fPositionGenerator;

    Pointset generated_pts;

};



#endif //GamSPSVoxelsAngDistribution_h
