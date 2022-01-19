/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#ifndef GamSPSVoxelsPosDistribution_h
#define GamSPSVoxelsPosDistribution_h

#include <utility>

#include "G4ParticleDefinition.hh"
#include "GamSPSPosDistribution.h"
#include "itkImage.h"
#include <fstream>

//#include <samplers/Sampler.hpp>
#include <samplers/SamplerWhitenoise.hpp>
#include <samplers/SamplerHalton.hpp>
#include <scrambling/ScramblingCranleyPatterson.hpp>
#include <io/fileIO.hpp>

#include "GamSamplerManager.h"



using namespace utk;


typedef double T;
const unsigned int D = 3;
typedef Point< D, T> P;



class GamSPSVoxelsPosDistribution : public GamSPSPosDistribution {

public:

    GamSPSVoxelsPosDistribution();

    virtual ~GamSPSVoxelsPosDistribution() {
        m_ostream_pos_indexes.close();
    }

    // Cannot inherit from GenerateOne
    virtual G4ThreeVector VGenerateOne();

    // typedef for vector of vector
    typedef std::vector<double> VD;
    typedef std::vector<VD> VD2;
    typedef std::vector<std::vector<VD>> VD3;

    void SetCumulativeDistributionFunction(VD vz, VD2 vy, VD3 vx);

//    GamSamplerManager * samplerManager;

    Pointset< D, T, P> generated_pts;

    void SetSamplerType(std::string sampler_type);

    void AddPointsToSamplerSequence(long long int nb_pts);

    std::string points01_filename;

    std::string pos_filename;
    std::ofstream m_ostream_pos_indexes;

    // Image type is 3D float by default (the pixel data are not used
    // nor even allocated. Only useful to convert pixel coordinates
    // to physical coordinates.
    typedef itk::Image<float, 3> ImageType;

    // The image is accessible from py side
    ImageType::Pointer cpp_image;

    G4ThreeVector fGlobalTranslation;
    G4RotationMatrix fGlobalRotation;

    

protected:
    VD3 fCDFX;
    VD2 fCDFY;
    VD fCDFZ;
};

#endif // GamSPSVoxelsPosDistribution_h
