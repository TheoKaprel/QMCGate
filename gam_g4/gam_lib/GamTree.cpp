/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#include "G4GenericAnalysisManager.hh"
#include "GamTree.h"

GamTree::GamTree(std::string name) {
    fTreeName = name;
}

GamTree::~GamTree() {
}


void GamTree::AddBranch(std::string vname) {
    for (auto branch:GamVBranch::fAvailableBranches) {
        if (branch->fBranchName == vname) {
            auto b = branch->CreateBranchCopy();
            fBranches.push_back(b);
            b->fBranchId = fBranches.size() - 1;
            fBranchesMap[vname] = b;
            return;
        }
    }
    std::ostringstream oss;
    oss << "Cannot find a branch name '" << vname
        << "' in the list of available branches ("
        << GamVBranch::fAvailableBranches.size() << ") "
        << GamVBranch::DumpAvailableBranchesList();
    Fatal(oss.str());
}

void GamTree::FillStep(G4Step *step, G4TouchableHistory *history) {
    for (auto branch:fBranches)
        branch->FillStep(step, history);
}

GamVBranch *GamTree::GetBranch(std::string vname) {
    // FIXME check exist
    return fBranchesMap[vname];
}

GamBranch<G4ThreeVector> *GamTree::GetThreeVectorBranch(std::string vname) {
    return GetBranch(std::move(vname))->GetAsThreeVectorBranch();
}

GamBranch<double> *GamTree::GetDoubleBranch(std::string vname) {
    return GetBranch(vname)->GetAsDoubleBranch();
}

GamBranch<std::string> *GamTree::GetStringBranch(std::string vname) {
    return GetBranch(vname)->GetAsStringBranch();
}

void GamTree::WriteToRoot(std::string filename) {
    auto n = fBranches[0]->size();
    if (n == 0) {
        std::cout << "WARNING no branch in tree: " << filename << std::endl;
        return;
    }
    auto fAnalysisManager = G4GenericAnalysisManager::Instance();
    fAnalysisManager->OpenFile(filename);
    fAnalysisManager->CreateNtuple(fTreeName, "Hits collection");
    int i = 0;
    for (auto &b:fBranches) {
        if (b->size() != n) {
            Fatal("Error branches does not have the same size " + fTreeName + " " + b->fBranchName);
        }
        b->fBranchRootId = i;
        if (b->fBranchType == 'D') fAnalysisManager->CreateNtupleDColumn(b->fBranchName);
        if (b->fBranchType == 'S') fAnalysisManager->CreateNtupleSColumn(b->fBranchName);
        if (b->fBranchType == 'I') fAnalysisManager->CreateNtupleIColumn(b->fBranchName);
        if (b->fBranchType == '3') {
            fAnalysisManager->CreateNtupleDColumn(b->fBranchName + "_X");
            fAnalysisManager->CreateNtupleDColumn(b->fBranchName + "_Y");
            fAnalysisManager->CreateNtupleDColumn(b->fBranchName + "_Z");
            i += 2;
        }
        i++;
    }
    fAnalysisManager->FinishNtuple();
    // FIXME Check size of all branches
    for (unsigned long j = 0; j < fBranches[0]->size(); j++) {
        for (auto &b:fBranches) {
            b->FillToRoot(fAnalysisManager, j);
        }
        fAnalysisManager->AddNtupleRow();
    }
    fAnalysisManager->Write();
    fAnalysisManager->CloseFile();
    delete fAnalysisManager; // important to allow several successive write
}

std::string GamTree::Dump() { // FIXME may be on py side (?)
    std::ostringstream oss;
    oss << "Tree: " << fTreeName << " " << fBranches.size() << " branches: ";
    for (auto b:fBranches) {
        oss << b->fBranchName << " (" << b->fBranchType << " " << b->size() << ") ";
    }
    return oss.str();
}


void GamTree::FreeBranches() {
    for (auto branch:fBranches) {
        //std::cout << "deleting " << branch->fBranchName << " " << std::endl;
        delete branch;
    }
}
