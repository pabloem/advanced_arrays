template <typename T>
int DynamicPerfectHash<T>::element_count(){
  return count;
}

template <typename T>
int DynamicPerfectHash<T>::copy_elements(ExtendibleArray<T>* el_lst){
  int el_idx = 0;
  for(int i = 0; i < sM; i++){
    LittleHashTable<T> *lht = (LittleHashTable<T> *) table[i];
    if( lht == NULL ) continue;
    int el_num = lht->elems_to_buffer(el_lst);
    el_idx += el_num;
  }
  return FINE;
}

template <typename T>
int DynamicPerfectHash<T>::cleanup(){
  for ( int i = 0; i < sM; i ++){
    LittleHashTable<T> *lht = (LittleHashTable<T> *) table[i];
    if (lht == NULL) continue;
    lht->cleanup();
  }
  return FINE;
}

template<typename T>
int DynamicPerfectHash<T>::rehash_all(T ins, bool add){
  ExtendibleArray<T>* elms = NULL;
  if(count > 0){
    elms = new ExtendibleArray<T>();
  }
  /* Put all elements in elms array. */
  copy_elements(elms);
  if(add) elms->push(ins);

  /*
    Clean up all the old structures - 
    Specifically, the LittleHashTable objects. */
  cleanup();

  /*
    Now we go and calculate the new numbers to resize the hash table. 
    We keep the previous ones, to add the new structures. */
  int pre_sM = sM;
  int tot_count = count;

  count = 0;
  M = (int) (1+c)*MAX(4,tot_count);
  k = generate_k();
  sM = M*sM_factor;

  /* 
     Allocate - or reallocate the big hash table, containing the Little ones. 
     The LittleHashTable elements are allocated lazily - only when they become
     necessary. */
  if ( table == NULL && sM > 0){
    table = (void **) malloc(sizeof(void*)*sM);
    memset(table,0,sizeof(void*)*sM);
  }
  else {
    void ** temp = (void **) realloc(table,sizeof(void*)*sM);
    if(temp != NULL) table = temp;
    memset(table+pre_sM,0,sizeof(void*)*(sM-pre_sM));
  }

  int res = add_all_elms(elms,tot_count);
  if(elms != NULL) delete elms;

  return res;
}

template<typename T>
int DynamicPerfectHash<T>::add_all_elms(ExtendibleArray<T>* elms, int num_elms){
  /*
    This function takes in the list of elements that we will insert in the
    dynamic perfect hash table, adds them to lists corresponding to the
    LittleHash tables that we add later on.   */

  if(num_elms == 0) return FINE;

  void ** lists = (void **) malloc(sizeof(void*)*sM);
  memset(lists,0,sizeof(void*)*sM);
  
  while(elms->number_of_elements > 0){
    T insert_me = elms->pop();
    int h = Hash((long int)insert_me,k)%sM;
    if(lists[h] == NULL) lists[h] = (void *) new ExtendibleArray<T>();
    ExtendibleArray<T> *this_lst = (ExtendibleArray<T> *) lists[h];
    this_lst->push(insert_me);
  }
  
  for(int i = 0; i < sM; i ++){
    if(lists[i] == 0) continue;

    ExtendibleArray<T> *this_lst = (ExtendibleArray<T> *) lists[i];

    if ( table[i] == 0 ){
      int litHashSz = 2*this_lst->number_of_elements;
      litHashSz = 2*litHashSz*(litHashSz-1);

      table[i] = (void *) new LittleHashTable<T>(litHashSz, generate_k());
    }

    LittleHashTable<T> *lht = (LittleHashTable<T> *) table[i];
    while(this_lst->number_of_elements > 0){
      lht->insert(this_lst->pop(),true);
      count+=1;
    }
    delete this_lst;
  }
  free(lists);
  return FINE;
}

template<typename T>
DynamicPerfectHash<T>::DynamicPerfectHash(){
  table = NULL;
  count = 0;
  sM = 0;
  M = 0;
  rehash_all();
}

template<typename T>
DynamicPerfectHash<T>::~DynamicPerfectHash(){
  for(int i = 0; i < sM; i ++){
    LittleHashTable<T> *lht = (LittleHashTable<T> *) table[i];
    if(lht == NULL) continue;

    delete lht;
  }
  free(table);
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
    /* Lazy creation of LittleHashTable : )
       TODO
       review that this sizing is correct */
    int litHashSz = 2;
    litHashSz = 2*litHashSz*(litHashSz-1);

    lht = new LittleHashTable<T>(litHashSz,generate_k());
    table[hash] = lht;
  }
  return lht->insert(elm,force);
}

template<typename T>
int DynamicPerfectHash<T>::lookup(T elm){
  int hash = Hash((long int) elm,k)%sM;
  count -= 1;
  LittleHashTable<T> *lht = (LittleHashTable<T> *) *(table+hash);
  if (lht == NULL) return FAIL;

  return lht->lookup(elm);
}

template<typename T>
int DynamicPerfectHash<T>::remove(T elm){
  int hash = Hash((long int) elm,k)%sM;
  LittleHashTable<T> *lht = (LittleHashTable<T> *) *(table+hash);

  return lht->remove(elm);
}
