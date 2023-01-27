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
        auto& temp = calcInfoMap[entry[1]];
        if (temp.count(mapKey) == 0) {
            temp[mapKey] = 0;
        } else if (ts - temp["maxGap.prevTime"] > temp[mapKey]) {
            temp[mapKey] = ts - temp["maxGap.prevTime"];
        }
        temp["maxGap.prevTime"] = ts;
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
        auto& temp = calcInfoMap[entry[1]][mapKey];
        if (entryPrice > temp) temp = entryPrice;
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
        auto& temp = calcInfoMap[entry[1]];
        temp["wap.numer"] += vol * price;
        temp["wap.denom"] += vol;
        temp[mapKey] = temp["wap.numer"] / temp["wap.denom"];
    }

    std::string getCalcMapKey() { return mapKey; }

private:
    std::string mapKey {"weightedAvgPrice"};
};

#endif