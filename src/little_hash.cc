template <typename R>
LittleHashTable<R>::LittleHashTable(int arr_sz, int in_k){
  table = new ExtendibleArray<R>(arr_sz);
  k = in_k;
  n = arr_sz;
}

template <typename R>
LittleHashTable<R>::~LittleHashTable(){
  table->shrink(table->number_of_elements);
}

template <typename R>
int LittleHashTable<R>::insert(R elm){
  int idx = Hash((long int) elm, k);
  idx = idx%n;
  if ((*table)[idx] != 0) return COLLISION;
  (*table)[idx] = elm;
  return FINE;
}

template <typename R>
int LittleHashTable<R>::lookup(R elm){
  int idx = Hash((long int) elm, k);
  idx = idx%n;
  R content = (*table)[idx];

  if (content == elm) return FINE;
  return FAIL;
}

template <typename R>
int LittleHashTable<R>::remove(R elm){
  int idx = Hash((long int) elm, k);
  idx = idx%n;
  R content = (*table)[idx];
  if (content == elm){
    table[idx] = 0;
    return FINE;
  }
  return FAIL;
}

