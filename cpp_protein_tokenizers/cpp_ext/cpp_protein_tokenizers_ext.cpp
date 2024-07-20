/* Contains the wrapper code for the C++ extension for alignment
 * calculations.
 */

#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/vector.h>    // Enables automatic type conversion for C++, python containers
#include <nanobind/stl/string.h>    // Enables automatic type conversion for C++, python containers
#include <nanobind/stl/tuple.h>
#include <string>
#include <vector>
#include "utilities.h"
#include "basic_tokenizers.h"
#include "subsmat_tokenizer.h"

namespace nb = nanobind;

NB_MODULE(cpp_protein_tokenizers_ext, m){
    m.def("validate_sequence_list", &validate_sequence_list);
    m.def("onehot_flat_encode_list", &onehot_flat_encode_list,
            nb::arg("sequenceList"), nb::arg("outputArray").noconvert(),
            nb::arg("expandedSymbolSet"), nb::arg("addGaps"));
    m.def("onehot_3d_encode_list", &onehot_3d_encode_list,
            nb::arg("sequenceList"), nb::arg("outputArray").noconvert(),
            nb::arg("expandedSymbolSet"), nb::arg("addGaps"));
    m.def("integer_encode_list", &integer_encode_list,
            nb::arg("sequenceList"), nb::arg("outputArray").noconvert(),
            nb::arg("expandedSymbolSet"), nb::arg("addGaps"));

    m.def("subsmat_flat_encode_list", &subsmat_flat_encode_list,
            nb::arg("sequenceList"), nb::arg("outputArray").noconvert(),
            nb::arg("aaTokens").noconvert());
    m.def("subsmat_3d_encode_list", &subsmat_3d_encode_list,
            nb::arg("sequenceList"), nb::arg("outputArray").noconvert(),
            nb::arg("aaTokens").noconvert());
}
