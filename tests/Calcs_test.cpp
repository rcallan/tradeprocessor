#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "StreamProcessor.h"
#include "Calc.h"
#include <tuple>
#include "GetCalcs.h"

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
    typedef std::tuple<MaxTimeGapCalc> CalcTypes;

    std::map<std::string, std::unordered_map<std::string, long>> calcInfoMap;

    StreamProcessor<GetCalcs<CalcTypes>::type> sp(calcInfoMap, GetCalcs<CalcTypes>{}.calcs);

    for (int i = 0; i < entries.size(); i++) {
        sp.tupleProcess(entries[i]);
    }

    EXPECT_EQ(sp.getCalcInfo("aaa", "maxGap"), 5787);
}

TEST(CalcsTest, TestVolCalc)
{
    typedef std::tuple<VolumeCalc> CalcTypes;

    std::map<std::string, std::unordered_map<std::string, long>> calcInfoMap;

    StreamProcessor<GetCalcs<CalcTypes>::type> sp(calcInfoMap, GetCalcs<CalcTypes>{}.calcs);

    for (int i = 0; i < entries.size(); i++) {
        sp.tupleProcess(entries[i]);
    }

    EXPECT_EQ(sp.getCalcInfo("aac", "vol"), 41);   
}

TEST(CalcsTest, TestWapCalc)
{
    typedef std::tuple<WeightedAvgPriceCalc> CalcTypes;

    std::map<std::string, std::unordered_map<std::string, long>> calcInfoMap;

    StreamProcessor<GetCalcs<CalcTypes>::type> sp(calcInfoMap, GetCalcs<CalcTypes>{}.calcs);

    for (int i = 0; i < entries.size(); i++) {
        sp.tupleProcess(entries[i]);
    }

    EXPECT_EQ(sp.getCalcInfo("aab", "weightedAvgPrice"), 810);
}

TEST(CalcsTest, TestMaxPriceCalc)
{
    typedef std::tuple<MaxPriceCalc> CalcTypes;

    std::map<std::string, std::unordered_map<std::string, long>> calcInfoMap;

    StreamProcessor<GetCalcs<CalcTypes>::type> sp(calcInfoMap, GetCalcs<CalcTypes>{}.calcs);

    for (int i = 0; i < entries.size(); i++) {
        sp.tupleProcess(entries[i]);
    }

    EXPECT_EQ(sp.getCalcInfo("aaa", "maxPrice"), 1222);
}
