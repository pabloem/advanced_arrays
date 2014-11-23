Advanced arrays
=================
**Author**: Pablo Estrada < pablo(at)snu ( dot) ac (d0t) kr >
***
Filed bugs, feature requests and pull requests are all welcome. Thanks : )

This repository comes from my project to implement the algorithms described in the
following papers:

 * Brodnik, Andrej, et al. Resizable arrays in optimal time and space. Springer Berlin Heidelberg, 1999.
 * Dietzfelbinger, Martin, et al. "Dynamic perfect hashing: Upper and lower bounds." SIAM Journal on Computing 23.4 (1994): 738-761.
 * Raman, Rajeev, and Satti Srinivasa Rao. "Succinct dynamic dictionaries and trees." Automata, Languages and Programming. Springer Berlin Heidelberg, 2003. 357-368.

This repo implements the resizable arrays described by Brodnik, et al. as a
middle step to implement the hash tables described by Dietzfelbinger, et al., and then
it uses the previous structures in the implementation of the succinct dynamic dictionaries
described by Raman, Rajeev and Rao in their paper.

####Files
 * tests/ - The tests directory contains all the tests. The run_tests.py script runs all the regression tests
 * tests/files/ - This directory contains charts, data and code with information about the project
 * extendible_arrays.cc - This file implements the ExtendibleArray class
 * extendible_arrays.h  - This file defines the ExtendibleArray class for other modules
 * little_hash.cc - This file implements the LittleHashTable class
 * little_hash.h  - This file defines the LittleHashTable class
 * dynamic_perfect_hash.cc - This file contains the implementation of the DynamicPerfectHash class
 * dynamic_perfect_hash.h  - This file contains the definition of the DynamicPerfectHash class
 * succinct_dynamic_dict.cc - This file contains the implementation of the SuccDynamicDict class

####Testing
To test this project, one can individually compile and run the C programs contained in the test
directory. All these programs contain explanatory output that should reasonably explain what's
going on.
In a future update, I'll add a more feature-rich testing script implemented in python, that will
run all the tests, and compare their output with the expected results.
