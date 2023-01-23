#ifndef ____Calc__
#define ____Calc__

#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <fstream>

template <typename T>
class Calc {
public:
    void process(std::vector<std::string>& entry, std::map<std::string, std::unordered_map<std::string, long>>& calcInfoMap) {
        static_cast<T*>(this)->processEntry(entry, calcInfoMap);
    }

    std::string getMapKey() {
        return static_cast<T*>(this)->getCalcMapKey();
    }
};

class MaxTimeGapCalc : public Calc<MaxTimeGapCalc> {
public:
    void processEntry(std::vector<std::string>& entry, std::map<std::string, std::unordered_map<std::string, long>>& calcInfoMap) {
        long ts = std::stol(entry[0]);
        if (calcInfoMap[entry[1]].count(mapKey) == 0) {
            calcInfoMap[entry[1]][mapKey] = 0;
            calcInfoMap[entry[1]]["maxGap.prevTime"] = ts;
        } else if (ts - calcInfoMap[entry[1]]["maxGap.prevTime"] > calcInfoMap[entry[1]][mapKey]) {
            calcInfoMap[entry[1]][mapKey] = ts - calcInfoMap[entry[1]]["maxGap.prevTime"];
        }
        calcInfoMap[entry[1]]["maxGap.prevTime"] = ts;
    }

    std::string getCalcMapKey() { return mapKey; }

private:
    std::string mapKey {"maxGap"};
};

class VolumeCalc : public Calc<VolumeCalc> {
public:
    void processEntry(std::vector<std::string>& entry, std::map<std::string, std::unordered_map<std::string, long>>& calcInfoMap) {
        long entryVol = std::stol(entry[2]);
        calcInfoMap[entry[1]][mapKey] += entryVol;
    }

    std::string getCalcMapKey() { return mapKey; }

private:
    std::string mapKey {"vol"};
};

class MaxPriceCalc : public Calc<MaxPriceCalc> {
public:
    void processEntry(std::vector<std::string>& entry, std::map<std::string, std::unordered_map<std::string, long>>& calcInfoMap) {
        long entryPrice = std::stol(entry[3]);
        if (entryPrice > calcInfoMap[entry[1]][mapKey]) calcInfoMap[entry[1]][mapKey] = entryPrice;
    }

    std::string getCalcMapKey() { return mapKey; }

private:
    std::string mapKey {"maxPrice"};
};

class WeightedAvgPriceCalc : public Calc<WeightedAvgPriceCalc> {
public:
    void processEntry(std::vector<std::string>& entry, std::map<std::string, std::unordered_map<std::string, long>>& calcInfoMap) {
        long vol = std::stol(entry[2]);
        long price = std::stol(entry[3]);
        calcInfoMap[entry[1]]["wap.numer"] += vol * price;
        calcInfoMap[entry[1]]["wap.denom"] += vol;
        calcInfoMap[entry[1]][mapKey] = calcInfoMap[entry[1]]["wap.numer"] / calcInfoMap[entry[1]]["wap.denom"];
    }

    std::string getCalcMapKey() { return mapKey; }

private:
    std::string mapKey {"weightedAvgPrice"};
};

#endif