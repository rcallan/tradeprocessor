#ifndef ____LineSplitter__
#define ____LineSplitter__

class LineSplitter {
public:
    static void split(std::string& line, std::string&& delim, std::vector<std::string>& values);
};

#endif