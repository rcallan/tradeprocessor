#ifndef ____StreamProcessor__
#define ____StreamProcessor__

#include "EntryProcessor.h"
#include "LineSplitter.h"
#include <vector>
#include <string>
#include <fstream>

class StreamProcessor {
public:
    StreamProcessor() = default;
    StreamProcessor(char* rp) : readPath(rp) { }
    StreamProcessor(char* rp, char* wp) : readPath(rp), writePath(wp) { }
    void process();
    void write();
    void setEntryProcessor(EntryProcessor* _ep) { ep = _ep; };
private:
    char* readPath;
    char* writePath;
    EntryProcessor* ep;
};

#endif