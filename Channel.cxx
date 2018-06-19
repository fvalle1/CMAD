#include "Channel.h"

Channel::Channel(Int_t channelNum): fLastFilledBin(0), fChannelNum(channelNum), fFitted(kFALSE) {
    fHist = new TH1F(Form("%d",channelNum), Form("Distribution ch:%d",channelNum), parameters::kNumOfBins, parameters::kThrMin, parameters::kThrMax);
    fHist->SetLineColor(kCyan-3);

    fParams = new Double_t[3];
}

void Channel::SetBinContent(Int_t bin, Int_t multiplicity){
    fHist->SetBinContent(++fLastFilledBin, multiplicity);
}

Double_t *Channel::Fit() {
    if(!fFitted) {
        auto gaus = new TF1("fit", "[0]*TMath::Gaus(x,[1],[2])");
        gaus->SetParameter(0, fHist->GetMaximum());
        gaus->SetParameter(1, fHist->GetMean());
        gaus->SetParameter(2, fHist->GetStdDev());

        gaus->SetParLimits(1, parameters::kThrMin, parameters::kThrMax);
        gaus->SetParLimits(2, 0, 10); //10 is the max of the distribution of sigmas

        fHist->Fit(gaus, "MQ");

        fParams[0] = fChannelNum;
        fParams[1] = gaus->GetParameter(1);
        fParams[2] = gaus->GetParameter(2);

        fFitted = kTRUE;
        gaus->Delete();
    }



    printf("\nchannel:%d\tmean:%.2f\tstd:%.2f",fChannelNum,fParams[1],fParams[2]);

    return fParams;
}
