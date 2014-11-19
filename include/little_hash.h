#ifndef LITTLE_HASH_TABLE
#define LITTLE_HASH_TABLE

#include "../include/advanced_arrays.h"
#include "../include/extendible_array.h"

template <typename R>
class LittleHashTable{
public:
  int k;
  int n;
  int elms;
  ExtendibleArray<R> *table;

  LittleHashTable(int arr_sz, int in_k);
  ~LittleHashTable();
  int insert(R elm);
  int lookup(R elm);
  int remove(R elm);
};

#include "../src/little_hash.cc"

#endif
