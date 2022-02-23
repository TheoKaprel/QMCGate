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
    fVoxelDirectionGenerator = new GamSPSVoxelsAngDistribution;
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

    // get and set the sampler type defined by the user
    std::string sampler_type = DictStr(user_info, "sampler");
    std::vector<std::string> lsamplers = {"WhiteNoise", "Halton"};
    CheckIsIn(sampler_type, lsamplers);
    fVoxelPositionGenerator->SetSamplerType(sampler_type);

    // set the filename "base"
    std::string filename_base = DictStr(user_info, "filename_base");
    fVoxelPositionGenerator->SetFileName(filename_base);


    // generate the initial number of points = Total activity set + 20 %
    // if the number of samples originally generated is not enough, it will be increased whenever necessary
    unsigned long long int nb_initial_pts = (unsigned long long int) ((DictFloat(user_info, "activity") * 1.e9));
    fVoxelPositionGenerator->AddPointsToSamplerSequence(nb_initial_pts);
}


void GamVoxelsSource::InitializeDirection(py::dict user_info) {
    fSPS->SetAngGenerator(fVoxelDirectionGenerator);

    // Only the isotropic direction in considered in the voxelized case for now
    auto duser_info = py::dict(user_info["direction"]);
    auto ang_type = DictStr(duser_info, "type");
    std::vector<std::string> l = {"iso"};
    CheckIsIn(ang_type, l);


    fVoxelDirectionGenerator->SetPosDistributionGamVox(fVoxelPositionGenerator);
    fVoxelDirectionGenerator->InitSamplingStuff();

//    // get and set the sampler type defined by the user
//    std::string sampler_type = DictStr(user_info, "sampler");
//    std::vector<std::string> lsamplers = {"WhiteNoise", "Halton"};
//    CheckIsIn(sampler_type, lsamplers);
//    fVoxelDirectionGenerator->SetSamplerType(sampler_type);
//
//    // generate the initial number of points = Total activity set
//    unsigned long long int nb_initial_pts = (unsigned long long int) (DictFloat(user_info, "activity") * 1.e9);
//    fVoxelDirectionGenerator->AddPointsToSamplerSequence(nb_initial_pts);
}

