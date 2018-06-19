//
// Created by Filippo Valle on 11/06/2018.
//

#include "TSystem.h"

int compile(){
    gSystem->CompileMacro("Channel.cxx", "kO");
    gSystem->CompileMacro("AnalysisManager.cxx", "kO");
    return 0;
}
