/* Utilities for sequence processing. */
#include "utilities.h"

// Codes for sequence validation.
#define VALID_SEQUENCE 1
#define INVALID_SEQUENCE 0


// Validates a list of sequences. If allSameLength, the sequences are required to
// all be the same length and that length is recorded; otherwise, the longest length
// is recorded. If expandedSymbolSet, amino acid symbols for ambiguous or unusual
// aas (B, J, O, U, X, Z, -) are allowed. If expandedSymbolSet is false but addGaps
// is true, gaps "-" are allowed but other unusual symbols are not. Only uppercase
// letters are allowed at this time.
std::tuple<int, int> validate_sequence_list(std::vector<std::string> sequenceList,
            bool expandedSymbolSet, bool addGaps, bool allSameLength){
    bool validQuery = true;
    size_t maxLength = 0;

    if (sequenceList.size() == 0)
        return std::tuple<int, int>{0, INVALID_SEQUENCE};


    if (expandedSymbolSet){
        for (auto & sequence : sequenceList) {
            for (char & c : sequence){
                switch (c){
                    case 'A':
                    case 'B':
                    case 'C':
                    case 'D':
                    case 'E':
                    case 'F':
                    case 'G':
                    case 'H':
                    case 'I':
                    case 'J':
                    case 'K':
                    case 'L':
                    case 'M':
                    case 'N':
                    case 'O':
                    case 'P':
                    case 'Q':
                    case 'R':
                    case 'S':
                    case 'T':
                    case 'U':
                    case 'V':
                    case 'W':
                    case 'X':
                    case 'Y':
                    case 'Z':
                    case '-':
                        break;
            
                    default:
                        validQuery = false;
                        break;

                }
            }
            if (allSameLength){
                if (sequence.length() != maxLength){
                    if (maxLength > 0)
                        return std::tuple<int, int>{0, INVALID_SEQUENCE};
                    else
                        maxLength = sequence.length();
                }
            }
            else if (sequence.length() > maxLength)
                maxLength = sequence.length();

            if (!validQuery)
                break;
        }
    }

    else if (addGaps){
        for (auto & sequence : sequenceList) {
            for (char & c : sequence){
                switch (c){
                    case 'A':
                    case 'C':
                    case 'D':
                    case 'E':
                    case 'F':
                    case 'G':
                    case 'H':
                    case 'I':
                    case 'K':
                    case 'L':
                    case 'M':
                    case 'N':
                    case 'P':
                    case 'Q':
                    case 'R':
                    case 'S':
                    case 'T':
                    case 'V':
                    case 'W':
                    case 'Y':
                    case '-':
                        break;
            
                    default:
                        validQuery = false;
                        break;

                }
            }
            if (allSameLength){
                if (sequence.length() != maxLength){
                    if (maxLength > 0)
                        return std::tuple<int, int>{0, INVALID_SEQUENCE};
                    else
                        maxLength = sequence.length();
                }
            }
            else if (sequence.length() > maxLength)
                maxLength = sequence.length();

            if (!validQuery)
                break;
        }
    }


    else{
        for (auto & sequence : sequenceList) {
            for (char & c : sequence){
                switch (c){
                    case 'A':
                    case 'C':
                    case 'D':
                    case 'E':
                    case 'F':
                    case 'G':
                    case 'H':
                    case 'I':
                    case 'K':
                    case 'L':
                    case 'M':
                    case 'N':
                    case 'P':
                    case 'Q':
                    case 'R':
                    case 'S':
                    case 'T':
                    case 'V':
                    case 'W':
                    case 'Y':
                        break;
            
                    default:
                        validQuery = false;
                        break;

                }
            }
            if (allSameLength){
                if (sequence.length() != maxLength){
                    if (maxLength > 0)
                        return std::tuple<int, int>{0, INVALID_SEQUENCE};
                    else
                        maxLength = sequence.length();
                }
            }
            else if (sequence.length() > maxLength)
                maxLength = sequence.length();

            if (!validQuery)
                break;
        }
    }

    if (!validQuery)
        return std::tuple<int, int>{0, INVALID_SEQUENCE};

    int maxLengthAsInt = maxLength;

    return std::tuple<int, int>{maxLengthAsInt, VALID_SEQUENCE};
}
