#ifndef DYNAMIC_PERF_HASH
#define DYNAMIC_PERF_HASH

#include "../include/advanced_arrays.h"
#include "../include/extendible_array.h"

#define c 1
#define sM_factor 2

template <typename T>
class DynamicPerfectHash{
private:
  int k;

  long unsigned int M;
  long unsigned int count;
  int sM;

  int rehash_all();
  void **table;
  //LittleHashTable<T>* table; // Initially implementing for long int
public:
  DynamicPerfectHash(unsigned int init_sz = 0, 
                        unsigned int sizeof_universe);
  int insert(T elm, bool force=false);
  int lookup(T elm);
  int remove(T elm);
};

template<typename T>
int DynamicPerfectHash<T>::rehash_all(){
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
  sM = M*sM_facto;
  //table.grow(sM-table.number_of_elements);
  if ( table == NULL ){
    table = malloc(sizeof(void*)*sM);
  }
  else {
    table = realloc(table,sizeof(void*)*sM);
  }
}

template<typename T>
DynamicPerfectHash<T>::DynamicPerfectHash(unsigned int initial_size /*=0*/,
                                                unsigned int sizeof_universe){
  count = 0;
  rehash_all();
}

template<typename T>
int DynamicPerfectHash<T>::insert(T elm, bool force){
  count += 1;
  if ( count > M ){
    rehash_all(); /* TODO insert element */
    return FINE;
  }
  int hash = Hash((long int)elm,k)%sM;
  LittleHashTable<T> *lht = (LittleHashTable<T> *) *(table+hash);
  return lht->insert(elm,force);
}

template<typename T>
int DynamicPerfectHash<T>::lookup(T elm){
  int hash = Hash((long int) elm,k)%sM;
  count -= 1;
  LittleHashTable<T> *lht = (LittleHashTable<T> *) *(table+hash);

  return lht->lookup(elm);
}

template<typename T>
int DynamicPerfectHash<T>::remove(T elm){
  int hash = Hash((long int) elm,k)%sM;
  LittleHashTable<T> *lht = (LittleHashTable<T> *) *(table+hash);

  return lht->remove(elm);
}

#endif
