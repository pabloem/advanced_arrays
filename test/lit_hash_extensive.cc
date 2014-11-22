#include "../include/little_hash.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
  LittleHashTable<int> *lht;
  srand(0);
  int k = rand()%PRIME_SDD;
  int inserted_elms = 10;
  int overload = 20;
  int arr_sz = 2*inserted_elms*(inserted_elms-1);
  inserted_elms += overload;
  arr_sz -= (1-arr_sz%2);
  k -= (1-k%2);
  printf("Creating hash table with %d elms, and k = %d\n",arr_sz,k);
  lht = new LittleHashTable<int>(arr_sz, k);

  srand(0);
  printf("\nInserting... \n");
  for ( int i = 0; i < inserted_elms; i ++){
    int elm = (int)rand();
    int h = Hash((long int) elm,k);
    printf("Elm %d - %d | Hash: %d | Idx: %d\n",i+1,elm,h,h%arr_sz);
    int res = lht->insert(elm);
    if ( res == COLLISION ){
      printf("Not inserted - COLLISION - Forcing\n");
      int new_res = lht->insert(elm,true);
      if (new_res == COLLISION) printf("FAILED TO INSERT\n");
      if (new_res == FINE ) printf("SUCCEEDED TO INSERT\n");
    }
    srand(elm);
  }

  srand(0);
  printf("\n\nLooking up...\n");
  for ( int i = 0; i < inserted_elms+10; i++ ){
    if ( i == inserted_elms ){
      printf("\n\nNow failures:\n");
    }
    int elm = (int)rand();
    int h = Hash((long int) elm,k);
    printf("Elm %d - %d | Hash: %d | Idx: %d\n",i+1,elm,h,h%arr_sz);
    int res = lht->lookup(elm);
    if ( res != FINE ){
      fprintf(stdout," - > ERROR\n");
    }
    srand(elm);
  }

  srand(0);
  printf("\n\nRemoving...\n");
  for ( int i = 0; i < inserted_elms; i++ ){
    int elm = (int)rand();
    int h = Hash((long int) elm,k);
    printf("Elm %d - %d | Hash: %d | Idx: %d\n",i+1,elm,h,h%arr_sz);
    int res = lht->lookup(elm);
    if ( res != FINE ) fprintf(stdout," - > ERROR\n");
    srand(elm);
  }

  for ( int i = 0; i < 10000; i++){
    lht = new LittleHashTable<int>(200, k);
    delete lht;
  }
  printf("\n\nEND\n");
}
