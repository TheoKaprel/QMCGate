/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#ifndef GamHitsCollectionActor_h
#define GamHitsCollectionActor_h

#include <pybind11/stl.h>

#include "G4Cache.hh"
#include "GamVActor.h"
#include "GamHelpers.h"
#include "GamTree.h"

namespace py = pybind11;

class GamHitsCollectionActor : public GamVActor {

public:

    explicit GamHitsCollectionActor(py::dict &user_info);

    virtual ~GamHitsCollectionActor();

    // Called when the simulation start (master thread only)
    virtual void StartSimulationAction();

    // Called when the simulation end (master thread only)
    virtual void EndSimulationAction();

    // Called every time a Run starts (all threads)
    virtual void BeginOfRunAction(const G4Run *run);

    // Called every time a Run ends (all threads)
    virtual void EndOfRunAction(const G4Run *run);

    // Called every time a Event starts (all threads)
    virtual void BeginOfEventAction(const G4Event *event);

    // Called every time a Event endss (all threads)
    virtual void EndOfEventAction(const G4Event *event);

    // Called every time a Track starts (all threads)
    virtual void PreUserTrackingAction(const G4Track *track);

    // Called every time a batch of step must be processed
    virtual void SteppingAction(G4Step *, G4TouchableHistory *);

    // Helper (will be availble from py)
    std::shared_ptr<GamTree> GetHits();

    std::vector<std::string> fStepFillNames;

protected:
    std::string fOutputFilename;
    std::shared_ptr<GamTree> fHits;
    std::vector<std::string> fUserBranchNames;
};

#endif // GamHitsCollectionActor_h
