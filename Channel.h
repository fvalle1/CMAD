#ifndef BOARD_CHANNEL_H
#define BOARD_CHANNEL_H

#include <vector>

#include "TH1.h"
#include "TH1F.h"
#include "TF1.h"
#include "TMath.h"

#include "Parameters.h"

class Channel{
public:
    explicit Channel(Int_t channelNum);
    void SetBinContent(Int_t bin, Int_t multiplicity);

    inline TH1F* GetTH1(){return (TH1F*)fHist;}
    Double_t *Fit();

private:

    TH1 *fHist;
    Double_t *fParams;
    Int_t fChannelNum;
    Int_t fLastFilledBin;
    Bool_t fFitted;
};


#endif