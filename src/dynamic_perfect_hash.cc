template <typename T>
int DynamicPerfectHash<T>::copy_elements(T* el_lst, T ins){
  int el_idx = 0;
  for(int i = 0; i < sM; i++){
    LittleHashTable<T> *lht = (LittleHashTable<T> *) table[i];
    int el_num = lht->elems_to_buffer(el_lst+el_idx);
    el_idx += el_num;
  }
  el_lst[el_idx] = ins;
  return FINE;
}

template <typename T>
int DynamicPerfectHash<T>::cleanup(){
  for ( int i = 0; i < sM; i ++){
    LittleHashTable<T> *lht = (LittleHashTable<T> *) table[i];
    lht->cleanup();
  }
  return FINE;
}

template<typename T>
int DynamicPerfectHash<T>::rehash_all(T ins, bool add){
  T* elms = (T*) malloc((count+1)*sizeof(T));
  /* Put all elements in elms array. */
  copy_elements(elms,ins);

  /*
    Clean up all the old structures - 
    Specifically, the LittleHashTable objects. */
  cleanup();

  /*
    Now we go and calculate the new numbers to resize the hash table. 
    We keep the previous ones, to add the new structures. */
  int pre_sM = sM;
  int tot_count = count+(int)add;

  count = 0;
  M = (int) (1+c)*MAX(4,tot_count);
  k = generate_k();
  sM = M*sM_factor;

  /* 
     Allocate - or reallocate the big hash table, containing the Little ones */
  if ( table == NULL ){
    table = (void **) malloc(sizeof(void*)*sM);
    memset(table,0,sizeof(void*)*sM);
  }
  else {
    table = (void **) realloc(table,sizeof(void*)*sM);
    memset(table+pre_sM,0,sizeof(void*)*sM);
  }

  for(int i = 0; i < tot_count; i ++){
    int res = insert(elms[i],true);
    /* We are never supposed to experience a collision here */
    assert( res != COLLISION );
  }
  return FINE;
}

template<typename T>
DynamicPerfectHash<T>::DynamicPerfectHash(){
  count = 0;
  sM = 0;
  M = 0;
  rehash_all();
}

template<typename T>
int DynamicPerfectHash<T>::insert(T elm, bool force){
  count += 1;
  if ( count > M ){
    return rehash_all(elm,true); /* TODO insert element */
  }
  int hash = Hash((long int)elm,k)%sM;
  LittleHashTable<T> *lht = (LittleHashTable<T> *) table[hash];
  if ( lht == NULL ){
    /* TODO
       detail this new declaration */
    lht = new LittleHashTable<T>(0,generate_k());
    table[hash] = lht;
  }
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
