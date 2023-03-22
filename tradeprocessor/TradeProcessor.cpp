#include "StreamProcessor.h"
#include <iostream>
#include "Calc.h"
#include <iostream>
#include "CalcInfoWriter.h"
#include "GetCalcs.h"
#include <chrono>

int main(int argc, char** argv) {
    std::string inputPath = "exampledata/input.csv";
    // std::string inputPath = "exampledata/example.csv";
    std::string outputPath = "exampledata/output.csv";

    // columns will be written to the output csv file in the order that calc types are listed here
    typedef std::tuple<MaxTimeGapCalc, VolumeCalc, WeightedAvgPriceCalc, MaxPriceCalc> CalcTypes;

    std::unordered_map<std::string, std::unordered_map<std::string, long>> calcInfoMap;
    
    StreamProcessor<CalcTypes> sp(inputPath, calcInfoMap);
    CalcInfoWriter ciw(outputPath, calcInfoMap, sp.getMapKeys());

    auto start = std::chrono::steady_clock::now();

    sp.process();

    auto end = std::chrono::steady_clock::now();

    auto diff = end - start;
    std::cout << "processing took " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;

    ciw.write();
}