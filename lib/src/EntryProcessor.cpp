#include "EntryProcessor.h"

void EntryProcessor::process(std::vector<std::string>& entry) {
    // Calc<MaxTimeGapCalc>* tmp = &calc;
    // Calc<VolumeCalc>* tmp = &calc;
    // Calc<MaxPriceCalc>* tmp = &calc;
    Calc<WeightedAvgPriceCalc>* tmp = &calc;
    
    tmp->process(entry);
}

void EntryProcessor::write() {
    char path[] = "exampledata/output.csv";
    calc.write(path);
}