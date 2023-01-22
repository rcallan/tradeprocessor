#include "StreamProcessor.h"
#include <iostream>

void StreamProcessor::process() {
    std::ifstream file(this->readPath);
    std::string value;

    while (file.good()) {
        std::getline(file, value, '\n');

        if (value.find(',') != std::string::npos) {
            std::vector<std::string> values;
            LineSplitter::split(value, ",", values);
            this->ep->process(values);
        } else {

        }
    }
}

void StreamProcessor::write() {
    this->ep->write();
}