#include "LineSplitter.h"
#include <algorithm>

void LineSplitter::split(std::string& line, std::string&& delim, std::vector<std::string>& values) {
    size_t pos = 0;
    while ((pos = line.find(delim, 0)) != std::string::npos) {
        values.emplace_back(line.substr(0, pos));
        line = line.substr(pos + 1);
    }

    if (!line.empty()) {
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        values.push_back(std::move(line));
    }
}