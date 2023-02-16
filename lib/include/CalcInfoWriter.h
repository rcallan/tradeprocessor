#ifndef ____CalcInfoWriter__
#define ____CalcInfoWriter__

#include "Calc.h"

class CalcInfoWriter {
public:
    CalcInfoWriter() = delete;
    CalcInfoWriter(std::string& path, std::unordered_map<std::string, std::unordered_map<std::string, long>>& cim, std::vector<std::string>&& mks) 
        : writePath(path), calcInfoMap(cim), mapKeys(mks) { }

    void write() const {
        std::ofstream outputFile(writePath);

        std::map<std::string, std::unordered_map<std::string, long>> sortedMap(std::begin(calcInfoMap), std::end(calcInfoMap));

        for (const auto& [k, v] : sortedMap) {
            outputFile << k << ",";
            for (int i = 0; i < mapKeys.size() - 1; i++) {
                outputFile << calcInfoMap[k][mapKeys[i]] << ",";
            }
            outputFile << calcInfoMap[k][mapKeys[mapKeys.size() - 1]];
            outputFile << "\n";
        }

        outputFile.close();
    }

private:
    std::string writePath;
    std::unordered_map<std::string, std::unordered_map<std::string, long>>& calcInfoMap;
    std::vector<std::string> mapKeys;
};

#endif