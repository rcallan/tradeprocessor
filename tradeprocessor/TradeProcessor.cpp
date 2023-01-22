#include "StreamProcessor.h"
#include <iostream>

int main(int argc, char** argv) {
    char path[] = "exampledata/input.csv";

    StreamProcessor sp(path);

    EntryProcessor* ep = new EntryProcessor();

    // probably could set calcs here

    sp.setEntryProcessor(ep);

    sp.process();
    sp.write();
}