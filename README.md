# CMAD chip

## Compile
```
root .x compile.C
```

## Run

First of all create an object `auto manager = AnalysisManager()`

To plot: `manager.PlotAllChannels(kTRUE)` kTRUE/kFALSE is for Fit

To write data to a .root and a .txt file `manager.ToFile()`
