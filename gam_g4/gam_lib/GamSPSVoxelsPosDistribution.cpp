/* --------------------------------------------------
   Copyright (C): OpenGate Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#include <Randomize.hh>
#include "GamSPSVoxelsPosDistribution.h"
#include "GamHelpers.h"
#include <fstream>



GamSPSVoxelsPosDistribution::GamSPSVoxelsPosDistribution() {
    // Create the image pointer
    // The size and allocation will be performed on the py side
    cpp_image = ImageType::New();

    // default position
    fGlobalTranslation = G4ThreeVector();
    fGlobalRotation = G4RotationMatrix();

    points01_filename = "/export/home/tkaprelian/Desktop/Sampling/code/output/points01/points01.edat";
    pos_filename = "/export/home/tkaprelian/Desktop/Sampling/code/output/samples/sampled_position_indexes.edat";

    assert(!m_ostream_pos_indexes.is_open());
    m_ostream_pos_indexes.open(pos_filename);

}

void GamSPSVoxelsPosDistribution::SetCumulativeDistributionFunction(VD vz, VD2 vy, VD3 vx) {
    // Warning : this is a COPY of all cumulative distribution functions
    fCDFZ = vz;
    fCDFY = vy;
    fCDFX = vx;
}

void GamSPSVoxelsPosDistribution::SetSamplerType(std::string sampler_type) {
    std::string WhiteNoise_type = "WhiteNoise";
    std::string Halton_type = "Halton";

    if (sampler_type == WhiteNoise_type) {
//        SamplerWhitenoise * sampler = new SamplerWhitenoise();

        SamplerWhitenoise sWN;
        sampler = &sWN;
        std::cout << "ok for sampler type attrib white noise" << std::endl;
    }
    else if ( sampler_type == Halton_type) {
        SamplerHalton sH;
        sampler = &sH;
        std::cout << "ok for sampler type attrib Halton" << std::endl;
    }
}

void GamSPSVoxelsPosDistribution::AddPointsToSamplerSequence(unsigned long long int nb_pts) {

    std::cout << " OK 1 " << std::endl;

    sampler->generateSamples(generated_pts, nb_pts);

//
//    scramblerCP->scramble<D, T, P>(generated_pts, generated_pts);

//    PointsetWriter<D, T,P> writer;
//    writer.open(points01_filename);
//    writer.writePointset(generated_pts);
//    writer.close();
}


G4ThreeVector GamSPSVoxelsPosDistribution::VGenerateOne() {

    double p1 = G4UniformRand();
    double p2 = G4UniformRand();
    double p3 = G4UniformRand();

    // Get Cumulative Distribution Function for Z
    int i = 0;
    while (p1 > fCDFZ[i]) i++;

    // Get Cumulative Distribution Function for Y, knowing Z
    int j = 0;
    while (p2 > fCDFY[i][j]) j++;

    // Get Cumulative Distribution Function for X, knowing X and Y
    int k = 0;
    while (p3 > fCDFX[i][j][k]) k++;

    // get random position within the voxel.
    // A pixel coordinate is centered: we add random-0.5 to be in the range[-0.5:0.5]
    itk::ContinuousIndex<double, 3> index;
    index[0] = k + G4UniformRand() - 0.5;
    index[1] = j + G4UniformRand() - 0.5;
    index[2] = i + G4UniformRand() - 0.5;

    // convert to physical coordinate
    itk::Point<double, 3> point;
    cpp_image->TransformContinuousIndexToPhysicalPoint(index, point);
    G4ThreeVector position(point[0], point[1], point[2]);

    m_ostream_pos_indexes << index[0] << '\t' <<  index[1] << '\t' <<   index[2] << std::endl;


    // move according to mother volume
    position = fGlobalRotation * position + fGlobalTranslation;

    return position;
}

