#ifndef ____LineSplitter__
#define ____LineSplitter__

#include <string>
#include <vector>

class LineSplitter {
public:
    static void split(std::string& line, std::string&& delim, std::vector<std::string>& values);
};

#endif