# cpp_protein_encoders

To use them as input to an ML model, protein sequences have to
be encoded (e.g. one-hot encoding, etc.) It's *very* easy to write
Python code to do this, but if you do this often enough, at some point
you'll realize you have multiple redundant code blocks in different
projects that all do the same thing. For this reason, it's convenient
to have a single simple plugin tool to do basic protein encoding wherever
you need it. `cpp_protein_encoders` provides a simple,
fast and flexible tool for common encoding schemes (I'll add
more over time if I find any others I am using frequently -- please
feel free to suggest any that you would find useful.)

Currently supported schemes include:

- One-hot encoding with either a 2d or 3d array as output, using either the
basic 20 amino acid alphabet, or the basic alphabet plus gaps, or an extended
alphabet including unusual symbols (B, J, O, U, X, Z).
- Integer encoding, using either the basic 20 amino acid alphabet, or the basic alphabet plus gaps, or an extended
alphabet including unusual symbols (B, J, O, U, X, Z). Integer encoding is
useful for LightGBM (gradient boosted trees) and some clustering schemes.
- Substitution matrix encoding using a 21 letter alphabet (standard AAs plus
gaps) with various percent homologies and two encoding schemes supported.

`cpp_protein_encoders` encodes sequences as numpy arrays. Why not as
PyTorch / Jax / Tensorflow? There are two reasons for this. First, numpy is
much more universal. A numpy array is easily converted to e.g. a PyTorch
array in-place with negligible overhead, and given numpy's popularity,
all the other popular frameworks can convert numpy arrays to their
own format. Moreover, you may need to use encoded sequences as input to
a library like LightGBM, XGBoost or xGPR that uses numpy arrays as input.

Second, by using numpy we ensure this package has only a single
dependency -- numpy -- which is *relatively* lightweight (the same cannot
be said for PyTorch or Tensorflow).

Since this package is (at this time) small and simple,
documentation is relatively brief and is below.

### Performance

Sequence encoding is almost never the bottleneck in ML or statistical
analysis (if it is, you're doing something unusual). Still, FWIW, this
package gives roughly an order of magnitude speed improvement over a
naive pure Python approach (more if you are processing numerous
minibatches).

### Installation
```
pip install cpp_protein_encoders
```

### Usage

```
from cpp_protein_encoders import OneHotProteinEncoder, IntegerProteinEncoder
from cpp_protein_encoders import SubstitutionMatrixEncoder

# Note that all characters are expected to be uppercase.

sequences = ['AAAGGGYYY', 'CCCTTTAAA', 'GGGTTTFF-']


# When creating a OneHotProteinEncoder or an IntegerProteinEncoder, we
# can use either the 'standard' alphabet (basic 20 AAs), the 'gapped'
# alphabet (basic 20 AAs + gaps), or the 'expanded' alphabet (gaps +
# unusual AAs, see above). If we pass sequences that contain unexpected
# characters, an exception will be raised.

encoder1 = OneHotProteinEncoder(alphabet = 'gapped')
encoder2 = IntegerProteinEncoder(alphabet = 'gapped')

# For substitution matrices, we can select a homology value to indicate
# which substitution matrix to use (90% homology, 85%, and so on).
# Current options are '95', '90', '85', '75', '62'.
# We can also set 'use_standardized_mat' to be True or False. If True,
# each AA is encoded using the corresponding row of a scaled Cholesky
# decomposition of a distance matrix built using the substitution matrix.
# This ensures that the Euclidean distance between any two representations
# is equal to the distance between them as determined using the substitution
# matrix. This can work well for kernel machines and some NNs. Alternatively,
# we can set 'use_standardized_mat' to be False, in which case the AAs are
# encoded as the corresponding row of the substitution matrix. This is
# unlikely to work well in kernel machines but may work well for some NNs.

encoder3 = SubstitutionMatrixEncoder(homology = '90', use_standardized_mat = True)

# For one-hot and substitution matrices, when encoding, you can specify 
# 'all_same_length = True' (or False) and 'flatten_output_array = True'
# (or False). If all_same_length, sequences are checked to make sure they
# are all the same length, and if they are not, an exception is raised.
# Otherwise sequences are zero-padded to be the same length. If
# flatten_output_array, the array that is returned is 2d and is of
# shape N x (M * A) where N is number of sequences, M is largest number
# of AAs and A is the alphabet size. Otherwise, output array is of size
# N x M x A and is 3d.
#
# For integer encoding, output arrays are always 2d, but you can still
# set the 'all_same_length' flag as desired.

first_set = encoder1.encode(sequences, all_same_length = False,
                           flatten_output_array = False)
second_set = encoder1.encode(sequences, all_same_length = False)
third_set = encoder1.encode(sequences, all_same_length = False,
                           flatten_output_array = False)
```
