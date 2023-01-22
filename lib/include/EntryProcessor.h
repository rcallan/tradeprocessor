#ifndef ____EntryProcessor__
#define ____EntryProcessor__

#include <vector>
#include "Calc.h"

class EntryProcessor {
public:
    void process();
private:
    std::vector<Calc> calcs;
};

#endif