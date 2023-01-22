#include "StreamProcessor.h"
#include <iostream>
#include "Calc.h"
#include <iostream>

int main(int argc, char** argv) {
    char path[] = "exampledata/input.csv";

    StreamProcessor sp(path);

    EntryProcessor* ep = new EntryProcessor();

    Calc<MaxTimeGapCalc>* mtgc = new MaxTimeGapCalc();
    Calc<VolumeCalc>* vc = new VolumeCalc();
    Calc<WeightedAvgPriceCalc>* wapc = new WeightedAvgPriceCalc();
    Calc<MaxPriceCalc>* mpc = new MaxPriceCalc();

    ep->calcs = std::make_tuple(mtgc, vc, wapc, mpc);

    sp.setEntryProcessor(ep);

    sp.process();
    sp.write();
}