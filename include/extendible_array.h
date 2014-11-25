#ifndef EXTENDIBLE_ARRAY
#define EXTENDIBLE_ARRAY

/* ExtendibleArray class
   The class provides O(1) amortized access to an array, as well as 
   O(sqrt(n)) extra space, as opposed to the standard implementation
   of Vector that has O(n) extra space.
   This is achieved by constructing a series of arrays indexed by a
   single index array, as follows:

   INDEX BLOCK: |_______|
   BLOCKS:       |->|_|      (Len: 1)
                 |->|__|     (Len: 2)
                 |->|___|    (Len: 3)
                ...........
                 |->|__________| (Len: sqrt(n))

 */

#include "advanced_arrays.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

template<typename T>
class ExtendibleArray{
private:
  void** index_block;
  unsigned int index_block_size;
  unsigned int index_block_used_sp;
  unsigned int capacity();

  int extend_index_block();
public:
  unsigned int number_of_elements;
  ExtendibleArray(unsigned int n = 0);
  ~ExtendibleArray();
  int memory_footprint();
  void print();
  void print_to_f(FILE* f);
  int grow(int n);
  int shrink(int n);
  T& operator[](unsigned int idx);
  int setzeros();

  int push(T elm);
  T pop();
};

#include "../src/extendible_array.cc"

#endif
