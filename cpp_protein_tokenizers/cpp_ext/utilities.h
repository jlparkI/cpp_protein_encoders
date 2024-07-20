#ifndef UTILITIES_HEADER_H
#define UTILITIES_HEADER_H

#include <string>
#include <vector>
#include <tuple>
#include <nanobind/stl/vector.h>    // Enables automatic type conversion for C++, python containers

std::tuple<int, int> validate_sequence_list(std::vector<std::string> sequenceList,
        bool expandedSymbolSet, bool addGaps, bool allSameLength);


#endif
