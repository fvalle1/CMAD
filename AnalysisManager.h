//
// Created by Filippo Valle on 11/06/2018.
//

#ifndef BOARD_FILEMANAGER_H
#define BOARD_FILEMANAGER_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#include "Channel.h"
#include "Parameters.h"
#include "TFile.h"
#include "TCanvas.h"


class AnalysisManager {
public:
    AnalysisManager();
    AnalysisManager & ToFile();
    AnalysisManager &PlotAllChannels(Bool_t fit = kFALSE);
    AnalysisManager & Distributions();


    inline TH1F* operator[](Int_t channel){return fChannels[channel]->GetTH1();};
    inline Double_t * operator()(Int_t channel){return fChannels[channel]->Fit();};


private:
    void ReadFile(Int_t threshold);
    void LoadData();
    void OutputTXT();

    TCanvas* *fCanvases;
    std::vector<Channel*> fChannels;
    TH1 **fDist;
    TFile *rootfile;
};


#endif //BOARD_FILEMANAGER_H
