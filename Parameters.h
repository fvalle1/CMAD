//
// Created by Filippo Valle on 11/06/2018.
//

#ifndef BOARD_PARAMETERS_H
#define BOARD_PARAMETERS_H


namespace parameters{
    const Int_t kThrMin = 600;
    const Int_t kThrMax = 730;
    const Int_t kNumOfBins = 30;
    const Int_t kNumOfChannels = 192;
    const Int_t kDeltaThr = 2;
    const Int_t kPadPerCanvas = 32;
    const TString kDirectory = "/Users/filippo/Developer/board/thr_scan_11Jun2018";
    const TString kOutputFile = "output.txt";
    const TString kRootOutputFile = "output.root";
}

#endif //BOARD_PARAMETERS_H
