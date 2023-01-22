#ifndef ____StreamOps__
#define ____StreamOps__

class StreamOps {
public:
    StreamOps() = default;
    StreamOps(char* rp) : readPath(rp) { }
    StreamOps(char* rp, char* wp) : readPath(rp), writePath(wp) { }
    void processStream();
    void write();
private:
    char* readPath;
    char* writePath;
};

#endif