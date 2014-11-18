###Advanced arrays
Author: Pablo Estrada < pablo(at)snu ( dot) ac (d0t) kr >
This repo comes from my project to implement the algorithms described in the
following two papers:

 * Brodnik, Andrej, et al. Resizable arrays in optimal time and space. Springer Berlin Heidelberg, 1999.
 * Dietzfelbinger, Martin, et al. "Dynamic perfect hashing: Upper and lower bounds." SIAM Journal on Computing 23.4 (1994): 738-761.
 * Raman, Rajeev, and Satti Srinivasa Rao. "Succinct dynamic dictionaries and trees." Automata, Languages and Programming. Springer Berlin Heidelberg, 2003. 357-368.

This repo implements the resizable arrays described by Brodnik, et al. as a
middle step to implement the succinct dynamic dictionaries described by Raman,
Rajeev and Rao.

####Files
 * extendible_arrays.cc - This file implements the ExtendibleArray class
 * extendible_arrays.h  - This file defines the ExtendibleArray class for other modules
 * dynamic_perfect_hash.cc - This file contains the implementation of the DynamicPerfectHash class
 * succinct_dynamic_dict.cc - This file contains the implementation of the SuccDynamicDict class
