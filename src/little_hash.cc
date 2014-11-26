template <typename R>
LittleHashTable<R>::LittleHashTable(int arr_sz, int in_k){
  table = new ExtendibleArray<R>(arr_sz);
  k = in_k;
  n = arr_sz;
}

template <typename R>
LittleHashTable<R>::~LittleHashTable(){
  table->shrink(table->number_of_elements);
  delete table;
}

template <typename R>
int LittleHashTable<R>::cleanup(){
  /*
    Resets all elements in the underlying array to zero. */
  table->setzeros();
  return FINE;
}

template <typename R>
int LittleHashTable<R>::resize(){
  /*
    This function increases the size of the table array, and reinserts 
    all elements from the elms array. */
  int new_size = 2*n*(n-1);
  printf("RESIZING - SZ:%d NWS: %d\n",n,new_size);

  int ea_szdf = new_size - table->number_of_elements;
  table->grow(ea_szdf);
  table->setzeros(); // This step might not be necessary
  k = generate_k();
  n = new_size;

  return FINE;
}

template <typename R>
int LittleHashTable<R>::elems_to_buffer(ExtendibleArray<R>* buffer){
  /* Copies all the elements contained in the hash table to a contiguous
     buffer in memory. */
  int el_idx = 0;
  for(int i = 0; i < n; i++){
    if( (*table)[i] != 0 ){
      buffer->push((*table)[i]);
      el_idx += 1;
    }
  }
  return el_idx;
}

#define MAX_RESHUFLES 50
#define RESIZE_ROUND MAX_RESHUFLES-1
template <typename R>
int LittleHashTable<R>::reshuffle(R ins){
  /* Input: The new element to insert
     Returns: 
       FINE if all elements were successfully inserted
       COLLISION if after attempting MAX_RESHUFLES times, we were
                 unable to insert all elements without collisions.

     When we attempt to insert a new element, and we find a collision,
     we attempt to fix the issue by copying all the elements to a buffer,
     updating to a new K, and retrying the insertion of all the elements */

  ExtendibleArray<R>* el_lst = new ExtendibleArray<R>();
  int el_idx = 0;

  /* Now we copy the elements stored in the table to the el_lst buffer
     to re-insert them later on */
  el_idx = elems_to_buffer(el_lst);

  el_lst->push(ins);

  int original_k = k;
  int res = 0;
  int res_count = 0;
  bool resized = false;

  while(true){
    table->setzeros();
    k = generate_k();
    elms = 0;
    if ( res_count == RESIZE_ROUND && !resized){
      /*
         If we have tried to reshuffle and failed, then we go ahead and
         resize the table. This should fix problems.
       */
      resize();
      res_count = 0;
      resized = true;
    }
    if(res_count == MAX_RESHUFLES){
      k = original_k;
      el_lst->pop();
    }
    for ( int i = 0; i < el_lst->number_of_elements; i++){
      res = insert((*el_lst)[i],false);
      if ( res == COLLISION ){
        break;
      }
    }

    // Result: COLLISION
    if ( res_count == MAX_RESHUFLES && res == COLLISION) break;
    
    res_count += 1;
    if( res == FINE ){
      delete el_lst;
      return FINE;
    }
  }

  fprintf(stderr,"MAXIMUM RESHUFLES\n");
  delete el_lst;
  return COLLISION;
}

template <typename R>
int LittleHashTable<R>::len(){
  /* Returns the length of the underlying array */
  return n;
}

template <typename R>
int LittleHashTable<R>::insert(R elm, bool force){
  /* Input: elm - The element that we want to insert
            force - Indicates whether to force insertion, or error out
                    after the first attempt.

     Returns:
       FINE - If the element was successfuly inserted
       COLLISION - If it failed to insert the element due to a collision

     Inserts the input element to the hash table. If the force option is
     activated, then a series of reshuffles will be attempted, in order to
     fit all the elements in the table.
   */
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
  /* Input: elm - The element to look up
     Returns:
       FINE - If the element was previously inserted to the hash table
       FAIL - Otherwise
   */
  int idx = Hash((long int) elm, k);
  idx = idx%n;
  R content = (*table)[idx];

  if (content == elm) return FINE;
  return FAIL;
}

template <typename R>
int LittleHashTable<R>::remove(R elm){
  /* Input: elm - The element to remove from the hash table
     Returns:
       FINE - If the element was previously inserted to the hash table,
              and succesfully removed.
       FAIL - Otherwise
   */
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
