#ifndef DYNAMIC_PERF_HASH
#define DYNAMIC_PERF_HASH

#include "../include/extendible_array.h"

#define PRIME_SDD 6143
#define c 1
#define sM_factor 2

#define MAX(X,Y) (((X)>(Y)) ? (X):(Y))

int Hash(long int key, int k){
  return (key*k)%PRIME_SDD;
}

template <typename T>
class LittleHashTable{
public:
  int k;
  int n;
  int elms;
  ExtendibleArray<T> table;

  LittleHashTable(int arr_sz);
};

template <typename T>
class DynamicPerfectHash{
private:
  int k;
  int generate_k();

  long unsigned int M;
  long unsigned int count;
  int sM;

  int rehash_all();
  ExtendibleArray<LittleHashTable<T>*> table; // Initially implementing for long int
  //  int Hash(int key);
public:
  DynamicPerfectHash(unsigned int init_sz = 0, 
                        unsigned int sizeof_universe);
  int insert(T elm);
  int lookup(T elm);
  int remove(T elm);
};

/*
  Function generate_k()
  Returns: This function returns the value of K such that 0<=K<=PRIME_SDD.
  K is calculated at random, but in this case it uses modulo operator over
  the rand() function. This makes elements at the beginning more likely.

  === TODO: A more robust implementation of generate_k() ===
 */
#include <cstdlib>
template<typename T>
int DynamicPerfectHash<T>::generate_k(){
  return rand() % PRIME_SDD;
}

template<typename T>
DynamicPerfectHash<T>::rehash_all(){
  T* elms = (T*) malloc(count*sizeof(T));
  /* Put all elements in elms array. */
  for (int i = 0; i < count; i ++){
    T* each_el = get_next_elm();
    memcpy(each_el,elms+i,sizeof(T));
  }

  /*
    TODO: Clean up all the old structures - 
    Specifically, the LittleHashTable objects.
   */

  M = (1+c)*MAX(4,count);
  k = generate_k();
  sM = M*sM_factor;
  table.grow(sM-table.number_of_elements);
}

template<typename T>
DynamicPerfectHash<T>::DynamicPerfectHash(unsigned int initial_size /*=0*/,
                                                unsigned int sizeof_universe){
  count = 0;
  rehash_all();
}

template<typename T>
int DynamicPerfectHash<T>::insert(T elm){
  int hash = Hash((long int)elm,k)%sM;
  count += 1;
  if ( count > M ){
    rehash_all(); /* TODO insert element */
    return FINE;
  }
}

#endif
