#ifndef LITTLE_HASH_TABLE
#define LITTLE_HASH_TABLE

#include "../include/advanced_arrays.h"
#include "../include/extendible_array.h"

template <typename R>
class LittleHashTable{
private:
  int k;
  int n;
  int elms;
  int reshuffle(R ins);

  ExtendibleArray<R> *table;

public:
  LittleHashTable(int arr_sz, int in_k);
  ~LittleHashTable();
  int cleanup();
  int insert(R elm, bool force=false);
  int lookup(R elm);
  int remove(R elm);
  int set_k(int in_k);
  int len();
  int elems_to_buffer(R* buffer);
};

#include "../src/little_hash.cc"

#endif
