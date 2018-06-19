//
// Created by Filippo Valle on 11/06/2018.
//

#include "AnalysisManager.h"


AnalysisManager::AnalysisManager() {
    fChannels.reserve(parameters::kNumOfChannels);

    for(Int_t i=0; i< parameters::kNumOfChannels; i++){
        fChannels.emplace_back(new Channel(i));
    }

    fCanvases = new TCanvas*[parameters::kNumOfChannels/parameters::kPadPerCanvas];

    LoadData();
}

void AnalysisManager::ReadFile(Int_t threshold){
    auto filename = TString(Form("%s/thr_scan_%d.data", parameters::kDirectory.Data(), threshold));

    std::__1::fstream file(filename);
    Int_t ichannel = 0;
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            fChannels[ichannel]->SetBinContent(threshold,std::stoi(line));
            ichannel++;
        }
    } else {
        std::__1::cerr << "file " << filename << " not found\n";
    }

    file.close();
}

void AnalysisManager::LoadData() {
    for(auto thr=parameters::kThrMin; thr < parameters::kThrMax; thr+=parameters::kDeltaThr){
        ReadFile(thr);
    }
}

AnalysisManager & AnalysisManager::ToFile(){
    TH1* tempHist;

    auto file = new TFile(parameters::kRootOutputFile.Data(), "RECREATE");
    file->cd();

    for(Int_t i=0; i< parameters::kNumOfChannels; i++){
        tempHist = fChannels[i]->GetTH1();
        tempHist->Write(Form("thr_scan_%d",i), TObject::kSingleKey || TObject::kOverwrite);
        file->Flush();
    }

    file->Close();

    OutputTXT();

    return *this;
}

void AnalysisManager::OutputTXT() {

    std::__1::fstream outputfile(parameters::kOutputFile.Data(), std::__1::ios::out);
    Double_t *buffer;
    for(Int_t i=0; i< parameters::kNumOfChannels; i++){
        buffer = fChannels[i]->Fit();
        if((buffer[1]>parameters::kThrMin & buffer[1]<parameters::kThrMax)) {
            outputfile << buffer[0] << "," << buffer[1] << "," << buffer[2] << "\n";
        }
    }

    outputfile.close();
}

AnalysisManager & AnalysisManager::Distributions() {
    fDist = new TH1 *[2];

    fDist[0] = new TH1F("mean", "mean dist", 10, parameters::kThrMin, parameters::kThrMax);
    fDist[1] = new TH1F("sigma", "mean sigma", 10, 0, (parameters::kThrMax - parameters::kThrMin) / 4.);
    Double_t *buffer;

    for (Int_t i = 0; i < parameters::kNumOfChannels; i++) {
        buffer = fChannels[i]->Fit();
        if ((buffer[1] > parameters::kThrMin & buffer[1] < parameters::kThrMax)) {
            fDist[0]->Fill(buffer[1]);
            fDist[1]->Fill(buffer[2]);
        }
    }

    auto file = new TFile(parameters::kRootOutputFile.Data(), "UPDATE");
    fDist[0]->Write("mean_dist", TObject::kSingleKey || TObject::kOverwrite);
    fDist[1]->Write("sigma_dist", TObject::kSingleKey || TObject::kOverwrite);

    file->Close();

    return *this;
}

AnalysisManager & AnalysisManager::PlotAllChannels(Bool_t fit) {
    auto file = new TFile(parameters::kRootOutputFile.Data(), "UPDATE");
    file->cd();

    TCanvas * bufferCanvas;

    for(Int_t iCanv = 0; iCanv < parameters::kNumOfChannels/parameters::kPadPerCanvas; iCanv++){
        auto cName = TString(Form("board_side_%d",iCanv));
        fCanvases[iCanv] = new TCanvas(cName, cName, 0, 0, 1050, 750);
        bufferCanvas=fCanvases[iCanv];
        bufferCanvas->Divide(parameters::kPadPerCanvas/4, 4);

        for(Int_t iPad = 1; iPad <= parameters::kPadPerCanvas; iPad++){
            bufferCanvas->cd(iPad);
            fChannels[iCanv*parameters::kPadPerCanvas+iPad-1]->GetTH1()->Draw();
            if(fit) fChannels[iCanv * parameters::kPadPerCanvas + iPad - 1]->Fit();
        }

        bufferCanvas->Write(cName, TObject::kSingleKey || TObject::kOverwrite);
        bufferCanvas->Print(Form("%s.pdf",cName.Data()));
        file->Flush();
    }

    file->Close();

    return *this;
}
