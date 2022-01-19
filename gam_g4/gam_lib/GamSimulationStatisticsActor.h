/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#ifndef GamSimulationStatisticsActor_h
#define GamSimulationStatisticsActor_h

#include <pybind11/stl.h>
#include "GamVActor.h"
#include "GamHelpers.h"

namespace py = pybind11;

class GamSimulationStatisticsActor : public GamVActor {

public:

    //explicit GamSimulationStatisticsActor(std::string type_name);
    explicit GamSimulationStatisticsActor(py::dict &user_info);

    virtual ~GamSimulationStatisticsActor();

    // Called when the simulation start (master thread only)
    virtual void StartSimulationAction();

    // Called when the simulation end (master thread only)
    virtual void EndSimulationAction();

    // Called every time a Run starts (all threads)
    virtual void BeginOfRunAction(const G4Run *run);

    // Called every time a Run ends (all threads)
    virtual void EndOfRunAction(const G4Run *run);

    // Called every time a Track starts (all threads)
    virtual void PreUserTrackingAction(const G4Track *track);

    // Called every time a batch of step must be processed
    virtual void SteppingAction(G4Step *, G4TouchableHistory *);

    py::dict GetCounts() { return fCounts; }

    void CreateCounts();

protected:
    int fRunCount;
    int fEventCount;
    long int fTrackCount;
    long int fStepCount;
    std::map<std::string, long int> fTrackTypes;
    double fDuration;
    std::chrono::system_clock::time_point fStartTime;
    std::chrono::system_clock::time_point fStopTime;
    std::chrono::steady_clock::time_point fStartTimeDuration;
    std::chrono::steady_clock::time_point fStopTimeDuration;
    bool fTrackTypesFlag;

    py::dict fCounts;

};

#endif // GamSimulationStatisticsActor_h
