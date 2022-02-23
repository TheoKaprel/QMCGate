//
// Created by tkaprelian on 1/25/22.
//

#ifndef GamSPSAngDistribution_h
#define GamSPSAngDistribution_h

#include "G4ParticleMomentum.hh"
#include "G4SPSAngDistribution.hh"
#include "G4ThreeVector.hh"
#include "GamSPSPosDistribution.h"

class GamSPSAngDistribution : public G4SPSAngDistribution {
public:

    virtual ~GamSPSAngDistribution() {}

    // cannot inherit from GenerateOne so we consider VGenerateOne instead
    virtual G4ParticleMomentum VGenerateOne();

    void SetPosDistributionGam(GamSPSPosDistribution * pg);

    GamSPSPosDistribution * GetPosDistribution();


protected:
    GamSPSPosDistribution *fPositionGenerator;

};


#endif //GamSPSAngDistribution_h
