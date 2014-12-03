#ifndef SUCCINCT_DYNAMIC_DICT
#define SUCCINCT_DYNAMIC_DICT

#include "../include/extendible_array.h"
#include "../include/dynamic_perfect_hash.h"

#define LEMMA3 w*w*w*w
#define BUCKET_ARRAY w*w*w*w*w

/* IN AN INITIAL VERSION, I WILL DESIGN THIS FOR AN INTEGER DATA 
   TYPE, AND EVENTUALLY WILL GENERALIZE IT TO MORE COMPLEX DATA
   TYPES */

template <typename T>
class SuccDynamicDict{
private:
  long unsigned int count;  // Elements inserted so far
  long unsigned int n;      // Elements that we are prepared to receive
  ExtendibleArray<void*> *hashes;
  unsigned int w;
  int logW;
  unsigned int real_w;

  int shift;

  int rehash_all(unsigned long int new_n);
  int build_bucket_arr(ExtendibleArray<T> *elms);
  int copy_elements(ExtendibleArray<T> *elm_lst, T prefix);

public:
  SuccDynamicDict(unsigned long int expected_number_of_elms = 0, int word_size = 64);
  int insert(T elm, bool force=false);
  int lookup(T elm);
  int remove(T elm);
  int cleanup();

};

#include "../src/succinct_dynamic_dict.cc"

#endif
