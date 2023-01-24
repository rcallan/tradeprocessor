#include "StreamProcessor.h"
#include <iostream>
#include "Calc.h"
#include <iostream>
#include "CalcInfoWriter.h"

int main(int argc, char** argv) {
    char inputPath[] = "exampledata/input.csv";
    // char inputPath[] = "exampledata/example.csv";
    char outputPath[] = "exampledata/output.csv";

    typedef std::tuple<
        std::shared_ptr<Calc<MaxTimeGapCalc>>,
        std::shared_ptr<Calc<VolumeCalc>>,
        std::shared_ptr<Calc<WeightedAvgPriceCalc>>,
        std::shared_ptr<Calc<MaxPriceCalc>>
    > CalcTypes;

    std::map<std::string, std::unordered_map<std::string, long>> calcInfoMap;

    StreamProcessor<CalcTypes> sp(inputPath, calcInfoMap);

    std::shared_ptr<Calc<MaxTimeGapCalc>> mtgc = std::make_shared<MaxTimeGapCalc>();
    std::shared_ptr<Calc<VolumeCalc>> vc = std::make_shared<VolumeCalc>();
    std::shared_ptr<Calc<WeightedAvgPriceCalc>> wapc = std::make_shared<WeightedAvgPriceCalc>();
    std::shared_ptr<Calc<MaxPriceCalc>> mpc = std::make_shared<MaxPriceCalc>();

    sp.setCalcs(std::make_tuple(mtgc, vc, wapc, mpc));

    auto mapKeys = sp.getMapKeys();
    CalcInfoWriter ciw(outputPath, calcInfoMap, mapKeys);

    sp.process();
    ciw.write();

}