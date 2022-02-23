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

//    dir_mom_filename = "/export/home/tkaprelian/Desktop/Sampling/code/output/samples/samplesImage_dir_";
//    iter = 1;
}

GamSPSVoxelsAngDistribution::~GamSPSVoxelsAngDistribution() {
//    m_ostream_dir_mom.close();
}

void GamSPSVoxelsAngDistribution::SetPosDistributionGamVox(GamSPSVoxelsPosDistribution *pg) {
    fPositionGenerator = pg;
}

void GamSPSVoxelsAngDistribution::InitSamplingStuff(){
//    suffixe = fPositionGenerator->suffixe;
    generated_pts = fPositionGenerator->generated_pts;

//    dir_mom_filename = dir_mom_filename + suffixe + ".edat";

//    assert(!m_ostream_dir_mom.is_open());
//    m_ostream_dir_mom.open(dir_mom_filename);
}


G4ParticleMomentum GamSPSVoxelsAngDistribution::VGenerateOne() {
    // generates isotropic flux.
    G4double rndm, rndm2;
    G4double px, py, pz;


    int iterr = fPositionGenerator->iter;
//    iter = iter+1;

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

//    m_ostream_dir_mom << moment_direction[0] << '\t' <<  moment_direction[1] << '\t' <<   moment_direction[2] << std::endl;

    return(moment_direction);
}
