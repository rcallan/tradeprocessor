#ifndef ____EntryProcessor__
#define ____EntryProcessor__

#include <vector>
#include <string>
#include "Calc.h"
#include <tuple>
#include <set>
#include <string>

class EntryProcessor {
public:
    void process(std::vector<std::string>& entry);
    void write();
// private:
    std::tuple<Calc<MaxTimeGapCalc>*, Calc<VolumeCalc>*, Calc<WeightedAvgPriceCalc>*, Calc<MaxPriceCalc>*> calcs;
    std::set<std::string> symbols {};
};

#endif