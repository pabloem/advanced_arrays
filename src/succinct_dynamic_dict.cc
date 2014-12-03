template <typename T>
SuccDynamicDict<T>::SuccDynamicDict(unsigned long int expected_number_of_elms, 
                                 int word_size){
  hashes = new ExtendibleArray<void*>();

  n = 0;
  shift = 0;
  w = word_size;
  logW = 0;
  int tst = 1;
  while(tst < w){ tst = tst << 1; logW += 1; }

  real_w = 8*sizeof(T);
  hashes = new ExtendibleArray<void*>();

  if(expected_number_of_elms <= w*w*w*w){
    rehash_all(LEMMA3);
    return;
  }
  rehash_all(BUCKET_ARRAY);
  
}

template <typename T>
int SuccDynamicDict<T>::copy_elements(ExtendibleArray<T> *el_lst, T prefix){
  prefix = prefix << w;
  if(n == LEMMA3){
    int start_prefix = el_lst->number_of_elements;

    DynamicPerfectHash<T> *dph = (DynamicPerfectHash<T> *) (*hashes)[0];
    if(dph == NULL) return FAIL;

    dph->copy_elements(el_lst);

    for(int i = start_prefix; i < el_lst->number_of_elements; i++){
      (*el_lst)[i] = (*el_lst)[i] || prefix;
    }
  }
  if(n==BUCKET_ARRAY){
    for(int i = 0; i < hashes->number_of_elements; i ++){
      SuccDynamicDict<T> *sdd = (SuccDynamicDict<T> *) (*hashes)[i];
      if(sdd == NULL) continue;
      
      sdd->copy_elements(el_lst,i);
    }
  }
  return FINE;
}

template <typename T>
int SuccDynamicDict<T>::rehash_all(unsigned long int new_n){
  ExtendibleArray<T> *all_elms = NULL;
  if(n != new_n){
    //We have a problem here-> We have to resize the whole thing down
    all_elms = new ExtendibleArray<T>();
    //Get all elms from the underlying structures
    copy_elements(all_elms,0);

    // Clean up the underlying structures
    while(hashes->number_of_elements > 0){
      if(n == LEMMA3) delete (DynamicPerfectHash<T> *) hashes->pop();
      else delete (SuccDynamicDict<T> *) hashes->pop();
    }
  }

  if(new_n == LEMMA3){
    n = LEMMA3;
    DynamicPerfectHash<T> *dph = new DynamicPerfectHash<T>();
    hashes->push((void *)dph);
    while(all_elms != NULL && all_elms->number_of_elements > 0){
      dph->insert(all_elms->pop(),true);
    }
  }
  if(new_n == BUCKET_ARRAY){
    n = BUCKET_ARRAY;
    int i = 0;
    unsigned long int find_N = 1;
    for(i = 0; i < 64; i ++){
      if(find_N >= new_n) break;
      find_N = find_N << 1;
    }

    i-=1;
    find_N = find_N >> 1;
    find_N = find_N / (w*w);

    shift = i - 2*logW;

    int b_array_sz = find_N;
    hashes->grow(b_array_sz);
    hashes->setzeros();
    if(all_elms != NULL) build_bucket_arr(all_elms);
  }
}

template <typename T>
int SuccDynamicDict<T>::build_bucket_arr(ExtendibleArray<T> *elms){
  ExtendibleArray<void*> *ea = new ExtendibleArray<void*>(hashes->number_of_elements);
  ea->setzeros();
  while(elms->number_of_elements > 0){
    T elm = elms->pop();
    T idx = elm >> (real_w-shift);
    int real_shift = real_w-w + shift;
    T cut_elm = (elm << real_shift) >> real_shift;
    if((*ea)[idx] == NULL) (*ea)[idx] = new ExtendibleArray<T>();
    ExtendibleArray<T> *dict_list = (ExtendibleArray<T> *) (*ea)[idx];

    dict_list->push(cut_elm);
  }

  for(int i=0; i < hashes->number_of_elements; i++){
    ExtendibleArray<T> *dict_list = (ExtendibleArray<T> *) (*ea)[i];
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

template <typename T>
int SuccDynamicDict<T>::insert(T elm, bool force){
  count += 1;
  if(n == LEMMA3 && count <= n){
    return ((DynamicPerfectHash<T>*) (*hashes)[0])->insert(elm,force);
  }
  if(n == BUCKET_ARRAY && count <= n){
    T ms_bits = elm >> (real_w-shift);
    int real_shift = real_w-w + shift;
    T cut_elm = (elm << real_shift) >> real_shift;
    if((*hashes)[ms_bits] == NULL) (*hashes)[ms_bits] = new SuccDynamicDict<T>();
    SuccDynamicDict<T> *h = (SuccDynamicDict<T> *) (*hashes)[ms_bits];
    return h->insert(cut_elm,force);
  }
}

template <typename T>
int SuccDynamicDict<T>::lookup(T elm){
  if(n == LEMMA3){
    return ((ExtendibleArray<T>*) hashes[0])->lookup(elm);
  }
  if(n == BUCKET_ARRAY){
    T ms_bits = elm >> (real_w-shift);
    int real_shift = real_w-w + shift;
    T cut_elm = (elm << real_shift) >> real_shift;

    if((*hashes)[ms_bits] == NULL) return FAIL;
    DynamicPerfectHash<T> *h = (*hashes)[ms_bits];
    return h->lookup(cut_elm);

  }
}

template <typename T>
int SuccDynamicDict<T>::remove(T elm){
  count -= 1;
  if(n == LEMMA3){
    return ((ExtendibleArray<T>*) hashes[0])->remove(elm);
  }
  if(n == BUCKET_ARRAY){
    T ms_bits = elm >> (real_w-shift);
    int real_shift = real_w-w + shift;
    T cut_elm = (elm << real_shift) >> real_shift;
    if((*hashes)[ms_bits] == NULL) return FAIL;
    DynamicPerfectHash<T> *h = (*hashes)[ms_bits];
    return h->remove(cut_elm);
  }
}
