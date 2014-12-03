SuccDynamicDict::SuccDynamicDict(unsigned long int expected_number_of_elms, 
                                 int word_size){
  hashes = new ExtendibleArray<void*>();

  n = 0;
  shift = 0;
  w = word_size;
  hashes = new ExtendibleArray<T>();

  if(expected_number_of_elms <= W*W*W*W){
    rehash_all(LEMMA3);
    return;
  }
  rehash_all(BUCKET_ARRAY);
  
}

int SuccDynamicDict::rehash_all(unsigned long int new_n){
  ExtendibleArray<T> *all_elms = NULL;
  if(n != new_n){
    //We have a problem here-> We have to resize the whole thing down
    all_elms = new ExtendibleArray();
    //Get all elms from the underlying structures
    for(int i = 0; i < hashes->number_of_elements; i ++){
      if((*hashes)[i] == NULL) continue;
      // Otherwise, we add all elements from this subhash table to our hash list
      //(*hashes)[i]->insert_all_elems(all_elems)
      //delete (*hashes)[i] // Then we free the element
    }
    //hashes->shrink(hashes->number_of_elements);
  }

  if(new_n == LEMMA3){
    n = LEMMA3;
    DynamicPerfectHash<T> *dph = new DynamicPerfectHash<T>();
    hashes.push(dph);
    while(all_elms != NULL && all_elms->number_of_elements > 0){
      dph->insert(all_elms->pop(),true);
    }
  }
  if(new_n == BUCKET_ARRAY){
    n = BUCKET_ARRAY;
    int i = 0;
    unsigned long int find_N = 1;
    for(i = 0; i < 64; i ++){
      if(find_N >= expected_number_of_elms) break;
      find_N = find_N << 1;
    }

    i-=1;
    find_N = find_N >> 1;
    find_N = find_N / (W*W);

    shift = i - 2*logW;

    int b_array_sz = find_N;
    hashes->grow(b_array_sz);
    hashes->setzeros();
    if(all_elms != NULL) build_bucket_arr(all_elms);
  }
}

int SuccDynamicDict::build_bucket_arr(ExtendibleArray<T> *elms){
  ExtendibleArray<void*> *ea = new ExtendibleArray<void*>(hashes->number_of_elements);
  ea->setzeros();
  while(elms->number_of_elements > 0){
    T elm = elms.pop();
    T idx = elm >> (w-shift);
    T cut_elm = (elm << shift) >> shift;
    if((*ea)[idx] == NULL) (*ea)[idx] = new ExtendibleArray<T>();
    ExtendibleArray<T> *dict_list = (ExtendibleArray<T> *) (*ea)[idx];

    dict_list->push(cut_elm);
  }

  for(int i=0; i < hashes->number_of_elements; i++){
    ExtendibleArray<T> *dict_list = (*ea)[i];
    if(dict_list == NULL) continue;

    if((*hashes)[i] == NULL){
      (*hashes)[i] = new SuccDynamicDict<T>(dict_list->number_of_elements,
                                                                   w-shift);
    }
    SuccDynamicDict<T> *sdd = (SuccDynamicDict<T> *) (*hashes)[i];
    while(dict_list->number_of_elements > 0){
      int res = sdd->insert(dict_list->pop(),true);

      if(res != FINE) return res;
    }
    delete dict_list;
  }
  delete ea;

  return FINE;
}

int SuccDynamicDict::insert(T elm, bool force){
  count += 1;
  if(n == LEMMA3 && count <= n){
    return ((ExtendibleArray<T>*) hashes[0])->insert(elm,force);
  }
  if(n == BUCKET_ARRAY && count <= n){
    T ms_bits = elm >> (w-shift);
    T cut_elm = (elm << shift) >> shift;
    if((*hashes)[ms_bits] == NULL) (*hashes)[ms_bits] = new SuccDynamicDict<T>();
    SuccDynamicDict<T> *h = (*hashes)[ms_bits];
    return h->insert(cut_elm,force);
  }
}

int SuccDynamicDict::lookup(T elm){
  if(n == LEMMA3){
    return ((ExtendibleArray<T>*) hashes[0])->lookup(elm);
  }
  if(n == BUCKET_ARRAY){
    int ms_bits = elm >> (w-shift);
    int cut_elm = (elm << shift) >> shift;
    if((*hashes)[ms_bits] == NULL) return FAIL;
    DynamicPerfectHash<T> *h = (*hashes)[ms_bits];
    return h->lookup(cut_elm);

  }
}

int SuccDynamicDict::remove(T elm){
  count -= 1;
  if(n == LEMMA3){
    return ((ExtendibleArray<T>*) hashes[0])->remove(elm);
  }
  if(n == BUCKET_ARRAY){
    int ms_bits = elm >> (w-shift);
    int cut_elm = (elm << shift) >> shift;
    if((*hashes)[ms_bits] == NULL) return FAIL;
    DynamicPerfectHash<T> *h = (*hashes)[ms_bits];
    return h->remove(cut_elm);
  }
}
