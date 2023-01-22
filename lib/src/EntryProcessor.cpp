#include "EntryProcessor.h"
#include <tuple>

template <typename TupleType, int n = std::tuple_size<TupleType>::value>
void tupleProcess(TupleType& t, std::vector<std::string>& entry) {
    if constexpr (n > 1) {
        tupleProcess<TupleType, n - 1>(t, entry);
    }
    std::get<n - 1>(t)->process(entry);
}

template <typename TupleType, int n = std::tuple_size<TupleType>::value>
void tupleWrite(TupleType& t, std::ofstream& os, std::string& k) {
    if constexpr (n > 1) {
        tupleWrite<TupleType, n - 1>(t, os, k);
    }
    std::get<n - 1>(t)->write(os, k);
}

void EntryProcessor::process(std::vector<std::string>& entry) {
    tupleProcess(calcs, entry);
    symbols.insert(entry[1]);
}

void EntryProcessor::write() {
    char path[] = "exampledata/output.csv";

    std::cout << "made it here" << std::endl;

    std::ofstream outputFile(path);

    for (std::string k : symbols) {
        outputFile << k << ",";
        tupleWrite(calcs, outputFile, k);
        outputFile << "\n";
    }

    outputFile.close();

}