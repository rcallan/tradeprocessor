#include "Calc.h"

class CalcInfoWriter {
public:
    CalcInfoWriter() = delete;
    CalcInfoWriter(char* path, std::map<std::string, std::unordered_map<std::string, long>>& cim, std::vector<std::string> mks) 
        : writePath(path), calcInfoMap(cim), mapKeys(mks) { }

    void write() {
        std::ofstream outputFile(writePath);

        for (const auto& [k, v] : calcInfoMap) {
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
    char* writePath;
    std::map<std::string, std::unordered_map<std::string, long>>& calcInfoMap;
    std::vector<std::string> mapKeys;
};