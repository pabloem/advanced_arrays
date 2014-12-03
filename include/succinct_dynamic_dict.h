#ifndef SUCCINCT_DYNAMIC_DICT
#define SUCCINCT_DYNAMIC_DICT

#include "../include/extendible_array.h"
#include "../include/dynamic_perfect_hash.h"

#define W 32
#define logW 5
#define LEMMA3 W*W*W*W
#define BUCKET_ARRAY W*W*W*W*W

/* IN AN INITIAL VERSION, I WILL DESIGN THIS FOR AN INTEGER DATA 
   TYPE, AND EVENTUALLY WILL GENERALIZE IT TO MORE COMPLEX DATA
   TYPES */
#define T int

class SuccDynamicDict{
private:
  long unsigned int count;  // Elements inserted so far
  long unsigned int n;      // Elements that we are prepared to receive
  ExtendibleArray<void*> *hashes;
  unsigned int w;

  int shift;

  int rehash_all();
  int build_bucket_arr(ExtendibleArray<T> *elms);

public:
  SuccDynamicDict(int expected_number_of_elms = 0);
  int insert(T elm, bool force=false);
  int lookup(T elm);
  int remove(T elm);
  int cleanup();

};

#include "../src/succinct_dynamic_dict.cc"

#endif
