#include "StreamProcessor.h"
#include <iostream>
#include "Calc.h"
#include <iostream>
#include "CalcInfoWriter.h"
#include "GetCalcs.h"

int main(int argc, char** argv) {
    char inputPath[] = "exampledata/input.csv";
    // char inputPath[] = "exampledata/example.csv";
    char outputPath[] = "exampledata/output.csv";

    typedef std::tuple<MaxTimeGapCalc, VolumeCalc, WeightedAvgPriceCalc, MaxPriceCalc> CalcTypes;

    std::map<std::string, std::unordered_map<std::string, long>> calcInfoMap;

    StreamProcessor<GetCalcs<CalcTypes>::type> sp(inputPath, calcInfoMap, GetCalcs<CalcTypes>{}.calcs);
    CalcInfoWriter ciw(outputPath, calcInfoMap, sp.getMapKeys());

    sp.process();
    ciw.write();
}