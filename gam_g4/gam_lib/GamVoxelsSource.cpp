/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#include "G4ParticleTable.hh"
#include "G4RandomTools.hh"
#include "GamVoxelsSource.h"
#include "GamDictHelpers.h"


GamVoxelsSource::GamVoxelsSource() : GamGenericSource() {
    fVoxelPositionGenerator = new GamSPSVoxelsPosDistribution;
}

GamVoxelsSource::~GamVoxelsSource() {
}

void GamVoxelsSource::PrepareNextRun() {
    GamGenericSource::PrepareNextRun();
    // rotation and translation to apply, according to mother volume
    fVoxelPositionGenerator->fGlobalRotation = fGlobalRotation;
    fVoxelPositionGenerator->fGlobalTranslation = fGlobalTranslation;
}

void GamVoxelsSource::InitializePosition(py::dict user_info) {
    fSPS->SetPosGenerator(fVoxelPositionGenerator);

    fVoxelPositionGenerator->SetPosDisType("Point");

    std::string sampler_type = DictStr(user_info, "sampler");
    std::vector<std::string> lsamplers = {"WhiteNoise", "Halton"};
    CheckIsIn(sampler_type, lsamplers);


    fVoxelPositionGenerator->SetSamplerType(sampler_type);

    unsigned long long int nb_initial_pts = (unsigned long long int) (DictFloat(user_info, "activity") * 1.e9);

    fVoxelPositionGenerator->AddPointsToSamplerSequence(nb_initial_pts);

}

