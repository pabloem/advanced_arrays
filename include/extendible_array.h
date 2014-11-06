/*
 */
#ifndef EXTENDIBLE_ARRAY
#define EXTENDIBLE_ARRAY

#define FINE 0
#define FAIL_TO_ALLOC 1
#define BAD_INPUT 2

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
  int memory_footprint();
  void print();
  void print_to_f(FILE* f);
  int grow(int n);
  int shrink(int n);
  T& operator[](unsigned int idx);
};

#include "../src/extendible_array.cc"

#endif
