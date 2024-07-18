#ifndef UTILITIES_HEADER_H
#define UTILITIES_HEADER_H

#include <string>
#include <vector>
#include <tuple>

std::tuple<int, int> validate_sequence_list(std::vector<std::string> sequenceList,
        bool expandedSymbolSet, bool addGaps, bool allSameLength);


#endif
