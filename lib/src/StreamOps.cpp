#include "StreamOps.h"
#include "LineSplitter.h"
#include <vector>
#include <string>

void StreamOps::processStream() {
    std::ifstream file (this->readPath);
    std::string value;

    while (file.good()) {
        std::getline(file, value, '\n');

        if (value.find(',') != std::string::npos) {
            std::vector<std::string> values;
            LineSplitter::split(value, ",", values);
        } else {

        }
    }
}

void StreamOps::write() {
    std::ofstream output_file (this->writePath);

    int numRows = 5;
    int numColumns = 5;

    for (unsigned i = 0; i < numRows; ++i) {
    for (unsigned j = 0; j < numColumns; ++j) {
        output_file << 5;
        if (j < numColumns - 1) {
        output_file << ",";
        }
    }
    if (i < numRows - 1) {
        output_file << "\n";
    }
    }
    output_file.close();
}