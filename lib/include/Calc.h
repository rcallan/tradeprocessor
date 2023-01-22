#ifndef ____Calc__
#define ____Calc__

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iostream>

template <class T>
class Calc {
public:
    void process(std::vector<std::string>& entry) {
        static_cast<T*>(this)->processEntry(entry);
    }
    void write(char* path) {
        static_cast<T*>(this)->writeOutput(path);
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
    // probably would like to change this so it accepts a ref to an ofstream and only writes its own piece to it and does not close it
    void writeOutput(char* path) {
        std::ofstream outputFile(path);

        for (const auto& [k, v] : maxGapMap) {
            outputFile << k;
            outputFile << ",";
            outputFile << v.maxGap;
            outputFile << "\n";
        }
        outputFile.close();
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

    void writeOutput(char* path) {
        std::ofstream outputFile(path);

        for (const auto& [k, v] : volMap) {
            outputFile << k;
            outputFile << ",";
            outputFile << v;
            outputFile << "\n";
        }
        outputFile.close();
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

    void writeOutput(char* path) {
        std::ofstream outputFile(path);

        for (const auto& [k, v] : priceMap) {
            outputFile << k;
            outputFile << ",";
            outputFile << v;
            outputFile << "\n";
        }
        outputFile.close();
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

    void writeOutput(char* path) {
        std::ofstream outputFile(path);

        for (const auto& [k, v] : wapMap) {
            outputFile << k;
            outputFile << ",";
            outputFile << v.wap;
            outputFile << "\n";
        }
        outputFile.close();
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