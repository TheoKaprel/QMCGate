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
#include <iostream>
#include <sstream>


GamSPSVoxelsPosDistribution::GamSPSVoxelsPosDistribution() {
    // Create the image pointer
    // The size and allocation will be performed on the py side
    cpp_image = ImageType::New();

    // default position
    fGlobalTranslation = G4ThreeVector();
    fGlobalRotation = G4RotationMatrix();

    // iteration that determines which point of the sampled set to pick
    // start at 1 because the two first lines are domain bounds
    iter = 1;

}

GamSPSVoxelsPosDistribution::~GamSPSVoxelsPosDistribution()  {
}

void GamSPSVoxelsPosDistribution::SetCumulativeDistributionFunction(VD vz, VD2 vy, VD3 vx) {
    // Warning : this is a COPY of all cumulative distribution functions
    fCDFZ = vz;
    fCDFY = vy;
    fCDFX = vx;
}


void GamSPSVoxelsPosDistribution::SetPointSet(Pointset ptset) {
    generated_pts = ptset;
}


G4ThreeVector GamSPSVoxelsPosDistribution::VGenerateOne() {
    ++iter;

    double p1 = generated_pts[iter].pos()[0];
    double p2 = generated_pts[iter].pos()[1];
    double p3 = generated_pts[iter].pos()[2];

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

    // move according to mother volume
    position = fGlobalRotation * position + fGlobalTranslation;

    return position;
}

