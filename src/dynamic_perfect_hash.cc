#ifndef DYNAMIC_PERF_HASH
#define DYNAMIC_PERF_HASH

#include "../include/extendible_array.h"

#define PRIME_SDD 6143

template <typename T>
class DynamicPerfectHash{
private:
  int k;
  int generate_k();

  unsigned int M;

  int rehash_all();

  ExtendibleArray<ExtendibleArray<T>*> table; // Initially implementing for long int
  int Hash(int key,int k);
public:
  DynamicPerfectHash(unsigned int init_sz = 0, 
                        unsigned int sizeof_universe);
  int insert(int id, T elm);
  T& lookup(int id);
  int remove(int id);
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
DynamicPerfectHash<T>::DynamicPerfectHash(unsigned int initial_size /*=0*/,
                                                unsigned int sizeof_universe){
  number_of_elements = 0;
  k = generate_k();
}

template<typename T>
int DynamicPerfectHash<T>::insert(int id, T elm){
  int hash = Hash(id);
  number_of_elements += 1;

}

template<typename T>
int DynamicPerfectHash<T>::Hash(int id){
  return number_of_elements;
}

#endif
