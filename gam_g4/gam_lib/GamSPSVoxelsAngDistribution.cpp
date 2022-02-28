//
// Created by tkaprelian on 1/26/22.
//

#include "GamSPSVoxelsAngDistribution.h"
#include "Randomize.hh"
#include <math.h>
#define _USE_MATH_DEFINES
#include <cmath>



GamSPSVoxelsAngDistribution::GamSPSVoxelsAngDistribution() {
    MinTheta = 0.;
    MaxTheta = M_PI;
    MinPhi = 0.;
    MaxPhi = 2*M_PI;

}

GamSPSVoxelsAngDistribution::~GamSPSVoxelsAngDistribution() {
}

void GamSPSVoxelsAngDistribution::SetPosDistributionGamVox(GamSPSVoxelsPosDistribution *pg) {
    fPositionGenerator = pg;
}

void GamSPSVoxelsAngDistribution::SetPointSet(Pointset ptset) {
    generated_pts = ptset;
}



G4ParticleMomentum GamSPSVoxelsAngDistribution::VGenerateOne() {
    // generates isotropic flux.
    G4double rndm, rndm2;
    G4double px, py, pz;

    int iterr = fPositionGenerator->iter;

    rndm = generated_pts[iterr].pos()[3];
    rndm2 = generated_pts[iterr].pos()[4];


    G4double sintheta, sinphi,costheta,cosphi;

    costheta = std::cos(MinTheta) - rndm * (std::cos(MinTheta)
                                            - std::cos(MaxTheta));
    sintheta = std::sqrt(1. - costheta*costheta);

    G4double Phi = MinPhi + (MaxPhi - MinPhi) * rndm2;
    sinphi = std::sin(Phi);
    cosphi = std::cos(Phi);

    px = -sintheta * cosphi;
    py = -sintheta * sinphi;
    pz = -costheta;

    G4double finx, finy, finz;
    finx = px;
    finy = py;
    finz = pz;

    G4double ResMag = std::sqrt((finx*finx) + (finy*finy) + (finz*finz));
    finx = finx/ResMag;
    finy = finy/ResMag;
    finz = finz/ResMag;

    G4ParticleMomentum moment_direction = G4ParticleMomentum(finx,finy,finz);

    return(moment_direction);
}
