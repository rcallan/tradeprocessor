#ifndef ____EntryProcessor__
#define ____EntryProcessor__

#include <vector>
#include <string>
#include "Calc.h"

class EntryProcessor {
public:
    void process(std::vector<std::string>& entry);
    void write();
private:
    // std::vector<Calc> calcs;
    // MaxTimeGapCalc calc;
    // VolumeCalc calc;
    // MaxPriceCalc calc;
    WeightedAvgPriceCalc calc;
};

#endif