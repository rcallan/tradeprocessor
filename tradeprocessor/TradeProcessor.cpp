#include "StreamOps.h"

int main(int argc, char** argv) {
    char* path = "exampledata/input.csv";

    StreamOps sp(path);

    sp.processStream();
}