#ifndef ____Calc__
#define ____Calc__

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <fstream>

template <class T>
class Calc {
public:
    void process(std::vector<std::string>& entry) {
        static_cast<T*>(this)->processEntry(entry);
    }
    void write(std::ofstream& os, std::string& k) {
        static_cast<T*>(this)->writeOutput(os, k);
    }
};

class MaxTimeGapCalc : public Calc<MaxTimeGapCalc> {
public:
    void processEntry(std::vector<std::string>& entry) {
        long ts = std::stol(entry[0]);
        if (maxGapMap.count(entry[1]) == 0) {
            maxGapMap[entry[1]] = MaxGapInfo(0, ts);
        } else if (ts - maxGapMap[entry[1]].prevTime > maxGapMap[entry[1]].maxGap) {
            maxGapMap[entry[1]].maxGap = ts - maxGapMap[entry[1]].prevTime;
        }
        maxGapMap[entry[1]].prevTime = ts;
    }

    void writeOutput(std::ofstream& os, std::string& k) {
        os << maxGapMap[k].maxGap << ",";
    }
private:
    struct MaxGapInfo {
        MaxGapInfo() = default;
        MaxGapInfo(long mg, long pt) : maxGap(mg), prevTime(pt) { }
        long maxGap;
        long prevTime;
    };
    std::map<std::string, MaxGapInfo> maxGapMap { };
};

class VolumeCalc : public Calc<VolumeCalc> {
public:
    void processEntry(std::vector<std::string>& entry) {
        long entryVol = std::stol(entry[2]);
        volMap[entry[1]] += entryVol;
    }

    void writeOutput(std::ofstream& os, std::string& k) {
        os << volMap[k] << ",";
    }
private:
    std::map<std::string, long> volMap;
};

class MaxPriceCalc : public Calc<MaxPriceCalc> {
public:
    void processEntry(std::vector<std::string>& entry) {
        long entryPrice = std::stol(entry[3]);
        if (entryPrice > priceMap[entry[1]]) priceMap[entry[1]] = entryPrice;
    }

    void writeOutput(std::ofstream& os, std::string& k) {
        os << priceMap[k] << ",";
    }
private:
    std::map<std::string, long> priceMap;
};

class WeightedAvgPriceCalc : public Calc<WeightedAvgPriceCalc> {
public:
    void processEntry(std::vector<std::string>& entry) {
        long vol = std::stol(entry[2]);
        long price = std::stol(entry[3]);
        wapMap[entry[1]].numer += vol * price;
        wapMap[entry[1]].denom += vol;
        wapMap[entry[1]].wap = wapMap[entry[1]].numer / wapMap[entry[1]].denom;
    }

    void writeOutput(std::ofstream& os, std::string& k) {
        os << wapMap[k].wap << ",";
    }
private:
    struct WapInfo {
        WapInfo() = default;
        WapInfo(long n, long d) : numer(n), denom(d) { }
        long numer;
        long denom;
        long wap;
    };
    std::map<std::string, WapInfo> wapMap;
};

#endif