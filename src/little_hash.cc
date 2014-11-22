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


#define MAX_RESHUFLES 50
template <typename R>
int LittleHashTable<R>::reshuffle(R ins){
  R* el_lst = (R*) malloc(sizeof(R)*(elms+1));
  int el_idx = 0;

  for(int i = 0; i < n; i++){
    if( (*table)[i] != 0 ){
      el_lst[el_idx] = (*table)[i];
      el_idx += 1;
    }
  }
  el_lst[el_idx] = ins;
  el_idx += 1;

  int original_k = k;
  int res = 0;
  int res_count = 0;
  while(true){
    table->setzeros();
    k = generate_k();
    elms = 0;
    if ( res_count == MAX_RESHUFLES ){
      /* Result: COLLISION
         If we have tried to reshuffle too many times, we settle to add only
         the previous elements, and error out.
       */
      k = original_k;
      el_idx -= 1;
    }
    for ( int i = 0; i < el_idx; i++){
      res = insert(el_lst[i],false);
      if ( res == COLLISION ){
        break;
      }
    }
    if ( res_count == MAX_RESHUFLES ) break; // Result: COLLISION

    res_count += 1;
    if( res == FINE ){
      free(el_lst);
      return FINE;
    }
  }

  fprintf(stderr,"MAXIMUM RESHUFLES\n");
  free(el_lst);
  return COLLISION;
}

template <typename R>
int LittleHashTable<R>::insert(R elm, bool force){
  int idx = Hash((long int) elm, k);
  idx = idx%n;
  if ((*table)[idx] != 0 && (*table)[idx] != elm){
    if (force){
      return reshuffle(elm);
    }
    return COLLISION;
  }
  if((*table)[idx] != elm){ // We are really inserting a new element
    elms += 1;
  }
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
    elms -= 1;
    table[idx] = 0;
    return FINE;
  }
  return FAIL;
}

template <typename R>
int LittleHashTable<R>::set_k(int in_k){
  if (elms > 0) return FAIL;
  k = in_k;
  return FINE;
}
