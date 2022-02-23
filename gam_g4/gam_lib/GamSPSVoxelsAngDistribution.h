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


    void InitSamplingStuff();

//    void SetSamplerType(std::string sampler_type);
//
//    void AddPointsToSamplerSequence(unsigned long long int nb_pts);

    virtual G4ParticleMomentum VGenerateOne();


private:
    G4double MinTheta, MaxTheta, MinPhi, MaxPhi;


//    SamplerBase * sampler;

//    ScramblingCranleyPatterson * scramblerCP;


    GamSPSVoxelsPosDistribution * fPositionGenerator;


    Pointset generated_pts;

//    std::string points01_filename_;
//    std::string suffixe;
//    std::string dir_mom_filename;
//    std::ofstream m_ostream_dir_mom;

//    int iter;
//    int * getScientificNot(unsigned long long int N);
};



#endif //GamSPSVoxelsAngDistribution_h
