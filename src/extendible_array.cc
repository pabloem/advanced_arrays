template<typename T>
int ExtendibleArray<T>::push(T elm){
  grow(1);
  operator[](number_of_elements-1) = elm;
  return FINE;
}

template<typename T>
T ExtendibleArray<T>::pop(){
  T res = operator[](number_of_elements-1);
  shrink(1);
  return res;
}

template<typename T>
int ExtendibleArray<T>::extend_index_block(){
  void* reall = NULL;
  if ( index_block != NULL ){
    reall  = realloc(index_block, 
                     index_block_size*2*sizeof(void*));
    index_block_size *= 2;
  }
  else {
    reall = malloc(sizeof(void*));
    index_block_size = 1;
  }
  if ( reall == NULL ) return FAIL_TO_ALLOC;
  index_block = (void **)reall;
  return FINE;
}

template<typename T>
unsigned int ExtendibleArray<T>::capacity(){
  return index_block_used_sp*(index_block_used_sp+1)/2;
}

template<typename T>
ExtendibleArray<T>::ExtendibleArray(unsigned int n/* = 0*/) {
  index_block = NULL;
  index_block_size = 0;
  index_block_used_sp = 0;
  number_of_elements = 0;
  
  if ( n > 0 ){
    grow(n);
    setzeros();
  }
}

template<typename T>
ExtendibleArray<T>::~ExtendibleArray(){
  shrink(number_of_elements);
}

template<typename T>
int ExtendibleArray<T>::memory_footprint(){
  int size_in_memory = 0;
  size_in_memory += index_block_size*sizeof(void*);
  size_in_memory += capacity()*sizeof(T);
  return size_in_memory;
}

template<typename T>
void ExtendibleArray<T>::print(){
  print_to_f(stdout);
}

template<typename T>
void ExtendibleArray<T>::print_to_f(FILE* f){
  fprintf(f,"RESIZABLE ARRAY | CP: %d \tN_ELM: %d\n",
          capacity(),number_of_elements);
  fprintf(f,"INDEX_BLOCK | SZ: %d \tUSED: %d\n",
          index_block_size,index_block_used_sp);
  fprintf(f,"IB: %p | ",index_block);
  for (int i = 0; i < index_block_used_sp; i++){
    fprintf(f,"%p ",index_block[i]);
  }
  fprintf(f,"\n");
}

template<typename T>
int ExtendibleArray<T>::grow(int n) {
  // If we have not fully taken the last block, we take it
  if ( number_of_elements < capacity() ){
    /* If the available elements in the last block are enough, we take them
       otherwise, we fill up the block and prepare to continue */
    int diff = (n > capacity()-number_of_elements) ? 
      capacity()-number_of_elements : n;
    number_of_elements += diff;
    n = n - diff;
  }
  while ( n > 0 ) {
    int block_size = index_block_used_sp+1;
    T* new_block = (T*) malloc(block_size*sizeof(T));
    if (new_block == NULL){
      return FAIL_TO_ALLOC;
    }
    
    memset(new_block,0,block_size*sizeof(T));
    
    if ( index_block_used_sp == index_block_size ){
      /* In this case the index block is full, so we'll resize it */
      int res = extend_index_block();
      if (res == FAIL_TO_ALLOC) return FAIL_TO_ALLOC;
    }
    
    index_block[index_block_used_sp] = new_block;
    index_block_used_sp += 1;
    
    if ( n < block_size ) number_of_elements += n;
    else number_of_elements = capacity();
    n -= block_size;
  }
  return FINE;
}

template<typename T>
int ExtendibleArray<T>::shrink(int n) {
  if ( n > number_of_elements || number_of_elements == 0){
    return BAD_INPUT;
  }
  int final_n_elm = number_of_elements - n;
  while ( n > 0 ){
    int elm_in_last_block = index_block_used_sp - (capacity() - 
                                                   number_of_elements);
    if ( elm_in_last_block > n ){
      number_of_elements = final_n_elm;
      goto end;
    }
    free(index_block[index_block_used_sp-1]);
    index_block[index_block_used_sp-1] = NULL;
    index_block_used_sp -= 1;
    n -= elm_in_last_block;
    number_of_elements -= elm_in_last_block;
  }
  //number_of_elements = final_n_elm;
 end:
  if (number_of_elements == 0) free(index_block);
  return FINE;
}

template<typename T>
T& ExtendibleArray<T>::operator[](unsigned int idx) {
  float f_block;
  int i_block ;
  int elms_up_to_block;
  int idx_in_block;
  T* p;

  f_block = (sqrt(8*idx+1)-1)/2;
  i_block = (int) f_block;
    
  i_block++;
  elms_up_to_block = i_block*(i_block+1)/2;
  idx_in_block = i_block - (elms_up_to_block - idx);
  i_block--;

  p = (T *) index_block[i_block];
  return p[idx_in_block];
}

template<typename T>
int ExtendibleArray<T>::setzeros(){
  for (int i = 0; i < index_block_used_sp; i++){
    void* arr = index_block[i];
    memset(arr,0,(i+1)*sizeof(T));
  }
}
