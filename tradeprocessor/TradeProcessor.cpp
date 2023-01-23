#include "StreamProcessor.h"
#include <iostream>
#include "Calc.h"
#include <iostream>

int main(int argc, char** argv) {
    char inputPath[] = "exampledata/input.csv";
    // char path[] = "exampledata/example.csv";
    char outputPath[] = "exampledata/output.csv";

    typedef std::tuple<
        std::shared_ptr<Calc<MaxTimeGapCalc>>,
        std::shared_ptr<Calc<VolumeCalc>>,
        std::shared_ptr<Calc<WeightedAvgPriceCalc>>,
        std::shared_ptr<Calc<MaxPriceCalc>>
    > CalcTypes;

    StreamProcessor<CalcTypes> sp(inputPath, outputPath);

    std::shared_ptr<Calc<MaxTimeGapCalc>> mtgc = std::make_shared<MaxTimeGapCalc>();
    std::shared_ptr<Calc<VolumeCalc>> vc = std::make_shared<VolumeCalc>();
    std::shared_ptr<Calc<WeightedAvgPriceCalc>> wapc = std::make_shared<WeightedAvgPriceCalc>();
    std::shared_ptr<Calc<MaxPriceCalc>> mpc = std::make_shared<MaxPriceCalc>();

    sp.setCalcs(std::make_tuple(mtgc, vc, wapc, mpc));

    sp.process();
    sp.write();

}