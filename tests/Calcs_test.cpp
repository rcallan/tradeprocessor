#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "StreamProcessor.h"
#include "Calc.h"
#include <tuple>

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

// std::vector<std::vector<std::string>> expected = {
//     {"aaa", "5787", "40", "1161", "1222"},
//     {"aab", "6103", "69", "810", "907"}, 
//     {"aac", "3081", "41", "559", "638"}
// };

TEST(CalcsTest, TestMaxTimeGapCalc)
{
    typedef std::tuple<
        std::shared_ptr<Calc<MaxTimeGapCalc>>
    > CalcTypes;

    std::map<std::string, std::unordered_map<std::string, long>> calcInfoMap;

    StreamProcessor<CalcTypes> sp(calcInfoMap);

    std::shared_ptr<Calc<MaxTimeGapCalc>> mtgc = std::make_shared<MaxTimeGapCalc>();

    sp.setCalcs(std::make_tuple(mtgc));

    for (int i = 0; i < entries.size(); i++) {
        sp.tupleProcess(entries[i]);
    }

    EXPECT_EQ(sp.getCalcInfo("aaa", "maxGap"), 5787);
    
}

TEST(CalcsTest, TestVolCalc)
{
    typedef std::tuple<
        std::shared_ptr<Calc<VolumeCalc>>
    > CalcTypes;

    std::map<std::string, std::unordered_map<std::string, long>> calcInfoMap;

    StreamProcessor<CalcTypes> sp(calcInfoMap);

    std::shared_ptr<Calc<VolumeCalc>> vc = std::make_shared<VolumeCalc>();

    sp.setCalcs(std::make_tuple(vc));

    for (int i = 0; i < entries.size(); i++) {
        sp.tupleProcess(entries[i]);
    }

    EXPECT_EQ(sp.getCalcInfo("aac", "vol"), 41);
    
}

TEST(CalcsTest, TestWapCalc)
{
    typedef std::tuple<
        std::shared_ptr<Calc<WeightedAvgPriceCalc>>
    > CalcTypes;

    std::map<std::string, std::unordered_map<std::string, long>> calcInfoMap;

    StreamProcessor<CalcTypes> sp(calcInfoMap);

    std::shared_ptr<Calc<WeightedAvgPriceCalc>> wapc = std::make_shared<WeightedAvgPriceCalc>();

    sp.setCalcs(std::make_tuple(wapc));

    for (int i = 0; i < entries.size(); i++) {
        sp.tupleProcess(entries[i]);
    }

    EXPECT_EQ(sp.getCalcInfo("aab", "weightedAvgPrice"), 810);
    
}

TEST(CalcsTest, TestMaxPriceCalc)
{
    typedef std::tuple<
        std::shared_ptr<Calc<MaxPriceCalc>>
    > CalcTypes;

    std::map<std::string, std::unordered_map<std::string, long>> calcInfoMap;

    StreamProcessor<CalcTypes> sp(calcInfoMap);

    std::shared_ptr<Calc<MaxPriceCalc>> mpc = std::make_shared<MaxPriceCalc>();

    sp.setCalcs(std::make_tuple(mpc));

    for (int i = 0; i < entries.size(); i++) {
        sp.tupleProcess(entries[i]);
    }

    EXPECT_EQ(sp.getCalcInfo("aaa", "maxPrice"), 1222);
    
}
