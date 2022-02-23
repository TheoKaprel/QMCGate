//
// Created by tkaprelian on 1/25/22.
//

#include "GamSPSAngDistribution.h"



G4ParticleMomentum GamSPSAngDistribution::VGenerateOne() {
    return GenerateOne();
}


void GamSPSAngDistribution::SetPosDistributionGam(GamSPSPosDistribution * pg){
    fPositionGenerator = pg;
}

GamSPSPosDistribution * GamSPSAngDistribution::GetPosDistribution() {
    return fPositionGenerator;
}