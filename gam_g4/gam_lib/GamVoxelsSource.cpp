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
    std::vector <std::string> lsamplers = {"WN", "LD"};
    CheckIsIn(sampler_type, lsamplers);
    SetSamplerType(sampler_type);


    // generate the initial number of points = Total activity set + 20 %
    // if the number of samples originally generated is not enough, it will be increased whenever necessary
    unsigned long long int nb_initial_pts = (unsigned long long int) ((DictFloat(user_info, "activity") * 1.e9));
    // Number of points generated = nb_points (= Activity) + 20 %
    unsigned long long int nb_pts_to_gen = (unsigned long long int) (1.2 * nb_initial_pts);
    GenerateSamplesPointset(nb_pts_to_gen);
    fVoxelPositionGenerator->SetPointSet(generated_pts);
}


void GamVoxelsSource::InitializeDirection(py::dict user_info) {
    fSPS->SetAngGenerator(fVoxelDirectionGenerator);

    // Only the isotropic direction in considered in the voxelized case for now
    auto duser_info = py::dict(user_info["direction"]);
    auto ang_type = DictStr(duser_info, "type");
    std::vector<std::string> l = {"iso"};
    CheckIsIn(ang_type, l);

    fVoxelDirectionGenerator->SetPosDistributionGamVox(fVoxelPositionGenerator);

    fVoxelDirectionGenerator->SetPointSet(generated_pts);
}



void GamVoxelsSource::SetSamplerType(std::string sampler_type) {
    std::string WhiteNoise_type = "WN";
    std::string Halton_type = "LD";

    if (sampler_type == WhiteNoise_type) {
        sampler = new SamplerWhitenoise;
    }
    else if ( sampler_type == Halton_type) {
        sampler = new SamplerHalton;
    }
    scramblerCP = new ScramblingCranleyPatterson;

}


void GamVoxelsSource::GenerateSamplesPointset(unsigned long long int nb_points) {
    sampler->generateSamples(generated_pts, nb_points);
    Pointset scrambled_pts;
    scramblerCP->scramble(generated_pts, scrambled_pts);
    generated_pts = scrambled_pts;
}