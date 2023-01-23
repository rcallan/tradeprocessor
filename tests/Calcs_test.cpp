#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "StreamProcessor.h"
#include "Calc.h"
#include <tuple>

TEST(CalcsTest, TestProcess)
{
    std::vector<std::vector<std::string>> entries = {
        {"52924702", "aaa", "13", "1136"},
        {"52924702", "aac", "20", "477"},
        {"52925641", "aab", "31", "907"},
        {"52927350", "aab", "29", "724"},
        {"52927783", "aac", "21", "638"},
        {"52930489", "aaa", "18", "1222"},
        {"52931654", "aaa", "9", "1078"},
        {"52933453", "aab", "9", "756"}
    };

    std::vector<std::vector<std::string>> expected = {
        {"aaa", "5787", "40", "1161", "1222"},
        {"aab", "6103", "69", "810", "907"}, 
        {"aac", "3081", "41", "559", "638"}
    };

    typedef std::tuple<
        std::shared_ptr<Calc<MaxTimeGapCalc>>, 
        std::shared_ptr<Calc<VolumeCalc>>, 
        std::shared_ptr<Calc<WeightedAvgPriceCalc>>, 
        std::shared_ptr<Calc<MaxPriceCalc>>
    > tupleforcalcs;

    StreamProcessor<tupleforcalcs> sp;

    std::shared_ptr<Calc<MaxTimeGapCalc>> mtgc = std::make_shared<MaxTimeGapCalc>();
    std::shared_ptr<Calc<VolumeCalc>> vc = std::make_shared<VolumeCalc>();
    std::shared_ptr<Calc<WeightedAvgPriceCalc>> wapc = std::make_shared<WeightedAvgPriceCalc>();
    std::shared_ptr<Calc<MaxPriceCalc>> mpc = std::make_shared<MaxPriceCalc>();

    auto calcs = std::make_tuple(mtgc, vc, wapc, mpc);

    sp.setCalcs(calcs);

    for (int i = 0; i < entries.size(); i++) {
        sp.tupleProcess(entries[i]);
        sp.insertSymbol(entries[i][1]);
    }

    // char writePath[] = "../exampledata/testoutput.csv";
    // sp.setWritePath(writePath);

    // sp.write();

    // EXPECT_EQ(static_cast<MaxTimeGapCalc*>(mtgc)->getMaxGap("aaa"), 5787);
    
}

// could probably add a test for each calc we have